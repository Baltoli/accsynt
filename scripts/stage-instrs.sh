#!/usr/bin/env bash

if [ "$#" -ne 4 ]; then
    echo "Usage: stage-instrs.sh model dir dylib output"
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

script="get-instrs-data.sh"

echo "#!/usr/bin/env bash" > $script
echo "mkdir -p $output" >> $script
chmod +x $script

for f in ${files[@]}; do
  base=$(basename $f .props)
  echo "echo \"[$i/$n] Running $base...\""
  echo -n $model $f $dylib \
    --single --reps=1 \
    --independent=128 --memsize=50 --quiet
  echo " > $output/$base.csv"

  i=$((i+1))
done >> $script
