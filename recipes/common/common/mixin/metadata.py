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

        # write file
        with io.open("metadata.json", mode='w', encoding='utf8') as outfile:
            outfile.write(json.dumps(data, indent=4, ensure_ascii=False))

        self.copy("metadata.json", dst="licenses", keep_path=False)
        return os.path.join(self.package_folder, 'licenses', 'metadata.json')

