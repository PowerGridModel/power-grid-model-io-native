// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#

#include <power_grid_model_io_native_c/basics.h>
#include <power_grid_model_io_native_c/handle.h>
#include <power_grid_model_io_native_c/vnf_pgm_converter.h>

#include <power_grid_model/common/exception.hpp>

#include <cstring>
#include <doctest/doctest.h>

namespace power_grid_model_io_native {

using enum PGM_IO_ExperimentalFeatures;

TEST_CASE("Test PGM_IO_create_vnf_converter") {
    PGM_IO_ExperimentalFeatures experimental_feature_flag = PGM_IO_experimental_features_disabled;

    SUBCASE("Test PGM_IO_create_vnf_converter without experimental feature flag") {
        PGM_IO_Handle* handle = PGM_IO_create_handle();
        auto converter = PGM_IO_create_vnf_converter(handle, "", experimental_feature_flag);
        CHECK(PGM_IO_error_code(handle) == PGM_IO_regular_error);
        PGM_IO_destroy_vnf_converter(converter);
        PGM_IO_destroy_handle(handle);
    }

    SUBCASE("Test PGM_IO_create_vnf_converter with experimental feature flag") {
        PGM_IO_Handle* handle = PGM_IO_create_handle();
        experimental_feature_flag = PGM_IO_experimental_features_enabled;
        auto converter = PGM_IO_create_vnf_converter(handle, "", experimental_feature_flag);
        CHECK(converter != nullptr);
        PGM_IO_destroy_vnf_converter(converter);
        PGM_IO_destroy_handle(handle);
    }
}

TEST_CASE("Test PGM_IO_get_vnf_input_data") {
    PGM_IO_Handle* handle = PGM_IO_create_handle();
    PGM_IO_ExperimentalFeatures experimental_feature_flag = PGM_IO_experimental_features_enabled;

    auto converter = PGM_IO_create_vnf_converter(handle, "", experimental_feature_flag);
    CHECK(converter != nullptr);

    auto json_result = PGM_IO_vnf_pgm_converter_get_input_data(handle, converter);
    std::string_view json_string = R"({"version":"1.0","type":"input","is_batch":false,"attributes":{},"data":{}})";
    CHECK(json_string == json_result);

    PGM_IO_destroy_vnf_converter(converter);
    PGM_IO_destroy_handle(handle);
}

} // namespace power_grid_model_io_native
