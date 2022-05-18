from pydicom import dcmread
from pydicom.data import get_testdata_file

path = get_testdata_file("CT_small.dcm")

ds = dcmread(path)

assert len(ds.PixelData) == 32768
