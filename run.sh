#!/bin/bash

# Print header
echo "==============================================="
echo "Physics-Based Renderer - Runner Script"
echo "==============================================="

# Function to check if a directory exists
check_dir() {
    if [ ! -d "$1" ]; then
        echo "ERROR: Directory $1 does not exist!"
        return 1
    fi
    return 0
}

# Function to check if a file exists
check_file() {
    if [ ! -f "$1" ]; then
        echo "ERROR: File $1 does not exist!"
        return 1
    fi
    return 0
}

# Check directories and files
echo "Checking project structure..."
check_dir "include" || exit 1
check_dir "src" || exit 1
check_dir "shaders" || exit 1
check_dir "resources" || exit 1
check_dir "resources/textures" || exit 1
check_dir "resources/textures/skybox" || exit 1
check_file "CMakeLists.txt" || exit 1
check_file "build.sh" || exit 1

# Check if build directory exists
if [ ! -d "build" ]; then
    echo "Build directory not found. Creating and building project..."
    ./build.sh
else
    echo "Build directory found. Do you want to rebuild? (y/n)"
    read -r answer
    if [ "$answer" = "y" ]; then
        echo "Rebuilding project..."
        rm -rf build
        ./build.sh
    fi
fi

# Check if executable exists
if [ ! -f "build/PhysicsBasedRenderer" ]; then
    echo "ERROR: Executable not found. Build may have failed."
    exit 1
fi

# Check if skybox textures exist
skybox_count=$(ls resources/textures/skybox/*.jpg 2>/dev/null | wc -l)
if [ "$skybox_count" -lt 6 ]; then
    echo "Warning: Skybox textures not found or incomplete."
    echo "Do you want to download sample textures? (y/n)"
    read -r answer
    if [ "$answer" = "y" ]; then
        echo "Downloading sample textures..."
        ./download_textures.sh
    fi
fi

# Run the renderer
echo "==============================================="
echo "Running Physics-Based Renderer..."
echo "Controls:"
echo "  W/A/S/D: Move camera"
echo "  Space/Ctrl: Move up/down"
echo "  Mouse: Look around"
echo "  Mouse Scroll: Zoom in/out"
echo "  Esc: Exit"
echo "==============================================="

cd build && ./PhysicsBasedRenderer
