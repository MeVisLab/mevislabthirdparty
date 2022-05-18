import certifi
import os

assert len(certifi.where()) > 0
assert os.path.exists(certifi.where())
