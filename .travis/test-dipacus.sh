#!/bin/sh

#SCRIPT_DIR defined in the docker image dipacus:env

$SCRIPT_DIR/build-dipacus.sh
ls build -la
./build/lab/test/base/test-base output
./build/lab/test/components/test-components output
./build/lab/test/derivates/test-derivates output


cat output/test/base/log.txt
cat output/test/components/log.txt
cat output/test/derivates/log.txt
