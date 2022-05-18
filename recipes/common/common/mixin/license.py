# -*- coding: utf-8 -*-

import os
import shutil
from conans import ConanFile

class License(object):
    def find_license_file(self:ConanFile):
        checkFiles = []
        for i in ["LICENSE", "License", "COPYING", "COPYRIGHT", "Copyright", "COPYING.BSD", "COPYING.LIB"]:
            checkFiles.append(os.path.join('sources', i))
            checkFiles.append(os.path.join('s', i))
            checkFiles.append(os.path.join('sources', f"{i}.md"))
            checkFiles.append(os.path.join('sources', f"{i}.rst"))
            checkFiles.append(os.path.join('sources', f"{i}.txt"))
            checkFiles.append(os.path.join('sources', f"{i}.TXT"))
            checkFiles.append(i)
            checkFiles.append(f"{i}.md")
            checkFiles.append(f"{i}.rst")
            checkFiles.append(f"{i}.txt")
            checkFiles.append(f"{i}.TXT")

        for d in [ self.build_folder, self.source_folder ]:
            for l in checkFiles:
                fullPath = os.path.join(d, l)
                if os.path.isfile(fullPath):
                    return fullPath

        return None

    def copy_license_file(self:ConanFile):
        # find and copy the license file if not already available
        targetPath = os.path.join(self.package_folder, 'licenses', 'LICENSE')
        if not os.path.isfile(targetPath):
            sourcePath = self.find_license_file()
            if sourcePath:
                if not os.path.exists(os.path.join(self.package_folder, "licenses")):
                    os.mkdir(os.path.join(self.package_folder, "licenses"))
                try:
                    shutil.copy2(src=sourcePath, dst=targetPath)
                    self.output.success("LICENSE file '%s' found." % sourcePath)
                    return targetPath
                except:
                    self.output.warn("Failed to copy '%s'." % sourcePath)

            # check that we have a license file now
            self.sanitize_package_contains_license()
        return targetPath if os.path.isfile(targetPath) else None
