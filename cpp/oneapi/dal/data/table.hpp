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

#include <type_traits>

#include "oneapi/dal/data/detail/table_impl_wrapper.hpp"
#include "oneapi/dal/util/type_traits.hpp"

namespace oneapi::dal {

class ONEAPI_DAL_EXPORT table {
    friend detail::pimpl_accessor;
    using pimpl = detail::pimpl<detail::table_impl_iface>;

public:
    table();
    table(const table&) = default;
    table(table&&);

    template <typename Impl,
              typename ImplType = std::decay_t<Impl>,
              typename          = std::enable_if_t<is_table_impl_v<ImplType> &&
                                          !std::is_base_of_v<table, ImplType>>>
    table(Impl&& impl) {
        init_impl(new detail::table_impl_wrapper(std::forward<Impl>(impl)));
    }

    table& operator=(const table&) = default;
    table& operator                =(table&&);

    bool has_data() const noexcept;
    std::int64_t get_column_count() const;
    std::int64_t get_row_count() const;
    const table_metadata& get_metadata() const;
    std::int64_t get_kind() const;

protected:
    table(const pimpl& impl) : impl_(impl) {}

    void init_impl(pimpl::element_type* impl);

private:
    pimpl impl_;
};

class ONEAPI_DAL_EXPORT homogen_table : public table {
    friend detail::pimpl_accessor;
    using pimpl = detail::pimpl<detail::homogen_table_impl_iface>;

public:
    static std::int64_t kind();

public:
    homogen_table();

    template <typename Impl,
              typename ImplType = std::decay_t<Impl>,
              typename          = std::enable_if_t<is_homogen_table_impl_v<ImplType> &&
                                          !std::is_base_of_v<table, ImplType>>>
    homogen_table(Impl&& impl) {
        init_impl(std::forward<Impl>(impl));
    }

    template <typename Data>
    homogen_table(std::int64_t row_count,
                  std::int64_t column_count,
                  const Data* data_pointer,
                  homogen_data_layout layout = homogen_data_layout::row_major);

#ifdef ONEAPI_DAL_DATA_PARALLEL
    template <typename Data>
    homogen_table(sycl::queue& queue,
                  std::int64_t row_count,
                  std::int64_t column_count,
                  const Data* data_pointer,
                  homogen_data_layout layout = homogen_data_layout::row_major,
                  const sycl::vector_class<sycl::event>& dependencies = {});
#endif

    template <typename Data>
    const Data* get_data() const {
        return reinterpret_cast<const Data*>(this->get_data());
    }

    const void* get_data() const;

    const homogen_table_metadata& get_metadata() const;

    std::int64_t get_kind() const {
        return kind();
    }

private:
    template <typename Impl>
    void init_impl(Impl&& impl) {
        // TODO: usage of protected method of base class: a point to break inheritance?
        auto* wrapper = new detail::homogen_table_impl_wrapper{ std::forward<Impl>(impl),
                                                                homogen_table::kind() };
        table::init_impl(wrapper);
    }

private:
    homogen_table(const pimpl& impl) : table(impl) {}
};

} // namespace oneapi::dal
