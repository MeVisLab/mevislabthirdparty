#include <Python.h>

void run(const char *command)
{
    if(PyRun_SimpleString(command) != 0) {
        exit(1);
    }
}

int main() {
    Py_Initialize();

    run("import datetime");
    run("import bz2");
    run("import ctypes");
    run("import decimal");
    run("import xml.etree.ElementTree");
    run("import hashlib");
    //run("import lzma");
    run("import multiprocessing");
    run("import pyexpat");
    run("import sqlite3");
    run("import ssl");
    run("import uuid");
    run("import argparse");
    run("import calendar");
    run("import cmath");
    run("import urllib");
    run("import xml");
    run("import json");
    run("import codecs");

	Py_Finalize();

	return 0;
}
