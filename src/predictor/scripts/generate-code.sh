#!/usr/bin/env bash

vars=(
  out_num_props
  out_num_sizes
  out_num_outputs
)

root=$(realpath ..)

gen_c="$root/src/generated.c"
header="$root/src/internal.h"

rm -f "$gen_c"
rm -f "$header"

./names.py names.csv \
    >>   "$gen_c" \
   2>>   "$header"

for var in "${vars[@]}"; do
  ./learn.py data.csv code "$var" \
    >>   "$gen_c" \
   2>>   "$header"
done
