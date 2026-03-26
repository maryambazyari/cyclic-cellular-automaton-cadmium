#!/bin/bash
set -e

if [ -z "$CADMIUM_V2_DIR" ]; then
  echo "ERROR: CADMIUM_V2_DIR is not set."
  exit 1
fi

if [ -z "$JSON_DIR" ]; then
  echo "ERROR: JSON_DIR is not set."
  exit 1
fi

if [ -z "$BOOST_DIR" ]; then
  echo "ERROR: BOOST_DIR is not set."
  exit 1
fi

rm -rf out
mkdir -p out
cd out

cmake -G Ninja \
  -DCADMIUM_V2_DIR="$CADMIUM_V2_DIR" \
  -DJSON_DIR="$JSON_DIR" \
  -DBOOST_DIR="$BOOST_DIR" \
  ..

cmake --build .

./main_cyclic ../cyclic_config_wrapped.json 50

mkdir -p ../logs
cp cyclic_grid_log.csv ../logs/cyclic_wrapped_log.csv