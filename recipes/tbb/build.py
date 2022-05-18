#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from cpt.packager import ConanMultiPackager

if __name__ == "__main__":
  builder = ConanMultiPackager()
  builder.add_common_builds(pure_c=False)

  # remove older libcxx (pre C++11)
  builder.remove_build_if(lambda build: build.settings.get("compiler.libcxx", "") == "libstdc++")

  builder.run()

