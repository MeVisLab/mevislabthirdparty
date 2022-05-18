import numpy as np

a = np.arange(15).reshape(3, 5)

assert a.size == 15
assert a.ndim == 2
