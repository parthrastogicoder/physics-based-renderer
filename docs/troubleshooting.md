# Troubleshooting Guide

This guide provides solutions for common issues that may occur with the Physics-Based Renderer.

## Compilation Issues

### Missing Libraries

**Issue**: Errors about missing libraries during compilation.

**Solution**:
```bash
# Install required dependencies
sudo apt-get update
sudo apt-get install -y cmake g++ libglew-dev libglfw3-dev libglm-dev
```

### STB Image Header Not Found

**Issue**: Compilation error about `stb_image.h` not being found.

**Solution**:
```bash
# Run the dependency installation script
./install_dependencies.sh

# If the issue persists, try:
mkdir -p include/stb
wget -O include/stb/stb_image.h https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
```

### OpenGL Version Issues

**Issue**: Error about unsupported OpenGL version.

**Solution**:
Check your GPU driver and update it if necessary. The engine requires OpenGL 3.3 or higher.

## Runtime Issues

### Blank Screen / Crashes

**Issue**: Application shows a blank screen or crashes upon launch.

**Solution**:
1. Check if your graphics driver supports OpenGL 3.3+
2. Ensure all shader files are in the correct location
3. Verify textures are properly loaded

```bash
# Check OpenGL version
glxinfo | grep "OpenGL version"
```

### Missing Textures

**Issue**: Textures not appearing or showing as pink/black.

**Solution**:
```bash
# Download sample textures
./download_textures.sh
```

### Black Skybox

**Issue**: Skybox appears black or is missing.

**Solution**:
1. Verify skybox textures exist in `resources/textures/skybox/`
2. Check if cubemap loading is working properly
3. Modify the `IBL::EquirectangularToCubemap` function to use a fallback color if loading fails

## Performance Issues

### Low FPS

**Issue**: Renderer runs at low framerates.

**Solution**:
1. Reduce resolution in `main.cpp` by changing SCR_WIDTH and SCR_HEIGHT
2. Simplify geometry by reducing segments in sphere models
3. Use simpler shaders for testing

## Debug Mode

To enable debug output, you can modify the `main.cpp` file to include OpenGL debug callbacks:

```cpp
// Add to the top of main.cpp
void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
                            GLsizei length, const char *message, const void *userParam) {
    // Ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 
    
    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;
    
    switch (source) {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;
    
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;
    
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}

// Add after GLEW initialization in main()
glEnable(GL_DEBUG_OUTPUT);
glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
glDebugMessageCallback(glDebugOutput, nullptr);
glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
```

## Environment Variables

You can set these environment variables to help with debugging:

```bash
# Force dedicated GPU on hybrid systems
export DRI_PRIME=1

# Enable OpenGL debugging
export MESA_DEBUG=1

# Set higher verbosity for GLFW
export GLFW_DEBUG=1
```
