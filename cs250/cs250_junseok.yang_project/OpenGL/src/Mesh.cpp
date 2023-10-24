/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Mesh.cpp
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#include "Mesh.h"
using namespace MyEngine;

Mesh::Mesh() : numVertices(0), numTris(0), numIndices(0) { }

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    m_vertices = vertices;
    m_indices = indices;

    SetUpMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureBuffer> textures)
{
    /*
    Why Does it Copy the Container?????
    */
    m_vertices = vertices;
    m_indices = indices;
    m_textures = textures;

    SetUpMesh();
}

void Mesh::Draw_TRIANGLES(const Shader& shader) const
{
    ptr_VAO->Bind();
    ptr_VBO->Bind();
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    ptr_VAO->UnBind();
}

void Mesh::Draw_PATCHES(const Shader& shader) const
{
    ptr_VAO->Bind();
    ptr_VBO->Bind();
    glDrawElements(GL_PATCHES, m_indices.size(), GL_UNSIGNED_INT, 0);
    ptr_VAO->UnBind();
}

void Mesh::SetUpMesh()
{
    ptr_VAO = std::make_unique<VertexArray>();
    ptr_VBO = std::make_unique<VertexBuffer>(m_vertices.data(), m_vertices.size() * sizeof(Vertex));
    ptr_EBO = std::make_unique<IndexBuffer>(m_indices.data(), m_indices.size() * sizeof(unsigned int));

    AttribLayOut layout;
    // Pos, Normal, TexCoord
    layout.Add<GL_FLOAT>(3);
    layout.Add<GL_FLOAT>(3);
    layout.Add<GL_FLOAT>(2);


    ptr_VAO->AddBuffer(*ptr_VBO, layout);
}