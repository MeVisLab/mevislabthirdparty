#include <Python.h>
#include <stdio.h>

void run(const char *command)
{
    printf("testing '%s' ", command);
    if(PyRun_SimpleString(command) != 0) {
        printf("[failed]\n");
        exit(1);
    }
    printf("[ok]\n");
}

int main() {
    Py_Initialize();

    //run("import lzma");
    run("import argparse");
    run("import asyncio");
    run("import base64");
    run("import bz2");
    run("import calendar");
    run("import cmath");
    run("import codecs");
    run("import ctypes");
    run("import dataclasses");
    run("import datetime");
    run("import decimal");
    run("import hashlib");
    run("import json");
    run("import multiprocessing");
    run("import pyexpat");
    run("import queue");
    run("import select");
    run("import socket");
    run("import sqlite3");
    run("import ssl");
    run("import threading");
    run("import typing");
    run("import urllib");
    run("import uuid");
    run("import xml.etree.ElementTree");
    run("import xml.parsers.expat");
    run("import xml");
    run("import zoneinfo");

    // testing 3.9.11-recursive_future_repr.patch:
    run(
"import asyncio\n"
"import functools\n"
"import sys\n"
"sys.setrecursionlimit(3000)\n"
"fut = asyncio.Future()\n"
"def done_cb(arg):\n"
"  pass\n"
"fut.add_done_callback(functools.partial(done_cb, fut))\n"
"print(repr(fut))");

	Py_Finalize();

	return 0;
}
