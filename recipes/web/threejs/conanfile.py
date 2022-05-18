# -*- coding: utf-8 -*-
from conans import ConanFile


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    settings = None
    generate_cmake = False

    def package(self):
        self.copy("three.js", src='sources/build/', dst='web/threejs')
        self.default_package()
