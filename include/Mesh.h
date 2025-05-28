#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Material.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

class Mesh {
public:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material material;
    
    // Constructor
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material);
    
    // Render the mesh
    void Draw(Shader &shader);
    
private:
    // Render data
    unsigned int VAO, VBO, EBO;
    
    // Initializes all the buffer objects/arrays
    void setupMesh();
};
