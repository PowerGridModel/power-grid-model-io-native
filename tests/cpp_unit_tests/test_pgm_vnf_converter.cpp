// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#include <power_grid_model_io_native/common/enum.hpp>
#include <power_grid_model_io_native/pgm_vnf_converter/pgm_vnf_converter.hpp>

#include <power_grid_model/auxiliary/dataset.hpp>
#include <power_grid_model/auxiliary/meta_data_gen.hpp>
#include <power_grid_model/common/exception.hpp>

#include <doctest/doctest.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

namespace power_grid_model_io_native {

using enum ExperimentalFeatures;

std::string_view const json_string = R"({"version":"1.0","type":"input","is_batch":false,"attributes":{},"data":{}})";

TEST_CASE("Test converter constructor") {
    SUBCASE("Without experimental features") {
        CHECK_THROWS_AS(PgmVnfConverter("", experimental_features_disabled), power_grid_model::ExperimentalFeature);
    }

    SUBCASE("With experimental features") { CHECK_NOTHROW(PgmVnfConverter("", experimental_features_enabled)); }
}

TEST_CASE("Test parse_vnf_file is callable") {
    auto converter = PgmVnfConverter("", experimental_features_enabled);
    CHECK_NOTHROW(converter.parse_vnf_file());
}

TEST_CASE("Test convert_input") {
    auto converter = PgmVnfConverter("", experimental_features_enabled);
    SUBCASE("Test convert_input is callable") { CHECK_NOTHROW(converter.convert_input()); }
    SUBCASE("Test convert_input") {
        converter.convert_input();
        auto json_result = converter.get_serialized_data();
        CHECK(json_string == json_result);
    }
}

// TEST_CASE("Test create_const_dataset_from_container is callable") {
//     power_grid_model::Container<power_grid_model::Node> container;
//     constexpr const auto& meta_data = power_grid_model::meta_data::meta_data_gen::meta_data;
//     CHECK_NOTHROW(create_const_dataset_from_container(container, meta_data));
// }

// TEST_CASE("Test serialize_data") {
//     power_grid_model::Container<power_grid_model::Node> container;
//     constexpr const auto& meta_data = power_grid_model::meta_data::meta_data_gen::meta_data;
//     power_grid_model::ConstDataset const const_dataset = create_const_dataset_from_container(container, meta_data);
//     CHECK_NOTHROW(serialize_data(const_dataset));
//     auto result = serialize_data(const_dataset);
//     CHECK(result == json_string);
// }

TEST_CASE("Test setter/getter of file_buffer") {
    auto converter = PgmVnfConverter("", experimental_features_enabled);
    std::string_view const value = "123";
    converter.set_file_buffer(value);
    auto file_buff = converter.get_file_buffer();
    CHECK(file_buff == value);
}

TEST_CASE("Test setter/getter of deserialized_data") {
    constexpr auto const& meta_data = power_grid_model::meta_data::meta_data_gen::meta_data;

    std::string_view const dataset_name = "input";
    power_grid_model::WritableDataset writable_dataset{false, 1, dataset_name, meta_data};

    auto converter = PgmVnfConverter("", experimental_features_enabled);
    converter.set_deserialized_dataset(&writable_dataset);
    auto* const writable_dataset_after_getter = converter.get_deserialized_dataset();
    CHECK(&writable_dataset == writable_dataset_after_getter);
}

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

TEST_CASE("Test parse_vnf_file_wrapper minimal example") {
    std::ifstream f("C:/Users/laury/Downloads/vision_validation.vnf");

    if (!f.is_open()) {
        std::cerr << "Error opening the file!";
    }

    std::ostringstream buffer;
    buffer << f.rdbuf();
    auto const fileContents = buffer.str();

    auto converter = PgmVnfConverter(fileContents, experimental_features_enabled);
    PgmVnfConverter* converterPtr = &converter;
    parse_vnf_file_wrapper(converterPtr);
    convert_input_wrapper(converterPtr);
    std::cout << converterPtr->get_serialized_data() << "\n";
}

} // namespace power_grid_model_io_native
