#!/usr/bin/env bash

readonly EVO_BASENAME="appframework"

function help() {
cat<<EOF
Please execute this shell script from the root directory of "$EVO_BASENAME".
EOF
exit 1
}

EVO_WORKDIR=$(pwd)
current_basename=`basename $EVO_WORKDIR`
test $current_basename != $EVO_BASENAME && help

time_stamp=`date`
rm -rf ./../build-Evo*
rm -rf out
mkdir -p out/lib
mkdir -p out/bin
mkdir -p out/intermediates
echo $time_stamp > out/.evo
echo $time_stamp > out/lib/.evo
echo $time_stamp > out/bin/.evo
echo $time_stamp > out/intermediates/.evo
echo $time_stamp

echo "~~DONE~~"
