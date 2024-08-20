// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#define PGM_VNF_DLL_EXPORTS

#include "dll_helpers/include/dll_helpers/import_export_helpers.h"

#include "../../../../../power-grid-model/power_grid_model_c/power_grid_model_c/src/forward_declarations.hpp"
#include "../../../../../power-grid-model/power_grid_model_c/power_grid_model_c/src/handle.hpp"

#include "../../../../power_grid_model_io_native_c/power_grid_model_io_native_c/include/power_grid_model_io_native_c/c_converter_api.h"
#include "../../../../power_grid_model_io_native_c/power_grid_model_io_native_c/include/power_grid_model_io_native_c/vnf_pgm_converter.h"

extern "C" {

PgmVnfConverter* PGM_VNF_create_converter(PGM_Handle* handle, char* file_buffer) {};

PGM_ConstDataset* PGM_VNF_get_input_data(PGM_Handle* handle, PgmVnfConverter* converter_ptr, PGM_ConstDataset* dataset){};

} // extern "C"
