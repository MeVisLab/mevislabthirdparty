# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans.errors import ConanException


class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'

    def test(self):
        self.check_license()

        cmd = "gperf.exe" if self.settings.os == "Windows" else "gperf"
        gperf = tools.which(cmd)
        if not gperf:
            raise ConanException("No instance of %s could be found on %PATH%" % cmd)

        self.output.info("using %s from: %s" % (cmd, gperf))
        self.run('%s --version' % cmd)
