# -*- coding: utf-8 -*-

from typing import Optional
from conan.tools.files import patch
from conans.errors import ConanException
from common import utils
from conans import ConanFile

class Patch(object):
    def apply_patches(self:ConanFile, base_path:str='sources', strip:int=1, fuzz:Optional[bool]=None):
        patches = self.conan_data.get('patches')
        if not patches:
            self.output.info("No applicable patches found")
            return

        entries = patches.get(self.version)
        if not entries:
            self.output.info("No applicable patches found")
            return

        for it in entries:
            if not isinstance(it, dict):
                self.output.error("Invalid patches section found.")
                raise ConanException("Invalid patches section found.")

            for key in it:
                it[key] = utils.substitute(self, it[key])

            if base_path and not 'base_path' in it:
                it['base_path'] = base_path

            if strip and not 'strip' in it:
                it['strip'] = strip

            if fuzz and not 'fuzz' in it:
                it['fuzz'] = fuzz

            self.output.info(f"Applying patch \'{it['patch_file']}\'")
            patch(self, **it)

