/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: model.cpp
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#include "model.h"

using namespace MyEngine;

Model::Model(const std::string& path)
{
    LoadModel(path);
}

void Model::LoadModel(const std::string& path)
{
    std::ifstream stream(path);

    std::string line;
    std::string prefix;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int index = 0;

    std::vector<glm::vec3> verts_pos;
    std::vector<glm::vec2> tex_coords;
    std::vector<glm::vec3> verts_norm;

    std::stringstream ss;

    bool isNewModel = false;

    if (!stream)
    {
        std::cerr << "No file\n";
    }

    while (std::getline(stream, line))
    {
        if (line == "")
            continue;

        prefix.clear();
        ss.clear();
        ss.str(line);
        ss >> prefix;

        if (prefix == "v")
        {
            if (isNewModel == true)
            {
                meshes.emplace_back(vertices, indices);
                vertices.clear();
                // Make new Mesh
                isNewModel = false;
            }

            glm::vec3 vertex_pos;
            ss >> vertex_pos.x >> vertex_pos.y >> vertex_pos.z;
            verts_pos.emplace_back(vertex_pos);
        }
        else if (prefix == "vt")
        {
            glm::vec2 textCoord;
            ss >> textCoord.x >> textCoord.y;
            tex_coords.emplace_back(textCoord);
        }
        else if (prefix == "vn")
        {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            verts_norm.emplace_back(normal);

            isNewModel = true;
        }
        else if (prefix == "f")
        {

            int temp = 0;
            GLint counter = 0;

            Vertex vertex;

            // vec3's to calculate normal_vec of face
            std::vector<glm::vec3> vert;
            unsigned int vert_per_face = 0;

            while (ss >> temp)
            {
                try
                {
                    if (temp < 0)
                        throw std::out_of_range("index from model file is negative value");

                    --temp;
                }
                catch (std::exception & e)
                {
                    std::cout << "EXCEPTION : " << e.what();
                    // this code is for negative value calculation
                    //if (counter == 0)
                    //    temp += verts_pos.size();
                    //else if (counter == 1)
                    //    temp += tex_coords.size();
                    //else if (counter == 2)
                    //    temp += verts_norm.size();
                    assert(true);
                }

                if (counter == 0)
                    vertex.position = verts_pos[temp];
                else if (counter == 1)
                    vertex.textureUV = tex_coords[temp];
                else if (counter == 2)
                    vertex.normal = verts_norm[temp];

                if (ss.peek() == '/')
                {
                    while (ss.peek() == '/')
                    {
                        ++counter;
                        ss.ignore(1, '/');
                    }
                }
                else if (ss.peek() == ' ' || ss.peek() == EOF)
                {
                    counter = 0;
                    vertices.emplace_back(vertex);
                    ++vert_per_face;
                    ss.ignore(1, ' ');
                }
            }

            for (unsigned int i = 0; i < vert_per_face - 2; ++i)
            {
                indices.push_back(index);
                indices.push_back(index + i + 1);
                indices.push_back(index + i + 2);
            }

            index += vert_per_face;
        }
    }

    meshes.emplace_back(vertices, indices);
}

void Model::Draw_TRIANGLES(const Shader& shader)
{
    for (const auto& mesh : meshes)
    {
        mesh.Draw_TRIANGLES(shader);
    }
}

void Model::Draw_PATCHES(const Shader& shader)
{
    for (const auto& mesh : meshes)
    {
        mesh.Draw_PATCHES(shader);
    }
}