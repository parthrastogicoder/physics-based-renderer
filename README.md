# Physics-Based Renderer

A physics-based rendering (PBR) engine using C++ and OpenGL that simulates realistic light interactions with materials.

## Description

This project implements a PBR engine with core concepts including:
- Energy conservation
- Fresnel effect
- Microfacet theory
- Metallic workflow
- Image-Based Lighting (IBL)

The renderer uses the Cook-Torrance BRDF with GGX normal distribution, Smith geometry function, and Schlick-Fresnel approximation to achieve physically accurate rendering.

## Features

- Physically-based material system
- Real-time rendering with OpenGL
- Cook-Torrance specular BRDF
- Image-Based Lighting for environment reflections
- Normal mapping support
- Basic primitive generation (sphere, cube, plane)
- Camera controls for scene navigation

## Getting Started

### Prerequisites

The following dependencies are required:
- C++ compiler (GCC/Clang)
- CMake (version 3.10 or higher)
- GLFW
- GLEW
- GLM

### Installation

1. Clone the repository:
```
git clone https://github.com/parthrastogicoder/physics-based-renderer.git
cd physics-based-renderer
```

2. Install dependencies:
```
./install_dependencies.sh
```

3. Build the project:
```
./build.sh
```

4. Run the executable:
```
./build/PhysicsBasedRenderer
```

## Controls

- **W/A/S/D**: Move the camera
- **Space/Ctrl**: Move up/down
- **Mouse**: Look around
- **Mouse Scroll**: Zoom in/out
- **Esc**: Exit the application

## Project Structure

```
.
├── CMakeLists.txt          # CMake build configuration
├── build.sh                # Build script
├── include/                # Header files
│   ├── Camera.h            # Camera system
│   ├── IBL.h               # Image-Based Lighting
│   ├── Material.h          # PBR material system
│   ├── Mesh.h              # 3D mesh handling
│   ├── Model.h             # Model loading and creation
│   ├── Shader.h            # Shader management
│   └── TextureLoader.h     # Texture loading utilities
├── resources/              # Resource files
│   ├── models/             # 3D model files
│   └── textures/           # Texture files
├── shaders/                # GLSL shader files
│   ├── basic.fs            # Basic fragment shader
│   ├── basic.vs            # Basic vertex shader
│   ├── pbr.fs              # PBR fragment shader
│   ├── pbr.vs              # PBR vertex shader
│   ├── skybox.fs           # Skybox fragment shader
│   └── skybox.vs           # Skybox vertex shader
└── src/                    # Source files
    ├── Camera.cpp          # Camera implementation
    ├── IBL.cpp             # IBL implementation
    ├── Material.cpp        # Material implementation
    ├── Mesh.cpp            # Mesh implementation
    ├── Model.cpp           # Model implementation
    ├── Shader.cpp          # Shader implementation
    ├── TextureLoader.cpp   # Texture loader implementation
    └── main.cpp            # Main application entry point
```

## Future Enhancements

- Shadow mapping
- Advanced environment mapping
- Model loading from files (using Assimp)
- Post-processing effects
- Performance optimizations
