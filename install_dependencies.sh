#!/bin/bash

# Install required dependencies
echo "Installing required dependencies..."
sudo apt-get update
sudo apt-get install -y cmake g++ libglew-dev libglfw3-dev libglm-dev

# Install stb_image
echo "Installing stb_image header..."
mkdir -p temp
cd temp
wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
sudo mkdir -p /usr/local/include/stb
sudo cp stb_image.h /usr/local/include/stb/
cd ..
rm -rf temp

# Create local include directory for stb (as a fallback)
echo "Creating local include directory for stb..."
mkdir -p "/home/parth/Desktop/Rendering engine /include/stb"
wget -O "/home/parth/Desktop/Rendering engine /include/stb/stb_image.h" https://raw.githubusercontent.com/nothings/stb/master/stb_image.h

echo "Dependencies installed successfully!"
