// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#ifndef POWER_GRID_MODEL_IO_NATIVE_C_VNF_PGM_CONVERTER_HPP
#define POWER_GRID_MODEL_IO_NATIVE_C_VNF_PGM_CONVERTER_HPP

#include <power_grid_model/auxiliary/dataset.hpp>
#include <power_grid_model/auxiliary/serialization/serializer.hpp>
#include <power_grid_model/common/exception.hpp>
#include <power_grid_model/component/node.hpp>
#include <power_grid_model/container.hpp>

#include <iostream>

inline power_grid_model::ConstDataset
create_const_dataset_from_container(const power_grid_model::Container<power_grid_model::Node>& /*container*/,
                                    power_grid_model::meta_data::MetaData const& meta_data) {
    // for now leave it empty
    std::string_view const dataset_name = "empty_dataset";
    power_grid_model::ConstDataset const_dataset{false, 1, dataset_name, meta_data};
    return const_dataset;
}

inline std::string get_serialized_data(power_grid_model::ConstDataset& const_dataset) {
    power_grid_model::meta_data::Serializer serializer(const_dataset, power_grid_model::SerializationFormat::json);
    std::string serialized_pgm_data = serializer.get_string(false, -1);
    return serialized_pgm_data;
}

class PgmVnfConverter {
  public:
    PgmVnfConverter(char* buffer = nullptr, power_grid_model::WritableDataset* data = nullptr);

    // Public member functions
    void parse_vnf_file();
    std::string convert_input();

  private:
    // Private attributes
    char* f_file_buffer;
    power_grid_model::WritableDataset*
        deserialized_data; // this type because it is generated by a deserializer type structure

    // Private setters/getters
    void set_file_buffer(char* file_buffer);

    void set_deserialized_data(power_grid_model::WritableDataset* deserialized_data);

    char* get_file_buffer();

    power_grid_model::WritableDataset* get_deserialized_data();

    // Private member functions
    std::vector<power_grid_model::Node> convert_node_input();
    void convert_line_input();
    void convert_sources_input();
    void convert_sym_loads_input();
    void convert_shunts_input();
    void convert_transformer_input();
    void convert_sym_gens_input();
    void convert_links_input();
};

inline PgmVnfConverter::PgmVnfConverter(char* buffer, power_grid_model::WritableDataset* data)
    : f_file_buffer(buffer), deserialized_data(data) {
    using namespace std::string_literals;
    using power_grid_model::ExperimentalFeature;
    throw ExperimentalFeature{"PGM_VNF_converter", ExperimentalFeature::TypeValuePair{.name = "PGM_VNF_conversion",
                                                                                      .value = std::to_string(1)}};
}

inline void PgmVnfConverter::parse_vnf_file() {
    // the function should use a deserializer type structure
    // will be implemented later
}

inline std::string PgmVnfConverter::convert_input() {
    std::vector<power_grid_model::Node> const nodes = convert_node_input();
    convert_line_input();
    convert_sources_input();
    convert_sym_loads_input();
    convert_shunts_input();
    convert_transformer_input();
    convert_sym_gens_input();
    convert_links_input();

    power_grid_model::Container<power_grid_model::Node> container;

    for (const auto& node : nodes) {
        container.emplace<power_grid_model::Node>(node.id(), node);
    }

    power_grid_model::meta_data::MetaData const meta_data;

    power_grid_model::ConstDataset const_dataset = create_const_dataset_from_container(container, meta_data);

    std::string serialized_pgm_data = get_serialized_data(const_dataset);

    // 1. our vnf importer it directly understands the vnf format
    // 2. convert vnf like dataset to internal types (take raw data and convert it to pgm component container)
    // 3. another function which 1. makes const dataset view from pgm component container  2. const dataset to
    // serializer

    return serialized_pgm_data;
}

inline void PgmVnfConverter::set_file_buffer(char* file_buffer) { this->f_file_buffer = file_buffer; }

inline void PgmVnfConverter::set_deserialized_data(power_grid_model::WritableDataset* data) {
    this->deserialized_data = data;
}

inline char* PgmVnfConverter::get_file_buffer() { return this->f_file_buffer; }

inline power_grid_model::WritableDataset* PgmVnfConverter::get_deserialized_data() { return this->deserialized_data; }

inline std::vector<power_grid_model::Node> PgmVnfConverter::convert_node_input() {
    std::vector<power_grid_model::NodeInput> node_inputs = {{1, 110.0}};

    std::vector<power_grid_model::Node> nodes;

    for (const auto& node_input : node_inputs) {
        nodes.emplace_back(node_input);
    }

    return nodes;
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

inline std::string convert_input_wrapper(PgmVnfConverter* obj) { return obj->convert_input(); }

#endif // POWER_GRID_MODEL_IO_NATIVE_C_VNF_PGM_CONVERTER_HPP
