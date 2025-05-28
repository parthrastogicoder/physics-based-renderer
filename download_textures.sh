#!/bin/bash

# Create skybox directories
mkdir -p "/home/parth/Desktop/Rendering engine /resources/textures/skybox"
mkdir -p "/home/parth/Desktop/Rendering engine /resources/textures/hdr"

# Download sample skybox textures
cd "/home/parth/Desktop/Rendering engine /resources/textures/skybox"

# Download a simple skybox texture set
echo "Downloading sample skybox textures..."
wget -O right.jpg "https://learnopengl.com/img/textures/skybox/right.jpg"
wget -O left.jpg "https://learnopengl.com/img/textures/skybox/left.jpg"
wget -O top.jpg "https://learnopengl.com/img/textures/skybox/top.jpg"
wget -O bottom.jpg "https://learnopengl.com/img/textures/skybox/bottom.jpg"
wget -O front.jpg "https://learnopengl.com/img/textures/skybox/front.jpg"
wget -O back.jpg "https://learnopengl.com/img/textures/skybox/back.jpg"

# Download a sample HDR image
cd "/home/parth/Desktop/Rendering engine /resources/textures/hdr"
echo "Downloading sample HDR environment map..."
wget -O environment.hdr "https://learnopengl.com/img/textures/hdr/newport_loft.hdr"

echo "Sample textures downloaded successfully!"
