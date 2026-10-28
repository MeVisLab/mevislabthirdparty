import os
from pathlib import Path

import numpy as np

a = np.arange(15).reshape(3, 5)

if a.size != 15:
    raise SystemExit(f"Expected 15 array elements, got {a.size}")

if a.ndim != 2:
    raise SystemExit(f"Expected a 2-dimensional array, got {a.ndim} dimensions")

test_data_value = os.environ.get("CONAN_TEST_DATA")
if not test_data_value:
    raise SystemExit("CONAN_TEST_DATA is not set")

test_data = Path(test_data_value)
if not test_data.is_file():
    raise SystemExit(f"Test data file does not exist: {test_data}")

if not os.access(test_data, os.R_OK):
    raise SystemExit(f"Test data file is not readable: {test_data}")

try:
    np.load(test_data)
except Exception as error:
    raise SystemExit(f"Could not load test data: {error}") from error

print("success")
