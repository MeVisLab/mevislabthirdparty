# -*- coding: utf-8 -*-


import io
import os
import shutil
import json
from datetime import datetime
from conans.errors import ConanInvalidConfiguration

from conans import ConanFile
from common.utils import spdx_licenses, other_licenses

class Metadata(object):
    def install_metadata(self:ConanFile):
        licenseFile = self.copy_license_file()
        mlinfoFile = self.create_metadata_file()
        if licenseFile or mlinfoFile:
            # Also copy files for direct consumption by MeVisLab
            thirdPartyInfoDir = os.path.join(self.package_folder, 'MeVis/ThirdParty/ThirdPartyInformation', self.name)
            os.makedirs(thirdPartyInfoDir, exist_ok=True)
            if licenseFile:
                shutil.copy2(src=licenseFile, dst=os.path.join(thirdPartyInfoDir, f"{self.name}.license"))
            if mlinfoFile:
                shutil.copy2(src=mlinfoFile, dst=os.path.join(thirdPartyInfoDir, f"{self.name}.mlinfo"))


    def create_metadata_file(self:ConanFile):
        # collect metadata.json informations
        data = {}
        data['id'] = self.name.lower()
        data['name'] = self.name
        data['display_name'] = self.name if self.display_name == None else self.display_name
        data['version'] = self.version
        if self.upstream_version:
            data['upstream_version'] = self.upstream_version
        data['license'] = self.license
        data['description'] = self.description
        data['homepage'] = self.homepage

        # TODO MeVisLab shows all licenses anyway.
        #      However, some customers use this information for their OTS monitoring.
        #      So when we provide that information, we have to be absolutely sure that we don't have false negatives.
        data['aboutNeeded'] = True

        lic = spdx_licenses.get(data['license'].lower(), other_licenses.get(data['license'].lower()))
        if not lic:
            print("\n\n")
            self.output.error("Invalid license: '" + self.license + "'")
            print("Please use a SPDX license identifier (https://spdx.org/licenses/).")
            raise ConanInvalidConfiguration("Unknown license type '" + data['license'] + "'")
        data['license_name'] = lic['name']

        # collect some build related informations
        data['build'] = {}
        data['build']['timestamp'] = int(datetime.now().timestamp())
        data['build']['duration'] = int(datetime.now().timestamp()) - self._timestamp
        data['build']['os'] = self.settings.get_safe("os")
        data['build']['arch'] = self.settings.get_safe("arch")
        data['build']['build_type'] = self.settings.get_safe("build_type")
        data['build']['compiler'] = self.settings.get_safe("compiler")
        data['build']['compiler_version'] = self.settings.get_safe("compiler.version")
        if self.settings.get_safe("compiler.runtime"):
            data['build']['compiler_runtime'] = self.settings.get_safe("compiler.runtime")
        if self.settings.get_safe("compiler.libcxx"):
            data['build']['compiler_libcxx'] = self.settings.get_safe("compiler.libcxx")

        if self.deps_cpp_info.deps:
            data['build']['dependencies'] = []
            for dependency in self.deps_cpp_info.deps:
                data['build']['dependencies'].append({ 'id': dependency, 'version': self.deps_cpp_info[dependency].version })

        # jenkins ci environment variables
        ci = {}
        if os.environ.get("BRANCH_NAME"):
            ci['branch_name'] = os.environ.get("BRANCH_NAME")

        if os.environ.get("BUILD_NUMBER"):
            ci['build_number'] = os.environ.get("BUILD_NUMBER")

        if os.environ.get("NODE_NAME"):
            ci['node_name'] = os.environ.get("NODE_NAME")

        if os.environ.get("CHANGE_ID"):
            ci['change_id'] = os.environ.get("CHANGE_ID")

        if os.environ.get("TAG_NAME"):
            ci['tag_name'] = os.environ.get("TAG_NAME")

        if os.environ.get("GIT_COMMIT"):
            ci['git_commit'] = os.environ.get("GIT_COMMIT")

        if os.environ.get("GIT_BRANCH"):
            ci['git_branch'] = os.environ.get("GIT_BRANCH")

        if ci:
            data['build']['ci'] = ci

        # write file
        with io.open("metadata.json", mode='w', encoding='utf8') as outfile:
            outfile.write(json.dumps(data, indent=4, ensure_ascii=False))

        self.copy("metadata.json", dst="licenses", keep_path=False)
        return os.path.join(self.package_folder, 'licenses', 'metadata.json')

