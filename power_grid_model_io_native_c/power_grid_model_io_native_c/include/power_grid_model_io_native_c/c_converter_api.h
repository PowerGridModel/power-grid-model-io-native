// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#ifndef C_CONVERTER_API_H
#define C_CONVERTER_API_H

#ifndef PGM_VNF_DLL_EXPORTS
#define PGM_VNF_DLL_EXPORTS
#endif

#include "../../../../power_grid_model_io_native/include/power_grid_model_io_native/vnf_converter/dll_helpers/include/dll_helpers/import_export_helpers.h"

#include "../../../../../power-grid-model/power_grid_model_c/power_grid_model_c/src/forward_declarations.hpp"
#include "../../../../../power-grid-model/power_grid_model_c/power_grid_model_c/src/handle.hpp"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PgmVnfConverter PgmVnfConverter;


PGM_VNF_converter_API PgmVnfConverter* PGM_VNF_create_converter(PGM_Handle* handle, char* file_buffer);


PGM_VNF_converter_API PGM_ConstDataset* PGM_VNF_get_input_data(PGM_Handle* handle, PgmVnfConverter* converter_ptr, PGM_ConstDataset* dataset);

};
#endif //C_CONVERTER_API_H