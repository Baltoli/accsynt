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

script="get-perf-data.sh"

echo "#!/usr/bin/env bash" >> $script
echo "pids=()" >> $script

for f in ${files[@]}; do
  base=$(basename $f .props)
#   echo "echo \"[$i/$n] Running $base...\""
  echo -n $model $f $dylib \
    --linear --reps=10 \
    --step=8 --start=0 --end=2048 \
    --independent=512 --memsize=120
  echo " > $output/$base.csv &"
  echo 'pids+=($!)'
done >> $script

echo 'wait ${pids[@]}' >> $script

chmod +x $script
