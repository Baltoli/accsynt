#!/usr/bin/env bash

if [ "$#" -ne 4 ]; then
    echo "Usage: stage.sh model dir dylib output"
    exit 1
fi

model="$1"
shift

dir="$1"
shift

dylib="$1"
shift

output="$1"
shift

file_names=$(find $dir -name '*.props')
files=($file_names)
i=1
n=${#files[@]}

script="get-perf-data.sh"

echo "#!/usr/bin/env bash" > $script
chmod +x $script

for f in ${files[@]}; do
  base=$(basename $f .props)
  echo "echo \"[$i/$n] Running $base...\""
  echo -n $model $f $dylib \
    --linear --reps=10 \
    --step=8 --start=1 --end=3072 \
    --independent=256 --memsize=90
  echo " > $output/$base.csv"

  i=$((i+1))
done > $script
