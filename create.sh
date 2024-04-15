#!/bin/bash

MODELS=(SERIAL OPENMP KOKKOS RAJA)

# Loop through each model
for model in "${MODELS[@]}"; do
  # Create build directory based on model name
  build_dir="build_$model"

  # Run cmake with build directory, model flag, and source directory
  cmake -B "$build_dir" -DMODEL="$model"

  # Build the project (replace 'make' with your actual build command)
  cmake --build "$build_dir"

done

echo "Build completed for all models."
