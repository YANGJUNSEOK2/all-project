/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: mesh.h
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#ifndef MESH_H
#define MESH_H

#include "TextureBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferArray.h"
#include "AttribLayOut.h"
#include "IndexBuffer.h"
#include "shader.h"

#include "math.h"

#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace MyEngine
{
    struct Vertex
    {
        Vertex()
        {
            position.x = 0;
            position.y = 0;
            position.z = 0;

            textureUV.x = 0;
            textureUV.y = 0;

            normal.x = 0;
            normal.y = 0;
            normal.z = 0;
        }

        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 textureUV;
    };

    class Mesh
    {
    public:
        Mesh();
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureBuffer> textures);


    private:
        void SetUpMesh();

        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
        std::vector<TextureBuffer> m_textures;

        int numVertices;
        int numTris;
        int numIndices;

        const float  PI = 3.14159f;
        const float  TWO_PI = 2.0f * PI;
        const float  HALF_PI = 0.5f * PI;

    public:
        std::unique_ptr<VertexBuffer> ptr_VBO;
        std::unique_ptr<IndexBuffer> ptr_EBO;
        std::unique_ptr<VertexArray> ptr_VAO;

        void Draw_TRIANGLES(const Shader& shader) const;
        void Draw_PATCHES(const Shader& shader) const;
    };
}
#endif //! MESH_H
