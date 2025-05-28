#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include "TextureLoader.h"

class Material {
public:
    // PBR material properties
    glm::vec3 albedo;      // Base color
    float metallic;        // Metalness (0.0 - 1.0)
    float roughness;       // Roughness (0.0 - 1.0)
    float ao;              // Ambient occlusion (0.0 - 1.0)
    
    // Texture maps
    unsigned int albedoMap;
    unsigned int normalMap;
    unsigned int metallicMap;
    unsigned int roughnessMap;
    unsigned int aoMap;
    
    bool useAlbedoMap;
    bool useNormalMap;
    bool useMetallicMap;
    bool useRoughnessMap;
    bool useAoMap;
    
    // Constructor
    Material();
    
    // Apply material to shader
    void Apply(Shader &shader);
    
    // Load texture maps
    void LoadAlbedoMap(const char* path);
    void LoadNormalMap(const char* path);
    void LoadMetallicMap(const char* path);
    void LoadRoughnessMap(const char* path);
    void LoadAoMap(const char* path);
    
    // Set scalar values
    void SetAlbedo(const glm::vec3 &color);
    void SetMetallic(float value);
    void SetRoughness(float value);
    void SetAo(float value);
};
