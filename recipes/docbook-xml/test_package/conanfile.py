import os
import xml.etree.ElementTree as ElementTree

from conan import ConanFile
from conan.errors import ConanException
from conan.tools.layout import basic_layout


class TestPackage(ConanFile):
    test_type = "explicit"

    def layout(self):
        basic_layout(self)

    def requirements(self):
        self.requires(self.tested_reference_str)

    def test(self):
        dependency = self.dependencies["docbook-xml"]
        dtd_folder = os.path.join(dependency.package_folder, "dtd", "docbook-xml")
        catalog = ElementTree.parse(os.path.join(dtd_folder, "catalog.xml"))
        namespace = "{urn:oasis:names:tc:entity:xmlns:xml:catalog}"
        public_id = f"-//OASIS//DTD DocBook XML V{dependency.ref.version}//EN"
        entries = [entry for entry in catalog.iter(f"{namespace}public") if entry.get("publicId") == public_id]
        if not entries:
            raise ConanException(f"catalog.xml does not map the public identifier {public_id}")
        dtd_path = os.path.join(dtd_folder, entries[0].get("uri"))
        if not os.path.isfile(dtd_path) or os.path.getsize(dtd_path) == 0:
            raise ConanException(f"missing or empty file: {dtd_path}")
