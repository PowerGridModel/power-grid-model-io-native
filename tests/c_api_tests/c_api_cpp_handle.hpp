// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "power_grid_model_io_native_c.h"

#include <memory>

namespace power_grid_model_io_native {

// custom deleter
template <auto func> struct DeleterFunctor {
    template <typename T> void operator()(T* arg) const { func(arg); }
};

// unique pointers
using HandlePtr = std::unique_ptr<PGM_IO_Handle, DeleterFunctor<&PGM_IO_destroy_handle>>;

} // namespace power_grid_model
