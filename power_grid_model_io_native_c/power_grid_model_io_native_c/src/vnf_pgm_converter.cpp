// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#define PGM_IO_DLL_EXPORTS

#include <power_grid_model_io_native/vnf_converter/vnf_pgm_converter.hpp>

#include "handle.hpp"
#include <power_grid_model_io_native_c/basics.h>
#include <power_grid_model_io_native_c/vnf_pgm_converter.h>

#include <power_grid_model/auxiliary/dataset.hpp>

using power_grid_model::ConstDataset;

// TODO(Laurynas-Jagutis) add call_with_catch for these functions.
PGM_IO_VnfConverter* PGM_VNF_create_converter(const PGM_IO_Handle* /*handle*/, char* file_buffer) {
    auto* converter = new PgmVnfConverter(file_buffer);
    parse_vnf_file_wrapper(converter);
    return reinterpret_cast<PGM_IO_VnfConverter*>(converter);
}

char const* PGM_VNF_get_input_data(const PGM_IO_Handle* /*handle*/, PGM_IO_VnfConverter* converter_ptr) {
    auto* converter = reinterpret_cast<PgmVnfConverter*>(converter_ptr);
    std::string json_data = convert_input_wrapper(converter);
    return json_data.c_str();
}

void PGM_VNF_delete_Converter(PGM_IO_VnfConverter* converter_ptr) {
    auto* converter = reinterpret_cast<PgmVnfConverter*>(converter_ptr);
    delete converter;
}
