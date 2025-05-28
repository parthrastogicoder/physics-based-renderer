#include "../include/Model.h"
#include <iostream>
#include <cmath>

Model::Model() {
}

void Model::CreateSphere(unsigned int xSegments, unsigned int ySegments, float radius, Material material) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    for (unsigned int y = 0; y <= ySegments; ++y) {
        for (unsigned int x = 0; x <= xSegments; ++x) {
            float xSegment = (float)x / (float)xSegments;
            float ySegment = (float)y / (float)ySegments;
            float xPos = std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI) * radius;
            float yPos = std::cos(ySegment * M_PI) * radius;
            float zPos = std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI) * radius;
            
            Vertex vertex;
            vertex.Position = glm::vec3(xPos, yPos, zPos);
            vertex.Normal = glm::normalize(glm::vec3(xPos, yPos, zPos));
            vertex.TexCoords = glm::vec2(xSegment, ySegment);
            
            // Calculate tangent and bitangent
            float theta = xSegment * 2.0f * M_PI;
            float phi = ySegment * M_PI;
            
            // Partial derivatives
            glm::vec3 dpdu(-radius * sin(theta) * sin(phi),
                          0,
                          radius * cos(theta) * sin(phi));
            
            glm::vec3 dpdv(radius * cos(theta) * cos(phi),
                          -radius * sin(phi),
                          radius * sin(theta) * cos(phi));
            
            vertex.Tangent = glm::normalize(dpdu);
            vertex.Bitangent = glm::normalize(glm::cross(vertex.Normal, vertex.Tangent));
            
            vertices.push_back(vertex);
        }
    }
    
    // Generate indices
    for (unsigned int y = 0; y < ySegments; ++y) {
        for (unsigned int x = 0; x < xSegments; ++x) {
            unsigned int first = (y * (xSegments + 1)) + x;
            unsigned int second = first + xSegments + 1;
            
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);
            
            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
    
    meshes.push_back(Mesh(vertices, indices, material));
}

void Model::CreateCube(float size, Material material) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    float halfSize = size / 2.0f;
    
    // Create 8 corners of the cube
    glm::vec3 positions[8] = {
        glm::vec3(-halfSize, -halfSize, -halfSize),
        glm::vec3( halfSize, -halfSize, -halfSize),
        glm::vec3( halfSize,  halfSize, -halfSize),
        glm::vec3(-halfSize,  halfSize, -halfSize),
        glm::vec3(-halfSize, -halfSize,  halfSize),
        glm::vec3( halfSize, -halfSize,  halfSize),
        glm::vec3( halfSize,  halfSize,  halfSize),
        glm::vec3(-halfSize,  halfSize,  halfSize)
    };
    
    // Define the 6 normals
    glm::vec3 normals[6] = {
        glm::vec3( 0.0f,  0.0f, -1.0f), // back
        glm::vec3( 0.0f,  0.0f,  1.0f), // front
        glm::vec3(-1.0f,  0.0f,  0.0f), // left
        glm::vec3( 1.0f,  0.0f,  0.0f), // right
        glm::vec3( 0.0f, -1.0f,  0.0f), // bottom
        glm::vec3( 0.0f,  1.0f,  0.0f)  // top
    };
    
    // Define the tangents and bitangents for each face
    glm::vec3 tangents[6] = {
        glm::vec3(1.0f, 0.0f, 0.0f),  // back
        glm::vec3(1.0f, 0.0f, 0.0f),  // front
        glm::vec3(0.0f, 0.0f, 1.0f),  // left
        glm::vec3(0.0f, 0.0f, -1.0f), // right
        glm::vec3(1.0f, 0.0f, 0.0f),  // bottom
        glm::vec3(1.0f, 0.0f, 0.0f)   // top
    };
    
    glm::vec3 bitangents[6] = {
        glm::vec3(0.0f, 1.0f, 0.0f),  // back
        glm::vec3(0.0f, 1.0f, 0.0f),  // front
        glm::vec3(0.0f, 1.0f, 0.0f),  // left
        glm::vec3(0.0f, 1.0f, 0.0f),  // right
        glm::vec3(0.0f, 0.0f, 1.0f),  // bottom
        glm::vec3(0.0f, 0.0f, -1.0f)  // top
    };
    
    // Define texture coordinates
    glm::vec2 texCoords[4] = {
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f)
    };
    
    // For each face, create 4 vertices and 6 indices (2 triangles)
    // Back face
    Vertex v1, v2, v3, v4;
    v1.Position = positions[0]; v1.Normal = normals[0]; v1.TexCoords = texCoords[0]; v1.Tangent = tangents[0]; v1.Bitangent = bitangents[0];
    v2.Position = positions[1]; v2.Normal = normals[0]; v2.TexCoords = texCoords[1]; v2.Tangent = tangents[0]; v2.Bitangent = bitangents[0];
    v3.Position = positions[2]; v3.Normal = normals[0]; v3.TexCoords = texCoords[2]; v3.Tangent = tangents[0]; v3.Bitangent = bitangents[0];
    v4.Position = positions[3]; v4.Normal = normals[0]; v4.TexCoords = texCoords[3]; v4.Tangent = tangents[0]; v4.Bitangent = bitangents[0];
    vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3); vertices.push_back(v4);
    indices.push_back(0); indices.push_back(1); indices.push_back(2);
    indices.push_back(2); indices.push_back(3); indices.push_back(0);
    
    // Front face
    v1.Position = positions[4]; v1.Normal = normals[1]; v1.TexCoords = texCoords[0]; v1.Tangent = tangents[1]; v1.Bitangent = bitangents[1];
    v2.Position = positions[5]; v2.Normal = normals[1]; v2.TexCoords = texCoords[1]; v2.Tangent = tangents[1]; v2.Bitangent = bitangents[1];
    v3.Position = positions[6]; v3.Normal = normals[1]; v3.TexCoords = texCoords[2]; v3.Tangent = tangents[1]; v3.Bitangent = bitangents[1];
    v4.Position = positions[7]; v4.Normal = normals[1]; v4.TexCoords = texCoords[3]; v4.Tangent = tangents[1]; v4.Bitangent = bitangents[1];
    vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3); vertices.push_back(v4);
    indices.push_back(4); indices.push_back(5); indices.push_back(6);
    indices.push_back(6); indices.push_back(7); indices.push_back(4);
    
    // Left face
    v1.Position = positions[0]; v1.Normal = normals[2]; v1.TexCoords = texCoords[0]; v1.Tangent = tangents[2]; v1.Bitangent = bitangents[2];
    v2.Position = positions[4]; v2.Normal = normals[2]; v2.TexCoords = texCoords[1]; v2.Tangent = tangents[2]; v2.Bitangent = bitangents[2];
    v3.Position = positions[7]; v3.Normal = normals[2]; v3.TexCoords = texCoords[2]; v3.Tangent = tangents[2]; v3.Bitangent = bitangents[2];
    v4.Position = positions[3]; v4.Normal = normals[2]; v4.TexCoords = texCoords[3]; v4.Tangent = tangents[2]; v4.Bitangent = bitangents[2];
    vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3); vertices.push_back(v4);
    indices.push_back(8); indices.push_back(9); indices.push_back(10);
    indices.push_back(10); indices.push_back(11); indices.push_back(8);
    
    // Right face
    v1.Position = positions[1]; v1.Normal = normals[3]; v1.TexCoords = texCoords[0]; v1.Tangent = tangents[3]; v1.Bitangent = bitangents[3];
    v2.Position = positions[5]; v2.Normal = normals[3]; v2.TexCoords = texCoords[1]; v2.Tangent = tangents[3]; v2.Bitangent = bitangents[3];
    v3.Position = positions[6]; v3.Normal = normals[3]; v3.TexCoords = texCoords[2]; v3.Tangent = tangents[3]; v3.Bitangent = bitangents[3];
    v4.Position = positions[2]; v4.Normal = normals[3]; v4.TexCoords = texCoords[3]; v4.Tangent = tangents[3]; v4.Bitangent = bitangents[3];
    vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3); vertices.push_back(v4);
    indices.push_back(12); indices.push_back(13); indices.push_back(14);
    indices.push_back(14); indices.push_back(15); indices.push_back(12);
    
    // Bottom face
    v1.Position = positions[0]; v1.Normal = normals[4]; v1.TexCoords = texCoords[0]; v1.Tangent = tangents[4]; v1.Bitangent = bitangents[4];
    v2.Position = positions[1]; v2.Normal = normals[4]; v2.TexCoords = texCoords[1]; v2.Tangent = tangents[4]; v2.Bitangent = bitangents[4];
    v3.Position = positions[5]; v3.Normal = normals[4]; v3.TexCoords = texCoords[2]; v3.Tangent = tangents[4]; v3.Bitangent = bitangents[4];
    v4.Position = positions[4]; v4.Normal = normals[4]; v4.TexCoords = texCoords[3]; v4.Tangent = tangents[4]; v4.Bitangent = bitangents[4];
    vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3); vertices.push_back(v4);
    indices.push_back(16); indices.push_back(17); indices.push_back(18);
    indices.push_back(18); indices.push_back(19); indices.push_back(16);
    
    // Top face
    v1.Position = positions[3]; v1.Normal = normals[5]; v1.TexCoords = texCoords[0]; v1.Tangent = tangents[5]; v1.Bitangent = bitangents[5];
    v2.Position = positions[2]; v2.Normal = normals[5]; v2.TexCoords = texCoords[1]; v2.Tangent = tangents[5]; v2.Bitangent = bitangents[5];
    v3.Position = positions[6]; v3.Normal = normals[5]; v3.TexCoords = texCoords[2]; v3.Tangent = tangents[5]; v3.Bitangent = bitangents[5];
    v4.Position = positions[7]; v4.Normal = normals[5]; v4.TexCoords = texCoords[3]; v4.Tangent = tangents[5]; v4.Bitangent = bitangents[5];
    vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3); vertices.push_back(v4);
    indices.push_back(20); indices.push_back(21); indices.push_back(22);
    indices.push_back(22); indices.push_back(23); indices.push_back(20);
    
    meshes.push_back(Mesh(vertices, indices, material));
}

void Model::CreatePlane(float width, float height, Material material) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    
    // Create 4 corners of the plane
    Vertex v1, v2, v3, v4;
    
    v1.Position = glm::vec3(-halfWidth, 0.0f, -halfHeight);
    v1.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
    v1.TexCoords = glm::vec2(0.0f, 0.0f);
    v1.Tangent = glm::vec3(1.0f, 0.0f, 0.0f);
    v1.Bitangent = glm::vec3(0.0f, 0.0f, 1.0f);
    
    v2.Position = glm::vec3(halfWidth, 0.0f, -halfHeight);
    v2.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
    v2.TexCoords = glm::vec2(1.0f, 0.0f);
    v2.Tangent = glm::vec3(1.0f, 0.0f, 0.0f);
    v2.Bitangent = glm::vec3(0.0f, 0.0f, 1.0f);
    
    v3.Position = glm::vec3(halfWidth, 0.0f, halfHeight);
    v3.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
    v3.TexCoords = glm::vec2(1.0f, 1.0f);
    v3.Tangent = glm::vec3(1.0f, 0.0f, 0.0f);
    v3.Bitangent = glm::vec3(0.0f, 0.0f, 1.0f);
    
    v4.Position = glm::vec3(-halfWidth, 0.0f, halfHeight);
    v4.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
    v4.TexCoords = glm::vec2(0.0f, 1.0f);
    v4.Tangent = glm::vec3(1.0f, 0.0f, 0.0f);
    v4.Bitangent = glm::vec3(0.0f, 0.0f, 1.0f);
    
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);
    
    meshes.push_back(Mesh(vertices, indices, material));
}

bool Model::LoadModel(const std::string &path) {
    // To be implemented using Assimp library
    std::cout << "Model loading from file not implemented yet." << std::endl;
    return false;
}

void Model::Draw(Shader &shader) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(shader);
    }
}
