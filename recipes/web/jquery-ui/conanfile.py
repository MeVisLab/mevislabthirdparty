# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
import shutil

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    settings = None
    generate_cmake = False

    def source(self):
        fileName = "jquery-ui-%s.zip" % self.version
        url = "https://jqueryui.com/resources/download/%s" % fileName
        sha256 = "5F063F91DF85431E3FEA84F5D5709726D6DCD15EE4BF86B0E9A4B134912A5EFD"
        self.download_distfile(url=url, sha256=sha256, fileName=fileName)

        fileName = "jquery-ui-themes-%s.zip" % self.version
        url = "https://jqueryui.com/resources/download/%s" % fileName
        sha256 = "45B4EACD4B033539538CD8996B8A02670B3B429EFC2044840DD20A3FAC9E1FED"
        self.download_distfile(url=url, sha256=sha256, fileName=fileName)

    def build(self):
        shutil.copytree("jquery-ui-themes-%s" % self.version, "sources", dirs_exist_ok=True)
        shutil.copytree("jquery-ui-%s" % self.version, "sources", dirs_exist_ok=True)
        shutil.move('sources/LICENSE.txt', 'sources/LICENSE')

    def package(self):
        self.copy("*", src='sources', dst=f"web/{self.name}", excludes='sources/external/*')
        self.default_package()
