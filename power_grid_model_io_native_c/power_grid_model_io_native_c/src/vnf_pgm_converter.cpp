// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#define PGM_IO_DLL_EXPORTS

#include "power_grid_model_io_native_c/vnf_pgm_converter.h"
#include "handle.hpp"

#include "../../../../../../power-grid-model/power_grid_model_c/power_grid_model_c/src/forward_declarations.hpp"
#include "../../../../../../power-grid-model/power_grid_model_c/power_grid_model_c/src/forward_declarations.hpp"
#include "../../../../../../power-grid-model/power_grid_model_c/power_grid_model/include/power_grid_model/common/exception.hpp"

#include <iostream>

// #include "power_grid_model_io_native/common/common.hpp"

PgmVnfConverter* parse_vnf_file_wrapper(PgmVnfConverter* obj) {
    obj->parse_vnf_file();
    return obj;
};

PGM_ConstDataset* convert_input_wrapper(PgmVnfConverter* obj) {
    return obj->convert_input();
};

PgmVnfConverter::PgmVnfConverter() {
    using namespace std::string_literals;
    using power_grid_model::ExperimentalFeature;
    throw ExperimentalFeature{
        "PGM_VNF_converter",
        ExperimentalFeature::TypeValuePair{
            .name = "PGM_VNF_conversion",
            .value = std::to_string(1)}
    };
};

void PgmVnfConverter::parse_vnf_file() {
    // a deserializer type structure
    // vnf file is a raw string
    // this->deserialized_data = parsed_data
};

PGM_ConstDataset* PgmVnfConverter::convert_input() {
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
    PGM_ConstDataset* fake_data = nullptr;;
    return fake_data;
};

void PgmVnfConverter::convert_node_input() {
    // Implementation
};

void PgmVnfConverter::convert_line_input() {
    // Implementation
};

void PgmVnfConverter::convert_sources_input() {
    // Implementation
};

void PgmVnfConverter::convert_sym_loads_input() {
    // Implementation
};

void PgmVnfConverter::convert_shunts_input() {
    // Implementation
};

void PgmVnfConverter::convert_transformer_input() {
    // Implementation
};

void PgmVnfConverter::convert_sym_gens_input() {
    // Implementation
};

void PgmVnfConverter::convert_links_input() {
    // Implementation
};

// void set_core_path(char const* const path) {
//     core_path = path;
//     std::cout << "Core path set to: '" << core_path << "'" << std::endl;
// };
