#!/bin/bash

# SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
#
# SPDX-License-Identifier: MPL-2.0

set -e

usage() {
  echo "Usage: $0 -p <preset> [-i]" 1>&2
  echo "  -i option to install package"
  cmake --list-presets
  exit 1
}

while getopts "p::i" flag; do
  case "${flag}" in
    p)
      PRESET=${OPTARG}
    ;;
    i) INSTALL=1;;
    *) usage ;;
  esac
done

if [ -z "${PRESET}" ] ; then
  usage
fi

echo "PRESET = ${PRESET}"
echo "INSTALL = ${INSTALL}"

BUILD_DIR=cpp_build/${PRESET}
INSTALL_DIR=install/${PRESET}
echo "Build dir: ${BUILD_DIR}"
echo "Install dir: ${INSTALL_DIR}"

rm -rf ${BUILD_DIR}/

# generate
cmake --preset ${PRESET}

# build
cmake --build --preset ${PRESET} --verbose -j1

# test
ctest --preset ${PRESET} --output-on-failure

# install
if [[ ${INSTALL} ]]; then
  cmake --build --preset ${PRESET} --target install
fi
