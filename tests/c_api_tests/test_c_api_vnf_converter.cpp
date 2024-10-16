// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

// #include <power_grid_model_io_native_c/vnf_pgm_converter.h>
#include <power_grid_model_io_native_c/handle.h>

#include <power_grid_model/common/exception.hpp>

#include "C:\headers\true_pgmionative\power-grid-model-io-native\power_grid_model_io_native_c\power_grid_model_io_native_c\src\vnf_pgm_converter.cpp"

#include <doctest/doctest.h>

namespace power_grid_model_io_native {

TEST_CASE("Test PGM_IO_create_vnf_converter") {
    PGM_IO_Handle* handle = PGM_IO_create_handle();
    PGM_IO_Idx experimental_feature_flag = 0;

    SUBCASE("Test PGM_IO_create_vnf_converter without experimental feature flag") {
        CHECK_THROWS_AS(PGM_IO_create_vnf_converter(handle, nullptr, experimental_feature_flag),
                        power_grid_model::ExperimentalFeature);
    }

    SUBCASE("Test PGM_IO_create_vnf_converter with experimental feature flag") {
        PGM_IO_Idx experimental_feature_flag = 1;
    }
};

} // namespace power_grid_model_io_native