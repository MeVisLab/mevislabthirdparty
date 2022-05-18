#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import json
import collections
import pkg_resources
import urllib.request
from datetime import date

def get_latest_spdx_tag():
    url = 'https://api.github.com/repos/spdx/license-list-data/tags'
    with urllib.request.urlopen(url) as f:
        res = f.read().decode('utf-8')
    spdx_tags = json.loads(res)
    latest_tag = '0'

    for t in spdx_tags:
        if pkg_resources.parse_version(t['name']) > pkg_resources.parse_version(latest_tag):
            latest_tag = t['name']

    print(f"using spdx tag: {latest_tag}")
    return latest_tag


def generate(ver):
    url = 'https://github.com/spdx/license-list-data/raw/{tag}/json/licenses.json'.format(tag=ver)
    with urllib.request.urlopen(url) as f:
        rawjson = json.loads(f.read().decode('utf-8'))

    licenses = {x['licenseId']: x for x in rawjson['licenses']}

    for license in licenses.values():
        del(license['seeAlso'])
        if 'isOsiApproved' not in license:
            license['isOsiApproved'] = False
        if 'isFsfLibre' not in license:
            license['isFsfLibre'] = False
        license['referenceNumber'] = int(license['referenceNumber'])


    dir = os.path.dirname(os.path.realpath('__file__'))
    with open(os.path.join(dir, 'common', 'utils', 'spdx_licenses.py'), 'w') as f:
        print("# -*- coding: utf-8 -*-", file=f)
        print("# Generated on {} for SPDX version {}\n\n".format(date.today().strftime("%d/%m/%Y"), ver), file=f)

        print("spdx_licenses = {", file=f)
        for license in collections.OrderedDict(sorted(licenses.items())):
            licenseId = licenses[license]['licenseId']
            ref = licenses[license]['referenceNumber']
            name = licenses[license]['name']
            deprecated = licenses[license]['isDeprecatedLicenseId']
            osi_approved = licenses[license]['isOsiApproved']
            fsf_libre = licenses[license]['isFsfLibre']
            details_url = licenses[license]['detailsUrl']

            print(f"  '{license.lower()}': {{ 'id': '{licenseId}', 'ref': {ref}, 'deprecated': {deprecated}, 'osi_approved': {osi_approved}, 'fsf_libre': {fsf_libre}, 'name': \"\"\"{name}\"\"\", 'details_url': '{details_url}' }},", file=f)
        print("}", file=f)

def main():
   generate(get_latest_spdx_tag())

if __name__ == '__main__':
    main()
