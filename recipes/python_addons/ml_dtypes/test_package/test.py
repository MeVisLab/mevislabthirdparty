import numpy

import ml_dtypes

values = numpy.array([0.5, -2.0], dtype=ml_dtypes.bfloat16)
assert values.astype(numpy.float32).tolist() == [0.5, -2.0]
assert ml_dtypes.finfo(ml_dtypes.float8_e4m3fn).max == 448

print(f"ml_dtypes {ml_dtypes.__version__}")
