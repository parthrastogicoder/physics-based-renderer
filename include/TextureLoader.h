#pragma once

#include <string>
#include <GL/glew.h>

class TextureLoader {
public:
    // Load a 2D texture from a file
    static unsigned int LoadTexture(const char* path, bool gamma = false);
    
    // Load a cubemap texture from 6 individual files
    static unsigned int LoadCubemap(const std::vector<std::string>& faces);
    
    // Generate an empty HDR texture
    static unsigned int CreateHDRTexture(unsigned int width, unsigned int height);
    
    // Generate an empty cubemap texture
    static unsigned int CreateCubemap(unsigned int width, unsigned int height);
};
