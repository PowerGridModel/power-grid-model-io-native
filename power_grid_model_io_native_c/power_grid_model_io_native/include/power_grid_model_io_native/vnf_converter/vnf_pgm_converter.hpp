// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#ifndef POWER_GRID_MODEL_IO_NATIVE_C_VNF_PGM_CONVERTER_HPP
#define POWER_GRID_MODEL_IO_NATIVE_C_VNF_PGM_CONVERTER_HPP

#include <power_grid_model/auxiliary/dataset.hpp>
#include <power_grid_model/common/exception.hpp>

#include <iostream>

class PgmVnfConverter {
  public:
    PgmVnfConverter(char* buffer = nullptr, power_grid_model::WritableDataset* data = nullptr);

    // Public member functions
    void parse_vnf_file();
    void convert_input(power_grid_model::ConstDataset* dataset);

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
    void convert_node_input();
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
};

inline void PgmVnfConverter::parse_vnf_file(){
    // the function should use a deserializer type structure
    // will be implemented later
};

inline void PgmVnfConverter::convert_input(power_grid_model::ConstDataset* /*dataset*/) {
    convert_node_input();
    convert_line_input();
    convert_sources_input();
    convert_sym_loads_input();
    convert_shunts_input();
    convert_transformer_input();
    convert_sym_gens_input();
    convert_links_input();

    // then return the buffer
    // return pgm_input_data;
    // for now.
    // fill in dataset
};

inline void PgmVnfConverter::set_file_buffer(char* file_buffer) { this->f_file_buffer = file_buffer; };

inline void PgmVnfConverter::set_deserialized_data(power_grid_model::WritableDataset* data) {
    this->deserialized_data = data;
};

inline char* PgmVnfConverter::get_file_buffer() { return this->f_file_buffer; };

inline power_grid_model::WritableDataset* PgmVnfConverter::get_deserialized_data() { return this->deserialized_data; };

inline void PgmVnfConverter::convert_node_input(){
    // Implementation
};

inline void PgmVnfConverter::convert_line_input(){
    // Implementation
};

inline void PgmVnfConverter::convert_sources_input(){
    // Implementation
};

inline void PgmVnfConverter::convert_sym_loads_input(){
    // Implementation
};

inline void PgmVnfConverter::convert_shunts_input(){
    // Implementation
};

inline void PgmVnfConverter::convert_transformer_input(){
    // Implementation
};

inline void PgmVnfConverter::convert_sym_gens_input(){
    // Implementation
};

inline void PgmVnfConverter::convert_links_input(){
    // Implementation
};

inline void parse_vnf_file_wrapper(PgmVnfConverter* obj) { obj->parse_vnf_file(); };

inline power_grid_model::ConstDataset* convert_input_wrapper(PgmVnfConverter* obj,
                                                             power_grid_model::ConstDataset* dataset) {
    obj->convert_input(dataset);
};

#endif // POWER_GRID_MODEL_IO_NATIVE_C_VNF_PGM_CONVERTER_HPP
