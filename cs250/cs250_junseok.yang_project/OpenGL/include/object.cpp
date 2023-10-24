/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: object.cpp
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#include "object.h"

namespace MyEngine
{
    Object* OBJECT = nullptr;

    Object::Object(std::string fileName) : name_(fileName)
    {
        OBJECT = this;
        position = glm::vec3(0.f);
        rotation_axis = glm::vec3(0.f); 
        scale = glm::vec3(10.f, 10.f, 1.f);
    }
    Object* Object::CreateObject(const std::string &fileName, glm::vec3 _position, glm::vec3 _scale,
                                        glm::vec3 _rotation_axis)
    {
        Object *obj = new Object(fileName);
        obj->setPosition(_position);
        obj->setScale(_scale);
        obj->setRotation(_rotation_axis);

        return obj;
    }
} // namespace MyEngine
