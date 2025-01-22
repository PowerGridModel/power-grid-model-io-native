// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#ifndef POWER_GRID_MODEL_IO_NATIVE_C_PGM_VNF_CONVERTER_HPP
#define POWER_GRID_MODEL_IO_NATIVE_C_PGM_VNF_CONVERTER_HPP

#include <power_grid_model_io_native/common/common.hpp>
#include <power_grid_model_io_native/common/enum.hpp>
#include <power_grid_model_io_native/pgm_vnf_converter/converter_parser.hpp>

#include <power_grid_model/auxiliary/dataset.hpp>
#include <power_grid_model/auxiliary/meta_data_gen.hpp>
#include <power_grid_model/auxiliary/serialization/serializer.hpp>
#include <power_grid_model/common/exception.hpp>
#include <power_grid_model/component/node.hpp>
#include <power_grid_model/container.hpp>

#include <iostream>
#include <regex>

namespace power_grid_model_io_native {

inline std::string serialize_data(pgm::ConstDataset const& const_dataset) {
    pgm::meta_data::Serializer serializer(const_dataset, pgm::SerializationFormat::json);
    std::string serialized_pgm_data = serializer.get_string(false, -1);
    return serialized_pgm_data;
}

using InputData = pgm::Container<pgm::NodeInput>;
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
    void set_deserialized_dataset(InputData deserialized_data);
    std::string_view get_file_buffer() const;
    InputData get_deserialized_dataset();

  private:
    // Private attributes
    std::string_view buffer_;
    InputData deserialized_data_;
    std::string serialized_data_;
    // attribute for experimentation
    std::vector<pgm::NodeInput> parsed_nodes_;

    // Private member functions
    pgm::ConstDataset make_const_dataset(pgm::meta_data::MetaData const& meta_data);
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
        using pgm::ExperimentalFeature;
        throw ExperimentalFeature{
            "PGM_VNF_converter",
            ExperimentalFeature::TypeValuePair{.name = "PGM_VNF_conversion",
                                               .value = "PgmVnfConverter is still in an experimental phase, if you'd "
                                                        "like to use it, enable experimental features."}};
    }
}

inline void PgmVnfConverter::parse_vnf_file() {
    auto parser = PgmVnfParser(this->buffer_);
    parser.parse_input();
    // need for a deep copy
    this->deserialized_data_ = parser.converted_data;
}

inline pgm::ConstDataset PgmVnfConverter::make_const_dataset(pgm::meta_data::MetaData const& meta_data) {
    pgm::ConstDataset const_dataset{false, 1, "input", meta_data};
    auto node_info = this->deserialized_data_.get_group_idx<pgm::NodeInput>();
    return const_dataset;
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

    constexpr auto const& meta_data = pgm::meta_data::meta_data_gen::meta_data;
    pgm::ConstDataset const const_dataset = make_const_dataset(meta_data);

    std::string const serialized_pgm_data = serialize_data(const_dataset);

    // 1. our vnf importer it directly understands the vnf format
    // 2. convert vnf like dataset to internal types (take raw data and convert it to pgm component container)
    // 3. another function which 1. makes const dataset view from pgm component container  2. const dataset to
    // serializer

    this->serialized_data_ = serialized_pgm_data;
}

inline void PgmVnfConverter::set_file_buffer(std::string_view file_buffer) { this->buffer_ = file_buffer; }

inline void PgmVnfConverter::set_deserialized_dataset(InputData data) { this->deserialized_data_ = data; }

inline std::string_view PgmVnfConverter::get_file_buffer() const { return this->buffer_; }

inline InputData PgmVnfConverter::get_deserialized_dataset() { return this->deserialized_data_; }

inline std::string const& PgmVnfConverter::get_serialized_data() const { return this->serialized_data_; }

inline std::vector<pgm::NodeInput> PgmVnfConverter::convert_node_input() {
    auto node_inputs = this->parsed_nodes_;
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
