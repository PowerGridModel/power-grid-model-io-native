// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <power_grid_model_io_native_c/power_grid_model_io_native_c/src/handle.cpp>

#include <power_grid_model/common/exception.hpp>
#include <power_grid_model_c/power_grid_model_c/src/forward_declarations.hpp>

#include <iostream>

#ifndef POWER_GRID_MODEL_IO_NATIVE_C_VNF_PGM_CONVERTER_H
#define POWER_GRID_MODEL_IO_NATIVE_C_VNF_PGM_CONVERTER_H

class PgmVnfConverter {
  public:
    PgmVnfConverter(char* buffer = nullptr, PGM_WritableDataset* data = nullptr);

    // Public member functions
    void parse_vnf_file();
    PGM_ConstDataset* convert_input();

  private:
    // Private attributes
    char* f_file_buffer;
    PGM_WritableDataset* deserialized_data; // this type because it is generated by a deserializer type structure

    // Private setters/getters
    void set_file_buffer(char* file_buffer);

    void set_deserialized_data(PGM_WritableDataset* deserialized_data);

    char* get_file_buffer();

    PGM_WritableDataset* get_deserialized_data();

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

inline PgmVnfConverter::PgmVnfConverter(char* buffer = nullptr, PGM_WritableDataset* data = nullptr)
    : f_file_buffer(buffer), deserialized_data(data) {
    using namespace std::string_literals;
    using power_grid_model::ExperimentalFeature;
    throw ExperimentalFeature{"PGM_VNF_converter", ExperimentalFeature::TypeValuePair{.name = "PGM_VNF_conversion",
                                                                                      .value = std::to_string(1)}};
};

inline void PgmVnfConverter::parse_vnf_file(){};

inline PGM_ConstDataset* PgmVnfConverter::convert_input() {
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
    // for now
    PGM_ConstDataset* fake_data = nullptr;
    return fake_data;
};

inline void PgmVnfConverter::set_file_buffer(char* file_buffer) { this->f_file_buffer = file_buffer; };

inline void PgmVnfConverter::set_deserialized_data(PGM_WritableDataset* deserialized_data) {
    this->deserialized_data = deserialized_data;
};

inline char* PgmVnfConverter::get_file_buffer() { return this->f_file_buffer; };

inline PGM_WritableDataset* PgmVnfConverter::get_deserialized_data() { return this->deserialized_data; };

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

inline PgmVnfConverter* parse_vnf_file_wrapper(PgmVnfConverter* obj) {
    obj->parse_vnf_file();
    return obj;
};

inline PGM_ConstDataset* convert_input_wrapper(PgmVnfConverter* obj) { return obj->convert_input(); };

    // void set_core_path(char const* const path) {};

#endif // VNF_PGM_CONVERTER_H
