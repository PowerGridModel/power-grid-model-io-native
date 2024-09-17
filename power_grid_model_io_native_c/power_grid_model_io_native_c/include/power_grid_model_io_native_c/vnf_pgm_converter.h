// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#ifndef POWER_GRID_MODEL_IO_NATIVE_C_VNF_PGM_CONVERTER_H
#define POWER_GRID_MODEL_IO_NATIVE_C_VNF_PGM_CONVERTER_H

#include "basics.h"

#ifdef __cplusplus
extern "C" {
#endif
PGM_IO_API PGM_IO_VnfConverter* PGM_VNF_create_converter(PGM_IO_Handle* handle, char* file_buffer);

PGM_IO_API PGM_IO_ConstDataset* PGM_VNF_get_input_data(PGM_IO_Handle* handle, PGM_IO_VnfConverter* converter_ptr,
                                                       PGM_IO_ConstDataset* dataset);
#ifdef __cplusplus
}
#endif

#endif // POWER_GRID_MODEL_IO_NATIVE_C_VNF_PGM_CONVERTER_H
