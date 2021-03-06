/*
 * \copyright Copyright 2014 Xiang Zhang All Rights Reserved.
 * \license @{
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @}
 */

#ifndef THUNDER_TENSOR_MATH_INL_TRANSFORM_HPP_
#define THUNDER_TENSOR_MATH_INL_TRANSFORM_HPP_

#include "thunder/tensor/math.hpp"
#include "thunder/tensor/math-inl.hpp"

#include <cmath>
#include <complex>

#include "thunder/exception.hpp"
#include "thunder/tensor/index_iterator.hpp"

namespace thunder {
namespace tensor {
namespace math {

template < typename T1, typename T2 >
T1 extract(const T1 &x, const T2 &y) {
  if (x.dimension() < y.dimension()) {
    throw out_of_range("Dimension exceeds limit.");
  }
  typename T1::dim_type y_dimension =
      static_cast< typename T1::dim_type >(y.dimension());
  for (typename T1::dim_type i = 0; i < y_dimension; ++i) {
    if (x.size(i) != static_cast< typename T1::size_type >(y.size(i))) {
      throw out_of_range("Size does not match.");
    }
  }
  typename T1::size_storage sz(x.dimension() - y_dimension + 1);
  for (typename T1::dim_type i = y_dimension; i < x.dimension(); ++i) {
    sz[i - y_dimension + 1] = x.size(i);
  }
  // Get the size of returning tensor
  sz[0] = 0;
  if (y.isContiguous()) {
    typename T2::size_type y_length = y.length();
    typename T2::pointer y_data = y.data();
    for (typename T2::size_type i = 0; i < y_length; ++i) {
      if (static_cast< bool >(y_data[i]) == true) {
        ++sz[0];
      }
    }
  } else {
    for (typename T2::reference_iterator begin = y.reference_begin(),
             end = y.reference_end(); begin != end; ++begin) {
      if (static_cast< bool >(*begin) == true) {
        ++sz[0];
      }
    }
  }

  // Create the new tensor and do the copy
  T1 t(sz, x.allocator());
  if (x.isContiguous() && y.isContiguous()) {
    typename T2::size_type y_length = y.length();
    typename T2::pointer y_data = y.data();
    typename T1::difference_type x_step = x.stride(y_dimension - 1);
    typename T1::size_type x_step_size = ::std::abs(x_step);
    typename T1::difference_type x_step_increment = x_step > 0 ? 1 : -1;
    typename T1::pointer t_data = t.data();
    typename T1::pointer x_data = x.data();
    typename T1::size_type current = 0;
    for (typename T2::size_type i = 0; i < y_length; ++i) {
      if (static_cast< bool >(y_data[i]) == true) {
        for (typename T1::size_type j = 0; j < x_step_size; ++j) {
          t_data[current++] = x_data[i * x_step + j * x_step_increment];
        }
      }
    }
  } else {
    typename T1::size_storage y_size(y.dimension());
    for (typename T1::dim_type i = 0; i < y_size.size(); ++i) {
      y_size[i] = y.size(i);
    }
    typename T1::size_type pos = 0;
    IndexIterator< typename T1::size_storage > t_begin =
        IndexIterator< typename T1::size_storage>::begin(y_size);
    for (IndexIterator< typename T2::size_storage > begin =
             IndexIterator< typename T2::size_storage >::begin(y.size()),
             end = IndexIterator< typename T2::size_storage >::end(y.size());
         begin != end; ++begin, ++t_begin) {
      if (static_cast< bool >(y[*begin]()) == true) {
        t[pos++].copy(x[*t_begin]);
      }
    }
  }
  return t;
}

template < typename T1, typename T2 >
T1 shuffle(const T1 &x, const T2 &y) {
  if (static_cast< typename T1::dim_type >(
          y.size(y.dimension() - 1)) != x.dimension()) {
    throw out_of_range("Shuffle dimension mismatches.");
  }
  if (y.dimension() == 1) {
    T1 t(x.allocator());
    typename T1::size_storage ind(x.dimension());
    for (typename T2::dim_type i = 0; i < y.size(0); ++i) {
      ind[i] = static_cast< typename T1::size_type >(y(i));
      if (ind[i] >= x.size(i)) {
        throw out_of_range("Shuffle index exceeds limit.");
      }
    }
    t() = x(ind);
    return t;
  }
  typename T1::size_storage sz(y.dimension() - 1);
  for (typename T1::dim_type i = 0; i < sz.size(); ++i) {
    sz[i] = y.size(i);
  }
  T1 t(sz, x.allocator());
  typename T1::size_storage ind(x.dimension());
  for (IndexIterator< typename T1::size_storage > begin =
           IndexIterator< typename T1::size_storage >::begin(sz),
           end = IndexIterator< typename T1::size_storage >::end(sz);
       begin != end; ++begin) {
    for (typename T1::dim_type i = 0; i < ind.size(); ++i) {
      ind[i] = static_cast< typename T1::size_type >(y[*begin](i));
      if (ind[i] >= x.size(i)) {
        throw out_of_range("Shuffle index exceeds limit.");
      }
    }
    t(*begin) = x(ind);
  }
  return t;
}

template < typename T1, typename T2 >
T1 permute(const T1 &x, const T2 &y, typename T1::dim_type d) {
  if (y.dimension() != 1) {
    throw invalid_argument("Permutation index dimension exceeds 1.");
  }
  if (d >= x.dimension()) {
    throw out_of_range("Dimension exceeds limit.");
  }

  typename T1::size_storage sz(x.dimension());
  for (typename T1::dim_type i = 0; i < d; ++i) {
    sz[i] = x.size(i);
  }
  sz[d] = y.size(0);
  for (typename T1::dim_type i = d + 1; i < x.dimension(); ++i) {
    sz[i] = x.size(i);
  }

  T1 t(sz, x.allocator());
  if (x.partialContiguity(0, d) &&
      x.partialContiguity(d + 1, x.dimension() - 1)) {
    typename T1::pointer x_pointer = x.data();
    typename T1::size_type x_left_length = 1;
    for (typename T1::dim_type i = 0; i < d; ++i) {
      x_left_length *= x.size(i);
    }
    typename T1::difference_type x_left_step = d > 0 ? x.stride(d - 1) : 0;
    typename T1::size_type x_right_length = 1;
    for (typename T1::dim_type i = d + 1; i < x.dimension(); ++i) {
      x_right_length *= x.size(i);
    }
    typename T1::difference_type x_right_step = x.stride(x.dimension() - 1);
    typename T1::size_type x_length = x.size(d);
    typename T1::difference_type x_step = x.stride(d);
    typename T1::pointer t_pointer = t.data();
    typename T1::difference_type t_left_step = d > 0 ? t.stride(d - 1) : 0;
    typename T1::difference_type t_right_step = t.stride(t.dimension() - 1);
    typename T1::size_type t_length = t.size(d);
    typename T1::difference_type t_step = t.stride(d);
    typename T2::pointer y_pointer = y.data();
    typename T2::difference_type y_step = y.stride(y.dimension() - 1);
    for (typename T1::size_type i = 0; i < t_length; ++i) {
      typename T1::size_type x_index =
          static_cast< typename T1::size_type >(y_pointer[i * y_step]);
      if (x_index >= x_length) {
        throw out_of_range("Index exceeds limit.");
      }
      for (typename T1::size_type j = 0; j < x_left_length; ++j) {
        for (typename T1::size_type k = 0; k < x_right_length; ++k) {
          t_pointer[j * t_left_step + i * t_step + k * t_right_step] =
              x_pointer[j * x_left_step + x_index * x_step + k * x_right_step];
        }
      }
    }
  } else {
    typename T1::size_storage iter_size = sz;
    iter_size[d] = 1;
    typename T1::size_storage x_ind(sz.size());
    typename T1::size_storage t_ind(sz.size());
    for (typename T2::size_type i = 0; i < y.length(); ++i) {
      typename T1::size_type x_index =
          static_cast< typename T1::size_type >(y(i));
      if (x_index >= x.size(d)) {
        throw out_of_range("Index exceeds limit.");
      }
      for (IndexIterator< typename T1::size_storage > begin =
               IndexIterator< typename T1::size_storage >::begin(iter_size),
               end = IndexIterator< typename T1::size_storage >::end(iter_size);
           begin != end; ++begin) {
        x_ind = *begin;
        t_ind = *begin;
        x_ind[d] = x_index;
        t_ind[d] = i;
        t(t_ind) = x(x_ind);
      }
    }
  }

  return t;
}

#define THUNDER_TENSOR_MATH_DEFINE_STD_TRANSFORM(tfunc, sfunc)          \
  template < typename T1, typename T2 >                                 \
  T2 tfunc(const T1 &x, typename T2::allocator_type alloc) {            \
    T2 t(alloc);                                                        \
    t.resizeAs(x);                                                      \
    typename T2::pointer t_pointer = t.data();                          \
    typename T2::difference_type t_step = t.stride(t.dimension() - 1);  \
    if (x.partialContiguity(0, x.dimension() - 1)) {                    \
      typename T1::pointer x_pointer = x.data();                        \
      typename T1::difference_type x_step = x.stride(x.dimension() - 1); \
      typename T1::size_type x_length = x.length();                     \
      for (typename T1::size_type i = 0; i < x_length; ++i) {           \
        t_pointer[i * t_step] = static_cast< typename T2::value_type >( \
            ::std::sfunc(x_pointer[i * x_step]));                       \
      }                                                                 \
    } else {                                                            \
      typename T2::size_type i = 0;                                     \
      for (typename T1::reference_iterator x_begin = x.reference_begin(), \
               x_end = x.reference_end(); x_begin != x_end; ++x_begin) { \
        t_pointer[i * t_step] =                                         \
            static_cast< typename T2::value_type >(::std::sfunc(*x_begin)); \
        ++i;                                                            \
      }                                                                 \
    }                                                                   \
    return t;                                                           \
  }

THUNDER_TENSOR_MATH_DEFINE_STD_TRANSFORM(getReal, real);
THUNDER_TENSOR_MATH_DEFINE_STD_TRANSFORM(getImag, imag);
THUNDER_TENSOR_MATH_DEFINE_STD_TRANSFORM(getArg, arg);
THUNDER_TENSOR_MATH_DEFINE_STD_TRANSFORM(getCnrm, norm);

#undef THUNDER_TENSOR_MATH_DEFINE_STD_TRANSFORM

template < typename T >
typename T::real_tensor viewReal(const T &x) {
  return x;
}

template < typename T >
typename T::real_tensor viewImag(const T &x) {
  throw domain_error("Real tensor does not have an imaginery part");
  return x;
}

}  // namespace math
}  // namespace tensor
}  // namespace thunder

#endif  // THUNDER_TENSOR_MATH_INL_TRANSFORM_HPP_
