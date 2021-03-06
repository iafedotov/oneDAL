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

#include <memory>

namespace oneapi::dal::preview {
namespace jaccard {
namespace detail {

struct backend_base {
    virtual similarity_result operator()(const descriptor_base &, const similarity_input &) {
        return similarity_result();
    }
    virtual ~backend_base() {}
};

template <typename Float, typename Method>
struct backend_block : public backend_base {
    virtual similarity_result operator()(const descriptor_base &, const similarity_input &);
    virtual ~backend_block() {}
};

template <typename Float, class Method>
std::shared_ptr<backend_base> get_backend(const descriptor_base &desc,
                                          const similarity_input &input);
} // namespace detail
} // namespace jaccard
} // namespace oneapi::dal::preview
