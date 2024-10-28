// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#include <power_grid_model_io_native/common/enum.hpp>
#include <power_grid_model_io_native/vnf_converter/vnf_pgm_converter.hpp>

#include <cstring>
#include <doctest/doctest.h>

namespace power_grid_model_io_native {

using enum ExperimentalFeatures;

std::string_view json_string = R"({"version":"1.0","type":"input","is_batch":false,"attributes":{},"data":{}})";

TEST_CASE("Test converter constructor") {
    SUBCASE("Without experimental features enabled") {
        CHECK_THROWS_AS(PgmVnfConverter("", experimental_features_disabled), power_grid_model::ExperimentalFeature);
    }

    SUBCASE("With experimental features enabled") { CHECK_NOTHROW(PgmVnfConverter("", experimental_features_enabled)); }
}

TEST_CASE("Test if the parse_vnf_file function can be called") {
    auto converter = PgmVnfConverter("", experimental_features_enabled);
    CHECK_NOTHROW(converter.parse_vnf_file());
}

TEST_CASE("Test the convert_input function") {
    auto converter = PgmVnfConverter("", experimental_features_enabled);
    SUBCASE("Test if the convert_input function can be called") { CHECK_NOTHROW(converter.convert_input()); }
    SUBCASE("Test the return of convert_input") {
        converter.convert_input();
        auto json_result = converter.get_serialized_data();
        CHECK(json_string == json_result);
    }
}

TEST_CASE("Test if the create_const_dataset_from_container function can be called") {
    power_grid_model::Container<power_grid_model::Node> container;
    constexpr const auto& meta_data = power_grid_model::meta_data::meta_data_gen::meta_data;
    CHECK_NOTHROW(create_const_dataset_from_container(container, meta_data));
}

TEST_CASE("Test the serialize_data function") {
    power_grid_model::Container<power_grid_model::Node> container;
    constexpr const auto& meta_data = power_grid_model::meta_data::meta_data_gen::meta_data;
    power_grid_model::ConstDataset const const_dataset = create_const_dataset_from_container(container, meta_data);
    CHECK_NOTHROW(serialize_data(const_dataset));
    auto result = serialize_data(const_dataset);
    CHECK(result == json_string);
}

TEST_CASE("Test the setter and getter of file_buffer") {
    auto converter = PgmVnfConverter("", experimental_features_enabled);
    std::string_view value = "123";
    converter.set_file_buffer(value);
    auto file_buff = converter.get_file_buffer();
    CHECK(file_buff == value);
}

// TEST_CASE("Test the setter and getter of deserialized data") {
//     auto converter = PgmVnfConverter("", experimental_features_enabled);
//     power_grid_model::WritableDataset* dataset = nullptr;
//     converter.set_deserialized_data(dataset);
//     auto const_data = converter.get_deserialized_data();
//     CHECK(dataset == const_data);
// }

TEST_CASE("Test parse_vnf_file_wrapper") {
    auto converter = PgmVnfConverter("", experimental_features_enabled);
    PgmVnfConverter* converterPtr = &converter;
    CHECK_NOTHROW(parse_vnf_file_wrapper(converterPtr));
}

TEST_CASE("Test convert_input_wrapper") {
    auto converter = PgmVnfConverter("", experimental_features_enabled);
    PgmVnfConverter* converterPtr = &converter;
    CHECK_NOTHROW(convert_input_wrapper(converterPtr));
    auto result = convert_input_wrapper(converterPtr);
    CHECK(json_string == result);
}

} // namespace power_grid_model_io_native
