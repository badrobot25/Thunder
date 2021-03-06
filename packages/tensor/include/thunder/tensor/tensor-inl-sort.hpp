/*
 * \copyright Copyright 2014-2015 Xiang Zhang All Rights Reserved.
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

#ifndef THUNDER_TENSOR_TENSOR_INL_SORT_HPP_
#define THUNDER_TENSOR_TENSOR_INL_SORT_HPP_

#include "thunder/tensor/tensor.hpp"
#include "thunder/tensor/tensor-inl.hpp"

#include "thunder/exception.hpp"
#include "thunder/tensor/math.hpp"
#include "thunder/tensor/complex.hpp"

namespace thunder {
namespace tensor {

template < typename S >
const Tensor< S >& Tensor< S >::sort(dim_type d, bool r) const {
  return math::sort(*this, d, r);
}

template < typename S >
const Tensor< S >& Tensor< S >::sort(
    dim_type d, Tensor< size_storage > *pos, bool r) const {
  return math::sort(*this, d, pos, r);
}


template < typename S >
Tensor< S >& Tensor< S >::sort(dim_type d, bool r) {
  return const_cast< Tensor& >(const_cast< const Tensor* >(this)->sort(d, r));
}

template < typename S >
Tensor< S >& Tensor< S >::sort(
    dim_type d, Tensor< size_storage > *pos, bool r) {
  return const_cast< Tensor& >(
      const_cast< const Tensor* >(this)->sort(d, pos, r));
}

template < typename S >
Tensor< S > Tensor< S >::sort(const Tensor &x, dim_type d, bool r) {
  return x.clone().sort(d, r);
}

template < typename S >
Tensor< S > Tensor< S >::sort(
    const Tensor &x, dim_type d, Tensor< size_storage > *pos, bool r) {
  return x.clone().sort(d, pos, r);
}

}  // namespace tensor
}  // namespace thunder

#endif  // THUNDER_TENSOR_TENSOR_INL_SORT_HPP_
