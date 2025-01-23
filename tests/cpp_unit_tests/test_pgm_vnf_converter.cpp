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
namespace {
using enum ExperimentalFeatures;

std::string_view const empty_json_string =
    R"({"version":"1.0","type":"input","is_batch":false,"attributes":{},"data":{}})";
} // namespace

TEST_CASE("Test converter constructor") {
    SUBCASE("Without experimental features") {
        CHECK_THROWS_AS(PgmVnfConverter("", experimental_features_disabled), pgm::ExperimentalFeature);
    }

    SUBCASE("With experimental features") { CHECK_NOTHROW(PgmVnfConverter("", experimental_features_enabled)); }
}

TEST_CASE("Test parse_vnf_file is callable") {
    auto converter = PgmVnfConverter("", experimental_features_enabled);
    CHECK_NOTHROW(converter.parse_vnf_file());
}

// TEST_CASE("Test create_const_dataset_from_container is callable") {
//     pgm::Container<pgm::Node> const container{};
//     constexpr const auto& meta_data = pgm::meta_data::meta_data_gen::meta_data;
//     CHECK_NOTHROW(create_const_dataset_from_container(container, meta_data));
// }

// TEST_CASE("Test serialize_data") {
//     pgm::Container<pgm::Node> const container{};
//     constexpr const auto& meta_data = pgm::meta_data::meta_data_gen::meta_data;
//     pgm::ConstDataset const const_dataset = create_const_dataset_from_container(container, meta_data);
//     CHECK_NOTHROW(serialize_data(const_dataset));
//     auto result = serialize_data(const_dataset);
//     CHECK(result == empty_json_string);
// }

TEST_CASE("Test setter/getter of file_buffer") {
    auto converter = PgmVnfConverter("", experimental_features_enabled);
    std::string_view const value = "123";
    converter.set_file_buffer(value);
    auto file_buff = converter.get_file_buffer();
    CHECK(file_buff == value);
}

TEST_CASE("Test setter/getter of deserialized_data") {
    using InputData = pgm::Container<pgm::NodeInput>;
    InputData converted_data;
    converted_data.emplace<pgm::NodeInput>(1, 1, 11.2);

    auto converter = PgmVnfConverter("", experimental_features_enabled);
    converter.set_deserialized_dataset(converted_data);
    auto converted_data_after_getter = converter.get_deserialized_dataset();
    // CHECK(converted_data == converted_data_after_getter);
    pgm::NodeInput const& c = converted_data.get_item<pgm::NodeInput>({0, 0});
    pgm::NodeInput const& c_after_getter = converted_data_after_getter.get_item<pgm::NodeInput>({0, 0});
    CHECK(c.id == c_after_getter.id);
    CHECK(c.u_rated == c_after_getter.u_rated);
}

TEST_CASE("Test parse_vnf_file_wrapper") {
    auto converter = PgmVnfConverter("", experimental_features_enabled);
    CHECK_NOTHROW(parse_vnf_file_wrapper(&converter));
}

namespace {

auto const* const vision_9_7_vnf_file_only_nodes = R"vnf(V9.7
NETWORK

[NODE]
#General GUID:'{7FF722ED-33B3-4761-84AC-A164310D3C86}' CreationTime:44875.5806865509 Name:'node1' Unom:11 
#Railtype 
#Installation Kb:0.5 Kt:1 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:14800 Y:14800 Symbol:1 Size:6 Width:4 UpstringsY:-70 FaultStringsX:-20 FaultStringsY:20 NoteX:5 NoteY:5 IconY:50 
#General GUID:'{1ED177A7-1F5D-4D81-8DE7-AB3E58512E0B}' CreationTime:44875.5937016435 Name:'node2' Unom:11 
#Railtype 
#Installation Kb:0.5 Kt:1 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:14940 Y:14800 Symbol:1 Size:6 Width:4 UpstringsY:-70 FaultStringsX:-20 FaultStringsY:20 NoteX:5 NoteY:5 IconY:50 
#General GUID:'{DDE3457B-DB9A-4DA9-9564-6F49E0F296BD}' CreationTime:44875.5965067593 Name:'node3' Unom:0.4 
#Railtype 
#Installation Kb:0.5 Kt:1 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15100 Y:14800 Symbol:1 Size:14 Width:4 UpstringsY:-150 FaultStringsX:-20 FaultStringsY:20 NoteX:5 NoteY:5 IconY:50 
#General GUID:'{A79AFDE9-4096-4BEB-AB63-2B851D7FC6D1}' CreationTime:44875.5989385185 Name:'node4' Unom:11 
#Railtype 
#Installation Kb:0.5 Kt:1 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15100 Y:15100 Symbol:1 Size:8 Width:4 UpstringsY:-90 FaultStringsX:-20 FaultStringsY:20 NoteX:5 NoteY:5 IconY:50 
#General GUID:'{7848DBC8-9685-452C-89AF-9AB308224689}' CreationTime:44886.4465440509 Unom:0.4 
#Railtype 
#Installation Kb:0.5 Kt:1 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15040 Y:14580 Symbol:1 Size:4 Width:4 UpstringsY:-50 FaultStringsX:-20 FaultStringsY:20 NoteX:5 NoteY:5 IconY:50 
[]

)vnf";

std::string_view const only_nodes_json_string =
    R"({"version":"1.0","type":"input","is_batch":false,"attributes":{},"data":{"node":[{"id":0,"u_rated":11},{"id":1,"u_rated":11},{"id":2,"u_rated":0.4},{"id":3,"u_rated":11},{"id":4,"u_rated":0.4}]}})";

} // namespace

TEST_CASE("Test parse_vnf_file_wrapper minimal example") {
    auto converter = PgmVnfConverter(vision_9_7_vnf_file_only_nodes, experimental_features_enabled);
    parse_vnf_file_wrapper(&converter);
    convert_input_wrapper(&converter);
    auto const result = converter.get_serialized_data();
    CHECK(result == only_nodes_json_string);
}

} // namespace power_grid_model_io_native
