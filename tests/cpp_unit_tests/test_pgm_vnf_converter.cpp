// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#include <power_grid_model_io_native/vnf_converter/vnf_pgm_converter.hpp>

#include <doctest/doctest.h>

namespace power_grid_model_io_native {

TEST_CASE("Test converter constructor") { CHECK_THROWS_AS(PgmVnfConverter(), power_grid_model::ExperimentalFeature); };

} // namespace power_grid_model_io_native
