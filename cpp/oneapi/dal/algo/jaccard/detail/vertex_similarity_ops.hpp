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

#include "oneapi/dal/algo/jaccard/common.hpp"
#include "oneapi/dal/algo/jaccard/vertex_similarity_types.hpp"

namespace oneapi::dal::preview {
namespace jaccard {
namespace detail {

template <typename... Options>
struct vertex_similarity_ops_dispatcher {
    similarity_result operator()(const descriptor_base &, const similarity_input &) const;
};

template <typename Descriptor>
struct vertex_similarity_ops {
    using float_t           = typename Descriptor::float_t;
    using method_t          = typename Descriptor::method_t;
    using input_t           = similarity_input;
    using result_t          = similarity_result;
    using descriptor_base_t = descriptor_base;

    auto operator()(const Descriptor &desc, const similarity_input &input) const {
        return vertex_similarity_ops_dispatcher<float_t, method_t>()(desc, input);
    }
};

} // namespace detail
} // namespace jaccard
} // namespace oneapi::dal::preview
