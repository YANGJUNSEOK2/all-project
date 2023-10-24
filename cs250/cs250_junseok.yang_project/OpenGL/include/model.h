/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: model.h
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
namespace MyEngine
{
    /*struct Material
    {
        float ambientStrength;
        float specularStrength;
        float shininess = 32.0f;
    };*/

    class Model
    {
    public:
        Model(const std::string& path);

        std::vector<Mesh> meshes;
        //Material material;

        void Draw_TRIANGLES(const Shader& shader);
        void Draw_PATCHES(const Shader& shader);
        void LoadModel(const std::string& path);

    private:

    };


}
#endif // !MODEL_H
