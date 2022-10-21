import pyodbc
import sys

try:
    print(f"pyodbc version: {list(map(int, (pyodbc.version.split('.'))))}")
except:
    print(f"invalid pyodbc version: {pyodbc.version}", file=sys.stderr)
    sys.exit(1)
