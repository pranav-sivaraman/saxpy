#!/bin/bash

MODELS=(SERIAL OPENMP KOKKOS RAJA)

export OMP_PROC_BIND=spread 
export OMP_PLACES=threads

for model in "${MODELS[@]}"; do
  # Create build directory based on model name
  build_dir="build_$model"

  "$build_dir/saxpy"
done
