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

#ifndef THUNDER_LINALG_MATH_INL_BLASLEVEL1_HPP_
#define THUNDER_LINALG_MATH_INL_BLASLEVEL1_HPP_

#include "thunder/linalg/math.hpp"
#include "thunder/linalg/math-inl.hpp"

#include "thunder/tensor.hpp"

namespace thunder {
namespace linalg {
namespace math {

template < typename L >
const typename L::tensor_type& asum(
    L *l, const typename L::tensor_type &x, const typename L::tensor_type &r) {
  return r;
}

template < typename L >
const typename L::tensor_type& axpy(
    L *l, const typename L::tensor_type &x, const typename L::tensor_type &y,
    const typename L::value_type &a) {
  return y;
}

template < typename L >
const typename L::tensor_type& copy(
    L *l, const typename L::tensor_type &x, const typename L::tensor_type &r) {
  return r;
}

template < typename L >
const typename L::tensor_type& dot(
    L *l, const typename L::tensor_type &x, const typename L::tensor_type &y,
    const typename L::tensor_type &r) {
  return r;
}

template < typename L >
const typename L::tensor_type& sdot(
    L *l, const typename L::tensor_type &x, const typename L::tensor_type &y,
    const typename L::tensor_type &r) {
  return r;
}

template < typename L >
const typename L::tensor_type& dotc(
    L *l, const typename L::tensor_type &x, const typename L::tensor_type &y,
    const typename L::tensor_type &r) {
  return r;
}

template < typename L >
const typename L::tensor_type& nrm2(
    L *l, const typename L::tensor_type &x, const typename L::tensor_type &r) {
  return r;
}

template < typename L >
const typename L::tensor_type& rot(
    L *l, const typename L::tensor_type &x, const typename L::tensor_type &y,
    const typename L::value_type &c, const typename L::value_type &s) {
  return y;
}

template < typename L >
const typename L::tensor_type& rotm(
    L *l, const typename L::tensor_type &x, const typename L::tensor_type &y,
    const typename L::tensor_type &p) {
  return p;
}

template < typename L >
const typename L::tensor_type& scal(
    L *l, const typename L::tensor_type &x, const typename L::value_type &a) {
  return x;
}

template < typename L >
const typename L::tensor_type& swap(
    L *l, const typename L::tensor_type &x, const typename L::tensor_type &y) {
  return y;
}

template < typename L >
const typename L::size_tensor& iamax(
    L *l, const typename L::tensor_type &x, const typename L::size_tensor &r) {
  return r;
}

template < typename L >
const typename L::size_tensor& iamin(
    L *l, const typename L::tensor_type &x, const typename L::size_tensor &r) {
  return r;
}

template < typename L >
const typename L::tensor_type& cabs1(
    L *l, const typename L::tensor_type &x, const typename L::tensor_type &r) {
  return r;
}

}  // namespace math
}  // namespace linalg
}  // namespace thunder

#endif  // THUNDER_LINALG_MATH_INL_BLASLEVEL1_HPP_
