#include "../include/IBL.h"
#include "../include/TextureLoader.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

IBL::IBL() 
    : envCubemap(0), 
      irradianceMap(0), 
      prefilterMap(0), 
      brdfLUTTexture(0) {
}

void IBL::LoadEnvironmentMap(const char* hdrPath) {
    // Generate environment cubemap
    envCubemap = EquirectangularToCubemap(hdrPath);
    
    // Generate irradiance map
    irradianceMap = GenerateIrradianceMap(envCubemap);
    
    // Generate prefilter map
    prefilterMap = GeneratePrefilterMap(envCubemap);
    
    // Generate BRDF LUT
    brdfLUTTexture = GenerateBRDFLookUpTexture();
}

void IBL::Apply(Shader &shader) {
    // Apply IBL maps to shader
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    shader.setInt("irradianceMap", 5);
    
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
    shader.setInt("prefilterMap", 6);
    
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
    shader.setInt("brdfLUT", 7);
}

void IBL::DrawSkybox(Shader &skyboxShader, unsigned int cubeVAO) {
    // Draw skybox
    skyboxShader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    skyboxShader.setInt("environmentMap", 0);
    
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

unsigned int IBL::EquirectangularToCubemap(const char* hdrPath) {
    // In a real implementation, this would load an HDR environment map
    // and convert it to a cubemap using a shader
    // For this version, we'll load a skybox from individual texture files
    std::vector<std::string> faces = {
        "resources/textures/skybox/right.jpg",
        "resources/textures/skybox/left.jpg",
        "resources/textures/skybox/top.jpg",
        "resources/textures/skybox/bottom.jpg",
        "resources/textures/skybox/front.jpg",
        "resources/textures/skybox/back.jpg"
    };
    
    // Load cubemap textures
    unsigned int cubemap = TextureLoader::LoadCubemap(faces);
    
    // If loading fails, create a dummy cubemap
    if (cubemap == 0) {
        std::cout << "Failed to load skybox textures, creating dummy environment cubemap." << std::endl;
        cubemap = TextureLoader::CreateCubemap(1024, 1024);
    } else {
        std::cout << "Loaded environment cubemap from skybox textures." << std::endl;
    }
    
    return cubemap;
}

unsigned int IBL::GenerateIrradianceMap(unsigned int envMap) {
    // In a real implementation, this would compute an irradiance map from the environment map
    // using a shader to perform convolution over the hemisphere
    // For this simplified version, we'll create a dummy irradiance map
    unsigned int irradianceMap = TextureLoader::CreateCubemap(32, 32);
    
    std::cout << "Created dummy irradiance map." << std::endl;
    return irradianceMap;
}

unsigned int IBL::GeneratePrefilterMap(unsigned int envMap) {
    // In a real implementation, this would compute a prefiltered environment map
    // using a shader to perform importance sampling based on the roughness level
    // For this simplified version, we'll create a dummy prefilter map
    unsigned int prefilterMap = TextureLoader::CreateCubemap(128, 128);
    
    std::cout << "Created dummy prefilter map." << std::endl;
    return prefilterMap;
}

unsigned int IBL::GenerateBRDFLookUpTexture() {
    // In a real implementation, this would compute a BRDF lookup texture
    // using a shader to integrate the BRDF for various roughness and NdotV values
    // For this simplified version, we'll create a dummy BRDF LUT
    unsigned int brdfLUTTexture;
    glGenTextures(1, &brdfLUTTexture);
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
    
    // Create a blank 512x512 texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, nullptr);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    std::cout << "Created dummy BRDF LUT." << std::endl;
    return brdfLUTTexture;
}
