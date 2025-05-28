#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build

# Navigate to build directory
cd build

# Configure using CMake
cmake ..

# Build the project
cmake --build . -- -j$(nproc)

echo "Build completed. Executable is in build directory."
