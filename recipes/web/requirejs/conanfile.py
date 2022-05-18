# -*- coding: utf-8 -*-
from conans import ConanFile
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    settings = None
    generate_cmake = False

    def source(self):
        # require-min.js
        fileName = "require-min-%s.js" % self.version
        url = "https://requirejs.org/docs/release/%s/minified/require.js" % self.version
        sha256 = "4948c3fe4b57cd92118ec7b89deb99ff0eb2586a02c5f454df21c1ecfc144c81"
        self.download_distfile(url=url, sha256=sha256, fileName=fileName, uncompress=False)
        os.rename(fileName, "require-min.js")

        # require.js
        fileName = "require-%s.js" % self.version
        url = "https://requirejs.org/docs/release/%s/comments/require.js" % self.version
        sha256 = "9485f0917f97fcf4f63a5ea365200ffd57f123f451382a2f9a1ad2e2fd51ac9b"
        self.download_distfile(url=url, sha256=sha256, fileName=fileName, uncompress=False)
        os.rename(fileName, "require.js")

        # r.js
        fileName = "r-%s.js" % self.version
        url = "https://requirejs.org/docs/release/%s/r.js" % self.version
        sha256 = "65951f36480c17a1efe101ab673382fc435e239f51f9f7f686ea9f974c065528"
        self.download_distfile(url=url, sha256=sha256, fileName=fileName, uncompress=False)
        os.rename(fileName, "r.js")


    def package(self):
        self.copy("*.js", src='.', dst='web/%s' % self.name)
        self.default_package()
