// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#ifndef POWER_GRID_MODEL_IO_NATIVE_C_PGM_VNF_CONVERTER_HPP
#define POWER_GRID_MODEL_IO_NATIVE_C_PGM_VNF_CONVERTER_HPP

#include <power_grid_model_io_native/common/common.hpp>
#include <power_grid_model_io_native/common/enum.hpp>
#include <power_grid_model_io_native/common/exception.hpp>

#include <power_grid_model/auxiliary/dataset.hpp>
#include <power_grid_model/auxiliary/meta_data_gen.hpp>
#include <power_grid_model/auxiliary/serialization/serializer.hpp>
#include <power_grid_model/component/node.hpp>
#include <power_grid_model/container.hpp>

#include <iostream>
#include <regex>

namespace power_grid_model_io_native {

inline pgm::ConstDataset make_const_dataset(std::vector<pgm::NodeInput> const& node_input,
                                            pgm::meta_data::MetaData const& meta_data) {
    std::string_view const dataset_name = "input";
    pgm::ConstDataset const_dataset{false, 1, dataset_name, meta_data};
    const_dataset.add_buffer("node", node_input.size(), node_input.size(), nullptr, node_input.data());
    return const_dataset;
}

inline std::string serialize_data(pgm::ConstDataset const& const_dataset) {
    pgm::meta_data::Serializer serializer(const_dataset, pgm::SerializationFormat::json);
    std::string serialized_pgm_data = serializer.get_string(false, -1);
    return serialized_pgm_data;
}

class PgmVnfConverter {
  public:
    using enum ExperimentalFeatures;
    PgmVnfConverter(std::string_view buffer,
                    ExperimentalFeatures experimental_feature_flag = experimental_features_disabled);

    // Public member functions
    void parse_vnf_file();
    void convert_input();

    std::string const& get_serialized_data() const;
    void set_file_buffer(std::string_view file_buffer);
    void set_deserialized_dataset(pgm::WritableDataset* deserialized_data);
    std::string_view get_file_buffer() const;
    pgm::WritableDataset* get_deserialized_dataset();

  private:
    // Private attributes
    std::string_view buffer_;
    pgm::WritableDataset* deserialized_data_{
        nullptr}; // this type because it is generated by a deserializer type structure
    std::string serialized_data_;
    // attribute for experimentation
    std::vector<pgm::NodeInput> parsed_nodes_;

    // Private member functions
    std::vector<pgm::NodeInput> convert_node_input();
    void convert_line_input();
    void convert_sources_input();
    void convert_sym_loads_input();
    void convert_shunts_input();
    void convert_transformer_input();
    void convert_sym_gens_input();
    void convert_links_input();
};

inline PgmVnfConverter::PgmVnfConverter(std::string_view buffer, ExperimentalFeatures experimental_feature_flag)
    : buffer_(buffer) {
    if (experimental_feature_flag == experimental_features_disabled) {
        throw ExperimentalFeature{"PGM_VNF_converter",
                                  ExperimentalFeature::TypeValuePair{
                                      .name = "PGM_VNF_conversion",
                                      .value = "PgmVnfConverter is still in an experimental phase, if you would "
                                               "like to use it, enable experimental features."}};
    }
}

inline void PgmVnfConverter::parse_vnf_file() {
    using svmatch = std::match_results<std::string_view::const_iterator>;
    using svregex_iterator = std::regex_iterator<std::string_view::const_iterator>;

    pgm::ID node_id = 0;
    std::vector<pgm::NodeInput> all_nodes;
    // std::map<std::string, std::vector<std::string>> all_nodes;
    std::regex const nodes_regex{R"(\[NODE\]([\s\S]*?)\[\])"};
    std::match_results<std::string_view::const_iterator> nodes_match;

    std::regex_search(this->buffer_.begin(), this->buffer_.end(), nodes_match, nodes_regex);
    auto const& nodes = nodes_match[1]; // the first group is the nodes data
    std::string_view const nodes_data{nodes.first, nodes.second};

    std::regex const node_regex{
        R"#(#General GUID:'\{([^\}]*)\}'\s+CreationTime:([\d\.]+)(?:\s+Name:'([^']*)')?\s+Unom:([\d\.]+))#"};

    svregex_iterator it{nodes_data.begin(), nodes_data.end(), node_regex};
    svregex_iterator const end;

    while (it != end) {
        svmatch const match = *it;

        std::cout << "GUID: " << match[1].str() << "\n";
        std::cout << "CreationTime: " << match[2].str() << "\n";
        std::cout << "Name: " << match[3].str() << "\n";
        std::cout << "Unom: " << match[4].str() << "\n\n";
        double const unom = std::stod(match[4].str());

        all_nodes.emplace_back(node_id, unom);

        // all_nodes["ID"].push_back(std::to_string(node_id));
        // all_nodes["Unom"].push_back(match[4].str());

        ++node_id;
        ++it;
    }

    this->parsed_nodes_ = all_nodes;
}

inline void PgmVnfConverter::convert_input() {
    std::vector<pgm::NodeInput> const nodes = convert_node_input();
    convert_line_input();
    convert_sources_input();
    convert_sym_loads_input();
    convert_shunts_input();
    convert_transformer_input();
    convert_sym_gens_input();
    convert_links_input();

    // pgm::Container<pgm::Node> container;

    // for (auto const& node : nodes) {
    //     container.emplace<pgm::Node>(node.id(), node);
    // }

    constexpr auto const& meta_data = pgm::meta_data::meta_data_gen::meta_data;
    pgm::ConstDataset const const_dataset = make_const_dataset(nodes, meta_data);

    std::string const serialized_pgm_data = serialize_data(const_dataset);

    // 1. our vnf importer it directly understands the vnf format
    // 2. convert vnf like dataset to internal types (take raw data and convert it to pgm component container)
    // 3. another function which 1. makes const dataset view from pgm component container  2. const dataset to
    // serializer

    this->serialized_data_ = serialized_pgm_data;
}

inline void PgmVnfConverter::set_file_buffer(std::string_view file_buffer) { this->buffer_ = file_buffer; }

inline void PgmVnfConverter::set_deserialized_dataset(pgm::WritableDataset* data) { this->deserialized_data_ = data; }

inline std::string_view PgmVnfConverter::get_file_buffer() const { return this->buffer_; }

inline pgm::WritableDataset* PgmVnfConverter::get_deserialized_dataset() { return this->deserialized_data_; }

inline std::string const& PgmVnfConverter::get_serialized_data() const { return this->serialized_data_; }

inline std::vector<pgm::NodeInput> PgmVnfConverter::convert_node_input() {
    auto node_inputs = this->parsed_nodes_;
    // std::vector<pgm::Node> nodes;

    // nodes.reserve(node_inputs.size());
    // for (auto const& node_input : node_inputs) {
    //     nodes.emplace_back(node_input);
    // }

    return node_inputs;
}

inline void PgmVnfConverter::convert_line_input() {
    // Implementation
}

inline void PgmVnfConverter::convert_sources_input() {
    // Implementation
}

inline void PgmVnfConverter::convert_sym_loads_input() {
    // Implementation
}

inline void PgmVnfConverter::convert_shunts_input() {
    // Implementation
}

inline void PgmVnfConverter::convert_transformer_input() {
    // Implementation
}

inline void PgmVnfConverter::convert_sym_gens_input() {
    // Implementation
}

inline void PgmVnfConverter::convert_links_input() {
    // Implementation
}

inline void parse_vnf_file_wrapper(PgmVnfConverter* obj) { obj->parse_vnf_file(); }

inline std::string const& convert_input_wrapper(PgmVnfConverter* obj) {
    obj->convert_input();
    return obj->get_serialized_data();
}

} // namespace power_grid_model_io_native

#endif // POWER_GRID_MODEL_IO_NATIVE_C_PGM_VNF_CONVERTER_HPP
