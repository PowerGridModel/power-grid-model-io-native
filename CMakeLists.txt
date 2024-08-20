# SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
#
# SPDX-License-Identifier: MPL-2.0

# CMakeList.txt : CMake project for power_grid_model_io_native, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.23)

include("cmake/pgm_io_native_version.cmake")

project (power_grid_model_io_native VERSION ${PGM_IO_NATIVE_VERSION})

option(PGM_IO_ENABLE_TESTS "Enable tests" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# cmake output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(GNUInstallDirs)

add_subdirectory("power-grid-model")

# add C library
add_subdirectory("power_grid_model_io_native_c")

# dev build
if(${PGM_IO_ENABLE_DEV_BUILD})
  include(CTest)
  enable_testing()
  # get tests
  add_subdirectory("tests")
endif()

# export the power grid model io native
include("cmake/export_power_grid_model_io_native.cmake")
