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

PGM_IO_VnfConverter* PGM_VNF_create_converter(PGM_IO_Handle* /*handle*/, char* file_buffer) {
    PgmVnfConverter* converter = new PgmVnfConverter(file_buffer);
    parse_vnf_file_wrapper(converter);
    return reinterpret_cast<PGM_IO_VnfConverter*>(converter);
};

PGM_IO_ConstDataset* PGM_VNF_get_input_data(PGM_IO_Handle* /*handle*/, PGM_IO_VnfConverter* converter_ptr,
                                            PGM_IO_ConstDataset* /*dataset*/) {
    // we have to reinterpret the C struct pointer back to pointer to converter
    PgmVnfConverter* converter = reinterpret_cast<PgmVnfConverter*>(converter_ptr);
    power_grid_model::ConstDataset* result = convert_input_wrapper(converter);
    return reinterpret_cast<PGM_IO_ConstDataset*>(result);
};
