// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

// NOLINTBEGIN(misc-include-cleaner)

#include "c_api_cpp_handle.hpp"
#include "power_grid_model_io_native_c.h"

#include <doctest/doctest.h>
namespace power_grid_model_io_native {

TEST_CASE("C API") {
    // get handle
    HandlePtr const unique_handle{PGM_IO_create_handle()};
    REQUIRE(unique_handle != nullptr);
    CHECK(PGM_IO_error_code(unique_handle.get()) == PGM_IO_no_error);
}

} // namespace power_grid_model_io_native

// NOLINTEND(misc-include-cleaner)
