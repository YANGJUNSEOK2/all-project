/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: object.h
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#ifndef OBJECT_H
#define OBJECT_H
#include <memory>
#include <glm/detail/type_vec.hpp>

#include "model.h"
#include "transform.h"

namespace MyEngine
{
    class Object
    {
    public:
        Object(std::string fileName);
        Object *CreateObject(const std::string &fileName, glm::vec3 _position, glm::vec3 _scale,
                          glm::vec3 _rotation_axis = glm::vec3(0, 0, 0));

        const std::string &getName() const { return name_; }
        const glm::vec3 &getPosition() const { return position; }
        const glm::vec3 &getScale() const { return scale; }
        const glm::vec3 &getRotation() const { return rotation_axis; }
        void setPosition(const glm::vec3 &pos) { position = pos; }
        void setRotation(const glm::vec3 &rot) { rotation_axis = rot; }
        void setScale(const glm::vec3 &s) { scale = s; }
    private:

        std::string name_;

        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation_axis;
    };

    extern Object *OBJECT;
}

#endif



