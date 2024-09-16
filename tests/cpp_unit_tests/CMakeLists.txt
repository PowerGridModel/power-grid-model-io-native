# SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
#
# SPDX-License-Identifier: MPL-2.0

set(PROJECT_SOURCES
    "test_pgm_vnf_converter.cpp"
    "test_entry_point.cpp"
)

add_executable(power_grid_model_io_native_unit_tests ${PROJECT_SOURCES})

target_link_libraries(power_grid_model_io_native_unit_tests
    PRIVATE
        power_grid_model
        power_grid_model_io_native
        doctest::doctest
        nlohmann_json nlohmann_json::nlohmann_json
)

doctest_discover_tests(power_grid_model_io_native_unit_tests)
