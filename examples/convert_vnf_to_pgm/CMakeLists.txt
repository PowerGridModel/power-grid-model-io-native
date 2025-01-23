# SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
#
# SPDX-License-Identifier: MPL-2.0

add_executable(convert_vnf_to_pgm "src/main.cpp")

target_link_libraries(convert_vnf_to_pgm
	PRIVATE power_grid_model_io_native_c
)

install(TARGETS convert_vnf_to_pgm
  EXPORT power_grid_model_io_nativeTargets
  COMPONENT power_grid_model_io_native
)
