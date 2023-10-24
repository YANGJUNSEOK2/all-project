/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: shader.h
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>  // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
namespace MyEngine
{
    class Shader
    {
    public:
        // the program ID
        unsigned int m_ID;

        // constructor reads and builds the shader
        Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr, const char* tessControlPath = nullptr, const char* tessEvaluationPath = nullptr);
        Shader() = delete;
        // use/activate the shader
        void use();
        void Unuse();
        // utility uniform functions
        void SetUniform(const std::string& name, GLboolean value) const;
        void SetUniform(const std::string& name, GLint value) const;
        void SetUniform(const std::string& name, GLuint value) const;
        void SetUniform(const std::string& name, GLfloat value) const;
        void SetUniform(const std::string& name, const GLdouble value) const;
        void SetUniform(const std::string& name, const glm::vec3& value) const;
        void SetUniform(const std::string& name, GLfloat x, GLfloat y, GLfloat z) const;
        void SetUniform(const std::string& name, const glm::vec4& value) const;
        void SetUniform(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
        void SetUniform(const std::string& name, const glm::mat4& mat) const;
        void SetUniform(const std::string& name, const glm::mat3& mat) const;
        void SetUniform1fv(const std::string& name, int count, void* data) const;
    };

}

#endif