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

#include <iomanip>
#include <iostream>

#include "oneapi/dal/data/accessor.hpp"
#include "oneapi/dal/data/table.hpp"

std::ostream &operator<<(std::ostream &stream,
                         const oneapi::dal::table &table) {
  auto arr = oneapi::dal::row_accessor<const float>(table).pull();
  const auto x = arr.get_data();

  for (std::int64_t i = 0; i < table.get_row_count(); i++) {
    for (std::int64_t j = 0; j < table.get_column_count(); j++) {
      std::cout << std::setw(10) << std::setiosflags(std::ios::fixed)
                << std::setprecision(3) << x[i * table.get_column_count() + j];
    }
    std::cout << std::endl;
  }
  return stream;
}
