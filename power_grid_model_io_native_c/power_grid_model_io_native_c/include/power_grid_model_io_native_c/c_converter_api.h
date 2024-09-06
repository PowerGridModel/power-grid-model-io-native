// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#ifndef POWER_GRID_MODEL_IO_NATIVE_C_C_CONVERTER_API_H
#define POWER_GRID_MODEL_IO_NATIVE_C_C_CONVERTER_API_H

#include "basics.h"
#include "vnf_pgm_converter.h"
#include "../src/handle.hpp"

#include "../../../../power-grid-model/power_grid_model_c/power_grid_model_c/src/forward_declarations.hpp"

#ifdef __cplusplus
extern "C" {
#endif

PGM_IO_API PgmVnfConverter* PGM_VNF_create_converter(PGM_IO_Handle* handle, char* file_buffer);

PGM_IO_API PGM_ConstDataset* PGM_VNF_get_input_data(PGM_IO_Handle* handle, PgmVnfConverter* converter_ptr, PGM_ConstDataset* dataset);

#ifdef __cplusplus
}
#endif 

#endif //POWER_GRID_MODEL_IO_NATIVE_C_C_CONVERTER_API_H
