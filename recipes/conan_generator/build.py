#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from cpt.packager import ConanMultiPackager

if __name__ == "__main__":
    builder = ConanMultiPackager()
    builder.add()
    builder.run()
