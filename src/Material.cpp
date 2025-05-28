#include "../include/Material.h"

Material::Material() 
    : albedo(glm::vec3(1.0f)), 
      metallic(0.0f), 
      roughness(0.5f), 
      ao(1.0f),
      useAlbedoMap(false),
      useNormalMap(false),
      useMetallicMap(false),
      useRoughnessMap(false),
      useAoMap(false) {
}

void Material::Apply(Shader &shader) {
    // Set material properties
    shader.setVec3("material.albedo", albedo);
    shader.setFloat("material.metallic", metallic);
    shader.setFloat("material.roughness", roughness);
    shader.setFloat("material.ao", ao);
    
    // Set texture usage flags
    shader.setBool("material.useAlbedoMap", useAlbedoMap);
    shader.setBool("material.useNormalMap", useNormalMap);
    shader.setBool("material.useMetallicMap", useMetallicMap);
    shader.setBool("material.useRoughnessMap", useRoughnessMap);
    shader.setBool("material.useAoMap", useAoMap);
    
    // Bind textures if they are used
    if (useAlbedoMap) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, albedoMap);
        shader.setInt("material.albedoMap", 0);
    }
    
    if (useNormalMap) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalMap);
        shader.setInt("material.normalMap", 1);
    }
    
    if (useMetallicMap) {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, metallicMap);
        shader.setInt("material.metallicMap", 2);
    }
    
    if (useRoughnessMap) {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, roughnessMap);
        shader.setInt("material.roughnessMap", 3);
    }
    
    if (useAoMap) {
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, aoMap);
        shader.setInt("material.aoMap", 4);
    }
}

void Material::LoadAlbedoMap(const char* path) {
    albedoMap = TextureLoader::LoadTexture(path, true);
    useAlbedoMap = true;
}

void Material::LoadNormalMap(const char* path) {
    normalMap = TextureLoader::LoadTexture(path, false);
    useNormalMap = true;
}

void Material::LoadMetallicMap(const char* path) {
    metallicMap = TextureLoader::LoadTexture(path, false);
    useMetallicMap = true;
}

void Material::LoadRoughnessMap(const char* path) {
    roughnessMap = TextureLoader::LoadTexture(path, false);
    useRoughnessMap = true;
}

void Material::LoadAoMap(const char* path) {
    aoMap = TextureLoader::LoadTexture(path, false);
    useAoMap = true;
}

void Material::SetAlbedo(const glm::vec3 &color) {
    albedo = color;
}

void Material::SetMetallic(float value) {
    metallic = value;
}

void Material::SetRoughness(float value) {
    roughness = value;
}

void Material::SetAo(float value) {
    ao = value;
}
