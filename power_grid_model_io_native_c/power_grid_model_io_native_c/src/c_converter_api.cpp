// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#define PGM_IO_DLL_EXPORTS

#include "../../../../power_grid_model_io_native_c/power_grid_model_io_native_c/include/power_grid_model_io_native_c/c_converter_api.h"
#include "../../../../power_grid_model_io_native_c/power_grid_model_io_native_c/include/power_grid_model_io_native_c/vnf_pgm_converter.h"
#include "handle.hpp"

#include "../../../../../power-grid-model/power_grid_model_c/power_grid_model_c/src/forward_declarations.hpp"

PgmVnfConverter* PGM_VNF_create_converter(PGM_IO_Handle* handle, char* file_buffer){
    PgmVnfConverter* fake_conv = nullptr;
    return fake_conv;
};

PGM_ConstDataset* PGM_VNF_get_input_data(PGM_IO_Handle* handle, PgmVnfConverter* converter_ptr, PGM_ConstDataset* dataset){
    PGM_ConstDataset* fake_datas = nullptr;
    return fake_datas;
};
