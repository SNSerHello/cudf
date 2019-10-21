/*
 * Copyright (c) 2019, NVIDIA CORPORATION.
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
 */

#pragma once

#include <cudf/filling.hpp>
#include <cudf/types.hpp>
#include <rmm/mr/device_memory_resource.hpp>

// for gdf_scalar, unnecessary once we switch to cudf::scalar
#include <cudf/types.h>

#include <cuda_runtime.h>

#include <memory>

namespace cudf {
namespace experimental {
namespace detail {

/**---------------------------------------------------------------------------*
 * @brief Internal API to repeat rows of a Table.
 *
 * Creates a new table by repeating the rows of @p input_table. The number of
 * repetitions of each element is defined by the value at the corresponding
 * index of @p count
 * Example:
 * ```
 * in = [4,5,6]
 * count = [1,2,3]
 * return = [4,5,5,6,6,6]
 * ```
 * @p count should be non-nullable; should not contain negative values; and the
 * sum of count elements should not overflow the size_type's limit. It is
 * undefined behavior if @p count has negative values or the sum overflows and
 * @p check_count is set to false.
 *
 * @param input_table Input table
 * @param count Non-nullable column of a integral type
 * @param check_count Whether to check count (negative values and overflow)
 * @param stream CUDA stream to run this function
 * @param mr Memory resource to allocate the result output table
 * @return std::unique_ptr<table> The result table containing the repetitions
 *---------------------------------------------------------------------------**/
std::unique_ptr<table> repeat(table_view const& input_table,
                              column_view const& count, bool check_count,
                              cudaStream_t stream,
                              rmm::mr::device_memory_resource* mr);

/**---------------------------------------------------------------------------*
 * @brief Internal API to repeat rows of a Table.
 *
 * Creates a new table by repeating @p count times the rows of @p input_table.
 * Example:
 * ```
 * in = [4,5,6]
 * count = 2
 * return = [4,4,5,5,6,6]
 * ```
 * @p count should be non-null and should hold a non-negative value.
 *
 * @param input_table Input table
 * @param count Non-null scalar of a integral type
 * @param stream CUDA stream to run this function
 * @param mr Memory resource to allocate the result output table
 * @return std::unique_ptr<table> The result table containing the repetitions
 *---------------------------------------------------------------------------**/
std::unique_ptr<table> repeat(table_view const& input_table,
                              gdf_scalar const& count,
                              cudaStream_t stream,
                              rmm::mr::device_memory_resource* mr);

}  // namespace detail
}  // namespace experimental
}  // namespace cudf
