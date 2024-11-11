# SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
#
# SPDX-License-Identifier: MPL-2.0
import pytest

from power_grid_model_io_native._core.power_grid_model_io_core import pgm_io_core
from power_grid_model_io_native._core.vnf_converter import PgmVnfConverter


def test_pgmvnfconverter_constructor_without_experimental_features():
    with pytest.raises(Exception) as e:
        _ = PgmVnfConverter("", 0)
    print(f"Raised exception: {e.type} - {e.value}")


# def test_pgmvnfconverter_constructor_with_experimental_features():
#     converter = PgmVnfConverter("", 1)
# assert converter is not None


def test_nothing():
    assert pgm_io_core.error_code() == 0
    assert pgm_io_core.error_message() == ""
