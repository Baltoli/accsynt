#!/usr/bin/env bash

dir="$1"
shift

dylib="$1"
shift

for f in $(find $dir -name '*.props'); do
  echo $f
done
