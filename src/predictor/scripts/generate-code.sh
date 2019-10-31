#!/usr/bin/env bash

vars=(
  out_num_props
)

root=$(realpath ../model)

gen_c="$root/src/generated.c"
header="$root/include/model/model.h"

rm -f "$gen_c"
rm -f "$header"

for var in "${vars[@]}"; do
  ./learn.py data.csv code "$var" \
    >   "$gen_c" \
    2>  "$header"
done
