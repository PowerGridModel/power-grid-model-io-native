// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#

#include <power_grid_model_io_native_c/basics.h>
#include <power_grid_model_io_native_c/handle.h>
#include <power_grid_model_io_native_c/pgm_vnf_converter.h>

#include <power_grid_model/common/exception.hpp>

#include <cstring>
#include <direct.h>
#include <doctest/doctest.h>
#include <stdio.h>

namespace power_grid_model_io_native {

using enum PGM_IO_ExperimentalFeatures;

TEST_CASE("Test PGM_IO_create_vnf_converter") {
    PGM_IO_ExperimentalFeatures experimental_feature_flag = PGM_IO_experimental_features_disabled;

    SUBCASE("Test PGM_IO_create_vnf_converter without experimental feature flag") {
        PGM_IO_Handle* handle = PGM_IO_create_handle();
        auto converter = PGM_IO_create_pgm_vnf_converter(handle, "", experimental_feature_flag);
        CHECK(PGM_IO_error_code(handle) == PGM_IO_regular_error);
        PGM_IO_destroy_pgm_vnf_converter(converter);
        PGM_IO_destroy_handle(handle);
    }

    SUBCASE("Test PGM_IO_create_vnf_converter with experimental feature flag") {
        PGM_IO_Handle* handle = PGM_IO_create_handle();
        experimental_feature_flag = PGM_IO_experimental_features_enabled;
        auto converter = PGM_IO_create_pgm_vnf_converter(handle, "", experimental_feature_flag);
        CHECK(converter != nullptr);
        PGM_IO_destroy_pgm_vnf_converter(converter);
        PGM_IO_destroy_handle(handle);
    }
}

TEST_CASE("Test PGM_IO_get_vnf_input_data") {
    PGM_IO_Handle* handle = PGM_IO_create_handle();
    PGM_IO_ExperimentalFeatures experimental_feature_flag = PGM_IO_experimental_features_enabled;

    auto converter = PGM_IO_create_pgm_vnf_converter(handle, "", experimental_feature_flag);
    CHECK(converter != nullptr);

    auto json_result = PGM_IO_pgm_vnf_converter_get_input_data(handle, converter);
    std::string_view json_string = R"({"version":"1.0","type":"input","is_batch":false,"attributes":{},"data":{}})";
    CHECK(json_string == json_result);

    PGM_IO_destroy_pgm_vnf_converter(converter);
    PGM_IO_destroy_handle(handle);
}

TEST_CASE("Test PGM_IO_get_example_vnf_input_data") {
    PGM_IO_Handle* handle = PGM_IO_create_handle();
    PGM_IO_ExperimentalFeatures experimental_feature_flag = PGM_IO_experimental_features_enabled;

    FILE* file = NULL;
    errno_t err = fopen_s(
        &file, "C:/headers/pgm-io-native-fresh/power-grid-model-io-native/tests/data/vision_validation.vnf", "r");

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* fileContents = (char*)malloc(fileSize + 1);

    size_t bytesRead = fread(fileContents, 1, fileSize, file);
    fileContents[bytesRead] = '\0';

    auto converter = PGM_IO_create_pgm_vnf_converter(handle, fileContents, experimental_feature_flag);
    CHECK(converter != nullptr);

    auto json_result = PGM_IO_pgm_vnf_converter_get_input_data(handle, converter);
    std::string_view json_string =
        R"({"version":"1.0","type":"input","is_batch":false,"attributes":{},"data":{"node":[{"id":0,"u_rated":11},{"id":1,"u_rated":11},{"id":2,"u_rated":0.4},{"id":3,"u_rated":11},{"id":4,"u_rated":0.4}]}})";
    CHECK(json_string == json_result);

    PGM_IO_destroy_pgm_vnf_converter(converter);
    PGM_IO_destroy_handle(handle);
    fclose(file);
}

} // namespace power_grid_model_io_native
