/*******************************************************************************
* Copyright 2020 Intel Corporation
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
*******************************************************************************/

#pragma once

#include "oneapi/dal/util/detail/type_traits.hpp"

namespace oneapi::dal {

template <typename T>
struct is_table_impl {
    ONEAPI_DAL_SIMPLE_HAS_METHOD_TRAIT(std::int64_t, get_column_count, () const)
    ONEAPI_DAL_SIMPLE_HAS_METHOD_TRAIT(std::int64_t, get_row_count, () const)
    ONEAPI_DAL_SIMPLE_HAS_METHOD_TRAIT(const table_metadata&, get_metadata, () const)
    ONEAPI_DAL_SIMPLE_HAS_METHOD_TRAIT(std::int64_t, get_kind, () const)

    static constexpr bool value = has_method_get_column_count_v<T> &&
                                  has_method_get_row_count_v<T> && has_method_get_metadata_v<T> &&
                                  has_method_get_kind_v<T>;
};

template <typename T>
inline constexpr bool is_table_impl_v = is_table_impl<T>::value;

template <typename T>
struct is_homogen_table_impl {
    ONEAPI_DAL_SIMPLE_HAS_METHOD_TRAIT(const void*, get_data, () const)
    ONEAPI_DAL_SIMPLE_HAS_METHOD_TRAIT(const homogen_table_metadata&, get_metadata, () const)

    using base = is_table_impl<T>;

    static constexpr bool value = base::template has_method_get_column_count_v<T> &&
                                  base::template has_method_get_row_count_v<T> &&
                                  has_method_get_metadata_v<T> && has_method_get_data_v<T>;
};

template <typename T>
inline constexpr bool is_homogen_table_impl_v = is_homogen_table_impl<T>::value;

} // namespace oneapi::dal
