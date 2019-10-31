#!/usr/bin/env python

import sys
import pandas as pd

def func_begin():
    return """#include <string.h>
int map_name(char const* str) {
"""

def func_end():
    return "  return -1;\n}";

def header():
    return "int map_name(char const* str);"

def main(args):
    name_dict = pd.read_csv(args[0]).set_index('name').to_dict()['index']
    code = ""
    for key in name_dict:
        code += '  if (strcmp(str, "{}") == 0) {{ return {}; }}\n'.format(key, name_dict[key])
    print(func_begin() + code + func_end(), file=sys.stdout)
    print(header(), file=sys.stderr)

if __name__ == "__main__":
    main(sys.argv[1:])
