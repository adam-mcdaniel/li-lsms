#!/bin/bash

LSMS_DIR=$(pwd)

source ../setup-run-env.sh
if [ -f ../profiler-injector.sh ]; then
    source ../profiler-injector.sh
fi

cd $LSMS_DIR/FePt/

srun -t10 -A csc688 -N1 $LSMS_DIR/build/bin/lsms i_lsms_express_gpu