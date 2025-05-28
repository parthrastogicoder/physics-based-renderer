#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Shader.h"

class Model {
public:
    // Model data
    std::vector<Mesh> meshes;
    
    // Constructor
    Model();
    
    // Generate primitives
    void CreateSphere(unsigned int xSegments, unsigned int ySegments, float radius, Material material);
    void CreateCube(float size, Material material);
    void CreatePlane(float width, float height, Material material);
    
    // Load model from file
    bool LoadModel(const std::string &path);
    
    // Draw the model
    void Draw(Shader &shader);
    
private:
    // Processes a node in assimp's node hierarchy
    void processNode(void* node, void* scene);
    
    // Processes a mesh from assimp
    Mesh processMesh(void* mesh, void* scene);
    
    // Load textures from assimp material
    std::vector<unsigned int> loadMaterialTextures(void* mat, int type, std::string typeName);
};
