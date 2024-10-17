# SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
#
# SPDX-License-Identifier: MPL-2.0

set(PROJECT_SOURCES
    "test_c_api.cpp"
    "test_entry_point.cpp"
    "test_c_api_vnf_converter.cpp"
)

add_executable(power_grid_model_io_native_c_api_tests ${PROJECT_SOURCES})

target_link_libraries(power_grid_model_io_native_c_api_tests
    PRIVATE
        power_grid_model
        power_grid_model_io_native
        power_grid_model_io_native_c
        doctest::doctest
)

doctest_discover_tests(power_grid_model_io_native_c_api_tests)
