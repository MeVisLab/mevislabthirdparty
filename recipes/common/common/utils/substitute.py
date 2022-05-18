
# -*- coding: utf-8 -*-

import string
from typing import Optional

from conans import ConanFile
from conans.client.tools.version import Version


def substitute(conanfile: ConanFile, value: Optional[str], **kwargs) -> Optional[str]:
    if value is None:
        return None

    ver = Version(conanfile.version)
    t = string.Template(value)

    return t.safe_substitute(
        name=conanfile.name,
        display_name=conanfile.display_name,
        version=conanfile.version,
        version_major=ver.major,
        version_minor=ver.minor,
        version_patch=ver.patch,
        homepage=conanfile.homepage,
        upstream_version=conanfile.upstream_version,
        **kwargs
    )
