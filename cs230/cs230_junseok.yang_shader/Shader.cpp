/*
junseok.yang
assignment3
cs230
spring 2019
*/

#include <CS230/graphics/Color4f.hpp>
#include <CS230/graphics/Shader.hpp>
#include <CS230/graphics/glCheck.hpp>
#include <CS230/math/matrix3.hpp>
#include <CS230/math/vector3.hpp>
#include <GL/glew.h>
#include <cassert>
#include <iostream>



namespace CS230
{
    Shader::Shader(const std::string& vertex_shader_source_code, const std::string& fragment_shader_source_code)
    {
        LoadFromSource(vertex_shader_source_code, fragment_shader_source_code);
    }

    bool Shader::LoadFromSource(const std::string& vertex_shader_source_code,
        const std::string& fragment_shader_source_code)
    {
        
        std::string vertexSource = vertex_shader_source_code;
        std::string fragmentSource = fragment_shader_source_code;

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glCheck(vertexShader);

        const GLchar *source = (const GLchar *)vertexSource.c_str();
        glCheck(glShaderSource(vertexShader, 1, &source, 0));

        glCheck(glCompileShader(vertexShader));

        GLint isCompiled = 0;
        glCheck(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled));

        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glCheck(glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength));

            GLchar message[1024];
            glCheck(glGetShaderInfoLog(vertexShader, maxLength, &maxLength, message));

            glCheck(glDeleteShader(vertexShader));

            return false;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glCheck(fragmentShader);

        source = (const GLchar *)fragmentSource.c_str();
        glCheck(glShaderSource(fragmentShader, 1, &source, 0));

        glCheck(glCompileShader(fragmentShader));

        glCheck(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled));

        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glCheck(glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength));

            GLchar message[1024];
            glCheck(glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, message));

            glCheck(glDeleteShader(fragmentShader));
            glCheck(glDeleteShader(vertexShader));

            return false;
        }

        GLuint program;
        handleToShader = program = glCreateProgram();
        glCheck(handleToShader);
      

        glCheck(glAttachShader(program, vertexShader));
        glCheck(glAttachShader(program, fragmentShader));

        glCheck(glLinkProgram(program));

        GLint isLinked = 0;
        glCheck(glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked));

        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glCheck(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength));

            GLchar message[1024];
            glCheck(glGetProgramInfoLog(program, maxLength, &maxLength, message));


            glCheck(glDeleteProgram(program));
            glCheck(glDeleteShader(vertexShader));
            glCheck(glDeleteShader(fragmentShader));

            return false;
        }

        glCheck(glDeleteShader(vertexShader));
        glCheck(glDeleteShader(fragmentShader));

        return true;
    }

    void Shader::SendUniformVariable(const std::string& variable_name, const matrix3& affine_matrix) noexcept
    {
        GLfloat m_Affine_Matrix[9];
        
        m_Affine_Matrix[0] = affine_matrix.elements[0][0];
        m_Affine_Matrix[1] = affine_matrix.elements[0][1];
        m_Affine_Matrix[2] = affine_matrix.elements[0][2];
        m_Affine_Matrix[3] = affine_matrix.elements[1][0];
        m_Affine_Matrix[4] = affine_matrix.elements[1][1];
        m_Affine_Matrix[5] = affine_matrix.elements[1][2];
        m_Affine_Matrix[6] = affine_matrix.elements[2][0];
        m_Affine_Matrix[7] = affine_matrix.elements[2][1];
        m_Affine_Matrix[8] = affine_matrix.elements[2][2];
        
        glCheck(glUniformMatrix3fv(GetUniformLocation(variable_name), 1, GL_FALSE, m_Affine_Matrix));
    }

    void Shader::SendUniformVariable(const std::string& variable_name, float number) noexcept
    {
        glCheck(glUniform1f(GetUniformLocation(variable_name), number));
    }

    void Shader::SendUniformVariable(const std::string& variable_name, int number) noexcept
    {
        glCheck(glUniform1i(GetUniformLocation(variable_name), number));
    }

    void Shader::SendUniformVariable(const std::string& variable_name, Color4f color) noexcept
    {
        glCheck(glUniform4f(GetUniformLocation(variable_name), color.red, color.green, color.blue, color.alpha));
    }

    void Shader::Select(const Shader& shader) noexcept
    {
        glCheck(glUseProgram(shader.handleToShader));
    }

    void Shader::SelectNothing() noexcept
    {
        glCheck(glUseProgram(NULL));
    }

    int Shader::GetUniformLocation(const std::string& name) noexcept
    {
        const GLchar* m_Name;
        m_Name = name.c_str();
        GLint m_Loc = glGetUniformLocation(handleToShader, m_Name);
        uniformNameToLocation.insert(std::make_pair(name, m_Loc));
        glCheck(m_Loc);
        return m_Loc;
    }

    void Shader::Delete() noexcept
    {
        glCheck(glDeleteProgram(handleToShader));
    }
}
