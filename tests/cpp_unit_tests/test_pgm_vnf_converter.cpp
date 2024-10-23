// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#include <power_grid_model_io_native/vnf_converter/vnf_pgm_converter.hpp>

#include <cstring>
#include <doctest/doctest.h>

namespace power_grid_model_io_native {

TEST_CASE("Test converter constructor") {
    SUBCASE("Without experimental features enabled") {
        CHECK_THROWS_AS(PgmVnfConverter(nullptr, nullptr, 0), power_grid_model::ExperimentalFeature);
    }

    SUBCASE("With experimental features enabled") { CHECK_NOTHROW(PgmVnfConverter(nullptr, nullptr, 1)); }
}

TEST_CASE("Test if the parse_vnf_file function can be called") {
    auto converter = PgmVnfConverter(nullptr, nullptr, 1);
    CHECK_NOTHROW(converter.parse_vnf_file());
}

TEST_CASE("Test the convert_input function") {
    auto converter = PgmVnfConverter(nullptr, nullptr, 1);
    SUBCASE("Test if the convert_input function can be called") { CHECK_NOTHROW(converter.convert_input()); }
    SUBCASE("Test the return of convert_input") {
        converter.convert_input();
        auto json_string = R"({"version":"1.0","type":"input","is_batch":false,"attributes":{},"data":{}})";
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
    auto json_string = R"({"version":"1.0","type":"input","is_batch":false,"attributes":{},"data":{}})";
    CHECK(result == json_string);
}

TEST_CASE("Test the setter and getter of file_buffer") {
    auto converter = PgmVnfConverter(nullptr, nullptr, 1);
    const char* value = "123";
    converter.set_file_buffer(value);
    auto file_buff = converter.get_file_buffer();
    CHECK(file_buff == value);
    CHECK(strcmp(file_buff, value) == 0);
}

TEST_CASE("Test the setter and getter of deserialized data") {
    auto converter = PgmVnfConverter(nullptr, nullptr, 1);
    power_grid_model::WritableDataset* dataset = nullptr;
    converter.set_deserialized_data(dataset);
    auto const_data = converter.get_deserialized_data();
    CHECK(dataset == const_data);
}

TEST_CASE("Test parse_vnf_file_wrapper") {
    auto converter = PgmVnfConverter(nullptr, nullptr, 1);
    PgmVnfConverter* converterPtr = &converter;
    CHECK_NOTHROW(parse_vnf_file_wrapper(converterPtr));
}

TEST_CASE("Test convert_input_wrapper") {
    auto converter = PgmVnfConverter(nullptr, nullptr, 1);
    PgmVnfConverter* converterPtr = &converter;
    auto json_string = R"({"version":"1.0","type":"input","is_batch":false,"attributes":{},"data":{}})";
    CHECK_NOTHROW(convert_input_wrapper(converterPtr));
    auto result = convert_input_wrapper(converterPtr);
    CHECK(json_string == result);
}

} // namespace power_grid_model_io_native
