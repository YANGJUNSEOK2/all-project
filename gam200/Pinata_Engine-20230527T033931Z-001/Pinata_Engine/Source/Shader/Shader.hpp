/************************************************************************
*	File name : Shader.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester
*************************************************************************/
#pragma once
#include<string>
#include <glew.h>
#include "../IO_Manager/Image_IO.hpp"

    class Shader
    {
    public:
        Shader();
        ~Shader() = default;

        void CompileShaders(const std::string& p_VertexFilePath, const std::string& p_FragmentFilePath);

        void compileShadersFromSource(const char* p_VertexCode, const char* p_FragmentCode);

        void LinkShaders();

        void AddAttribute(const std::string& p_AttributeName);

        GLint GetUniformLocation(const std::string& p_uniformName);

        void UseEnable();
        void UnUseDisable();

        void Dispose();
    private:
        void CompileShader(const std::string& p_FilePath, GLint p_Id);
        void CompileShader(const char* code, const std::string& name, GLuint id);

        int m_NumAttribute;
        GLuint m_ProgramID;
        GLuint m_VertexShaderID;
        GLuint m_FragmentShaderID;
    };
