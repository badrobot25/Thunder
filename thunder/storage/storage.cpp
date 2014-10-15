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

#include "thunder/storage/storage.hpp"
#include "thunder/storage/storage-inl.hpp"

#include <complex>

namespace thunder {
namespace storage {

template class Storage< double >;
template class Storage< float >;
template class Storage< ::std::complex< double > >;
template class Storage< ::std::complex< float > >;

}  // namespace storage
}  // namespace thunder
