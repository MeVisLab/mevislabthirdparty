#include <Python.h>
#include <stdio.h>

void run_stmt(const char *stmt)
{
    printf("testing '%s' ", stmt);
    if(PyRun_SimpleString(stmt) != 0) {
        printf("[failed]\n");
        exit(1);
    }
    printf("[ok]\n");
}

void run_program(const char *desc, const char *prog)
{
    printf("testing '%s' ", desc);
    if(PyRun_SimpleString(prog) != 0) {
        printf("[failed]\n");
        exit(1);
    }
    printf("[ok]\n");
}

int main() {
    Py_Initialize();

    //run_stmt("import lzma");
    run_stmt("import argparse");
    run_stmt("import asyncio");
    run_stmt("import base64");
    run_stmt("import bz2");
    run_stmt("import calendar");
    run_stmt("import cmath");
    run_stmt("import codecs");
    run_stmt("import ctypes");
    run_stmt("import dataclasses");
    run_stmt("import datetime");
    run_stmt("import decimal");
    run_stmt("import functools");
    run_stmt("import hashlib");
    run_stmt("import json");
    run_stmt("import multiprocessing");
    run_stmt("import pyexpat");
    run_stmt("import queue");
    run_stmt("import select");
    run_stmt("import socket");
    run_stmt("import sqlite3");
    run_stmt("import ssl");
    run_stmt("import sys");
    run_stmt("import threading");
    run_stmt("import typing");
    run_stmt("import urllib");
    run_stmt("import uuid");
    run_stmt("import xml.etree.ElementTree");
    run_stmt("import xml.parsers.expat");
    run_stmt("import xml");
    run_stmt("import zoneinfo");

    run_program("recursice_future_repr.patch",
        "import asyncio\n"
        "import functools\n"
        "import sys\n"
        "sys.setrecursionlimit(3000)\n"
        "fut = asyncio.Future()\n"
        "def done_cb(arg):\n"
        "  pass\n"
        "fut.add_done_callback(functools.partial(done_cb, fut))\n"
        "assert(repr(fut) == \"<Future pending cb=[done_cb(<Future ... [recursion]>)() at <string>:6]>\")\n"
    );

	Py_Finalize();

	return 0;
}
