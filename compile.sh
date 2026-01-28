#!/bin/bash 
LSMS_ROOT=$(pwd)

rm -Rf build
mkdir build
cd build

module reset

module load amd/6.4.1 \
    rocm/6.4.1 \
    PrgEnv-amd

module load cray-hdf5-parallel
export ROCM_PATH=/opt/rocm-6.4.1

module list

echo "HDF5_DIR=$HDF5_DIR"
echo "ROCM_PATH=$ROCM_PATH"

cmake -DCMAKE_TOOLCHAIN_FILE=$PWD/../toolchain/frontier-rocm-hip.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER_WORKS=1 \
    -DCMAKE_CXX_COMPILER_WORKS=1 \
    -DCMAKE_C_COMPILER_ID=Clang \
    -DCMAKE_CXX_COMPILER_ID=Clang \
    -DCMAKE_THREAD_LIBS_INIT="-pthread" \
    -DCMAKE_USE_PTHREADS_INIT=1 \
    -DOpenMP_C_FLAGS="-fopenmp" \
    -DOpenMP_CXX_FLAGS="-fopenmp" \
    -DOpenMP_C_LIB_NAMES="omp" \
    -DOpenMP_CXX_LIB_NAMES="omp" \
    -DOpenMP_omp_LIBRARY=$ROCM_PATH/llvm/lib/libomp.so \
    -DHDF5_LIBRARIES=$HDF5_DIR/lib/ \
    -DHDF5_INCLUDE_DIRS=$HDF5_DIR/include \
    -DHDF5_C_LIBRARY=$HDF5_DIR/lib/libhdf5.so \
    -DHDF5_HL_LIBRARY=$HDF5_DIR/lib/libhdf5_hl.so \
    -DHDF5_PREFER_PARALLEL=ON \
    ..

gmake -j16