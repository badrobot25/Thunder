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

#include <fstream>
#include <ios>
#include <sstream>
#include <string>

#include "thunder/serializer/binary_protocol.hpp"
#include "thunder/serializer/serializer.hpp"
#include "thunder/serializer/static.hpp"
#include "thunder/serializer/text_protocol.hpp"

#include "thunder/serializer/binary_protocol-inl.hpp"
#include "thunder/serializer/serializer-inl.hpp"
#include "thunder/serializer/static-inl.hpp"
#include "thunder/serializer/text_protocol-inl.hpp"

namespace thunder {
namespace serializer {

template class BinaryProtocol< ::std::stringstream >;
template class BinaryProtocol< ::std::fstream >;
template class TextProtocol< ::std::stringstream >;
template class TextProtocol< ::std::fstream >;

template class Serializer< BinaryProtocol< ::std::stringstream > >;
template class Serializer< BinaryProtocol< ::std::fstream > >;
template class Serializer< TextProtocol< ::std::stringstream > >;
template class Serializer< TextProtocol< ::std::fstream > >;

#define THUNDER_SERIALIZER_INSTANTIATE_STRINGSTREAM_CONSTRUCTOR(P)      \
  template Serializer< P >::Serializer();                               \
  template Serializer< P >::Serializer(::std::ios_base::openmode mode); \
  template Serializer< P >::Serializer(const ::std::string &str);       \
  template Serializer< P >::Serializer(                                 \
      const ::std::string &str, ::std::ios_base::openmode mode);

THUNDER_SERIALIZER_INSTANTIATE_STRINGSTREAM_CONSTRUCTOR(
    BinaryProtocol< ::std::stringstream >);
THUNDER_SERIALIZER_INSTANTIATE_STRINGSTREAM_CONSTRUCTOR(
    TextProtocol< ::std::stringstream >);

#undef THUNDER_SERIALIZER_INSTANTIATE_STRINGSTREAM_CONSTRUCTOR

#define THUNDER_SERIALIZER_INSTANTIATE_FSTREAM_CONSTRUCTOR(P)           \
  template Serializer< P >::Serializer();                               \
  template Serializer< P >::Serializer(const char * filename);          \
  template Serializer< P >::Serializer(                                 \
      const char * filename, ::std::ios_base::openmode mode);           \
  template Serializer< P >::Serializer(const ::std::string &filename);  \
  template Serializer< P >::Serializer(                                 \
      const ::std::string &filename, ::std::ios_base::openmode mode);

THUNDER_SERIALIZER_INSTANTIATE_FSTREAM_CONSTRUCTOR(
    BinaryProtocol< ::std::fstream >);
THUNDER_SERIALIZER_INSTANTIATE_FSTREAM_CONSTRUCTOR(
    TextProtocol< ::std::fstream >);

#undef THUNDER_SERIALIZER_INSTANTIATE_FSTREAM_CONSTRUCTOR

}  // namespace serializer
}  // namespace thunder
