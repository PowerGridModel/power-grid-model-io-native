# SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
#
# SPDX-License-Identifier: MPL-2.0

add_library(power_grid_model_io_native STATIC)

set_target_properties(power_grid_model_io_native PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(power_grid_model_io_native PUBLIC power_grid_model)

target_include_directories(power_grid_model_io_native PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
