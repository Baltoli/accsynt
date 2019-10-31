#!/usr/bin/env bash

vars=(
  out_output_0_arg
  out_output_1_arg
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
