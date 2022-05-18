import os

from babel import core
from babel.core import default_locale

assert core.negotiate_locale(['de_DE', 'en_US'], ['de_DE', 'de_AT']) == 'de_DE'

for value in ['C', 'C.UTF-8', 'POSIX']:
    os.environ['LANGUAGE'] = value
    assert default_locale() == 'en_US_POSIX'
