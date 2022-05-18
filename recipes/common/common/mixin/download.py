# -*- coding: utf-8 -*-

from typing import Optional
from conans import tools
from conans import ConanFile
from conans.errors import ConanException
from ftplib import FTP
import shutil
import os

class Download(object):
    def __ftp_upload(self:ConanFile, ftp: str, localfile: str, remotedir: str):
        # python is soooo ugly!
        # it's fine to read a variable from the outer function inside a closure
        # but it's not ok to write to it.
        closure_vars = {
            'total': os.path.getsize(localfile),
            'written': 0,
            'blocksize': 8192
        }

        def cb(block):
            def fmt_size(num, suffix='B'):
                for unit in ['','Ki','Mi','Gi','Ti','Pi','Ei','Zi']:
                    if abs(num) < 1024.0:
                        return "%3.1f%s%s" % (num, unit, suffix)
                    num /= 1024.0
                return "%.1f%s%s" % (num, 'Yi', suffix)
            closure_vars['written'] += closure_vars['blocksize']
            curr = fmt_size(closure_vars['written'] / closure_vars['total'])
            total = fmt_size(closure_vars['total'])
            self.output.rewrite_line(f'FTP upload {localfile}: {curr}/{total}')

        if remotedir != '':
            ftp.cwd(remotedir)
        with open(localfile, 'rb') as fin:
            ftp.storbinary("STOR %s" % localfile, fin, callback=cb, blocksize=closure_vars['blocksize'])
        self.output.success("File uploaded")


    def __download(self:ConanFile, url:str, sha256:str, filename:str, cache:bool):
        ftphost = os.environ.get('CONAN_DISTFILES_FTP_HOST')
        ftpdir = os.environ.get('CONAN_DISTFILES_FTP_DIR', 'distfiles')
        ftpuser = os.environ.get('CONAN_DISTFILES_FTP_USERNAME', 'anonymous')
        ftppwd = os.environ.get('CONAN_DISTFILES_FTP_PASSWORD', '')

        if cache and ftphost != None:
            info = '' if ftpuser == '' else (" (user: '{}', using password: {})".format(ftpuser, "no" if ftppwd == '' else "yes"))
            self.output.info(f"Downloading {self.name} file {filename} from FTP server {ftphost}{info}")

            try:
                tools.ftp_download(ftphost, f"{ftpdir}/{filename}", login=ftpuser, password=ftppwd)
            except:
                self.output.info(f"Failed to download '{ftpdir}/{filename}' from FTP server")

            if os.path.exists(filename) and sha256:
                try:
                    tools.check_sha256(filename, sha256)
                except:
                    self.output.error(f'FTP download {filename}: invalid checksum {sha256}!')
                    os.remove(filename)

                    if os.environ.get('CONAN_DISTFILES_FTP_UPLOAD', 0).lower() in ['y', 'yes', '1']:
                        try:
                            with FTP(host=ftphost, user=ftpuser, passwd=ftppwd) as ftp:
                                if ftpdir != '':
                                    ftp.cwd(ftpdir)
                                ftp.delete(filename)
                        except:
                            pass

        if not os.path.exists(filename):
            self.output.info(f"Downloading {self.name} file {filename} from {url}")
            tmpfile = filename + ".__download__"
            if os.path.exists(tmpfile):
                if sha256:
                    try:
                        tools.check_sha256(tmpfile, sha256)
                    except:
                        os.remove(tmpfile)
                else:
                    os.remove(tmpfile)

            if not os.path.exists(tmpfile):
                tools.download(url=url, filename=tmpfile)

            if not os.path.exists(tmpfile):
                raise ConanException("File '%s' not found" % filename)

            if sha256:
                tools.check_sha256(tmpfile, sha256)

            os.rename(tmpfile, filename)

            if cache and ftphost is not None and os.environ.get('CONAN_DISTFILES_FTP_UPLOAD', 0).lower() in ['y', 'yes', '1']:
                self.output.info(f"Try to uploading {self.name} file {filename} to FTP")
                try:
                    with FTP(host=ftphost, user=ftpuser, passwd=ftppwd) as ftp:
                        self.__ftp_upload(ftp, filename, ftpdir)
                except:
                    self.output.info("Failed to upload to FTP server")


    def __uncompress(self: ConanFile, fileName: str, baseFolder:Optional[str]=None) -> None:
        fileName = os.path.abspath(fileName)
        if baseFolder is not None:
            baseFolder = os.path.join(os.getcwd(), baseFolder)
            os.makedirs(baseFolder, exist_ok=True)

        with tools.chdir(baseFolder) if baseFolder is not None else tools.no_op():
            tools.unzip(fileName)


    def download_distfile(self: ConanFile, url:str, fileName:str, sha256:str, baseFolder:Optional[str]=None, uncompress:bool=True, cache:bool=True):
        if not url:
            raise ConanException("url argument is required")
        if not fileName:
            raise ConanException("fileName argument is required")

        distdir = os.environ.get('CONAN_DISTDIR')
        if distdir != None:
            try:
                os.makedirs(distdir, exist_ok=True)
            except:
                self.output.warning(f"Failed to create CONAN_DISTDIR directory 'distdir'.")

        if distdir != None and os.path.exists(distdir):
            file = os.path.join(distdir, fileName)
            if os.path.exists(file):
                self.output.info(f"Skipping download. Using local cached '{file}'")
                if sha256:
                    tools.check_sha256(file, sha256)
            else:
                self.__download(url=url, sha256=sha256, filename=file, cache=cache)

            if uncompress:
                self.output.info(f"Uncompressing file '{file}'")
                self.__uncompress(file, baseFolder=baseFolder)
            else:
                self.output.info(f"Copying file '{file}' to source folder")
                if baseFolder is None:
                    baseFolder = self.source_folder
                else:
                    baseFolder = os.path.join(self.source_folder, baseFolder)
                    os.makedirs(baseFolder, exist_ok=True)

                shutil.copy2(file, baseFolder)
        else:
            self.__download(url=url, sha256=sha256, filename=fileName, cache=cache)

            if uncompress:
                self.output.info("Uncompressing file '{}'".format(fileName))
                self.__uncompress(fileName, baseFolder=baseFolder)
                os.unlink(fileName)
