#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.h"

class IBL {
public:
    // IBL maps
    unsigned int envCubemap;
    unsigned int irradianceMap;
    unsigned int prefilterMap;
    unsigned int brdfLUTTexture;
    
    // Constructor
    IBL();
    
    // Load an HDR environment map and generate all IBL maps
    void LoadEnvironmentMap(const char* hdrPath);
    
    // Apply IBL to shader
    void Apply(Shader &shader);
    
    // Draw skybox
    void DrawSkybox(Shader &skyboxShader, unsigned int cubeVAO);
    
private:
    // Generate a cubemap from an HDR equirectangular environment map
    unsigned int EquirectangularToCubemap(const char* hdrPath);
    
    // Generate an irradiance cubemap from an environment cubemap
    unsigned int GenerateIrradianceMap(unsigned int envMap);
    
    // Generate a prefiltered environment map for specular IBL
    unsigned int GeneratePrefilterMap(unsigned int envMap);
    
    // Generate a BRDF LUT for split-sum approximation
    unsigned int GenerateBRDFLookUpTexture();
};
