/************************************************************************
*	File name : Shader.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include<string>
#include <glew.h>
#include "../IO_Manager/Image_IO.hpp"
#include "../MathLibrary/MathLibrary.hpp"
#include "../Vertex/Vertex.hpp"
#include <map>

class Shader
{
public:
    Shader();
    Shader(const std::string& vertex_shader_source_code, const std::string& fragment_shader_source_code);
    ~Shader() = default;

    void CompileShaders(const std::string& p_VertexFilePath, const std::string& p_FragmentFilePath);

    void compileShadersFromSource(const char* p_VertexCode, const char* p_FragmentCode);

    void LinkShaders();

    void AddAttribute(const std::string& p_AttributeName);

    void UseEnable();
    void UnUseDisable();

    void Dispose();

private:
    void CompileShader(const std::string& p_FilePath, GLint p_Id);
    void CompileShader(const char* code, const std::string& name, GLuint id);

public:
    bool LoadFromSource(const std::string& vertex_shader_source_code, const std::string& fragment_shader_source_code);

    void SendUniformVariable(const std::string& variable_name, const Matrix3<float>& affine_matrix) noexcept;
    void SendUniformVariable(const std::string& variable_name, float number) noexcept;
    void SendUniformVariable(const std::string& variable_name, int number) noexcept;
    void SendUniformVariable(const std::string& variable_name, Color color) noexcept;

    int GetUniformLocation(const std::string& name) noexcept;

    constexpr unsigned GetShaderHandler() const noexcept { return m_ProgramID; }

    void Delete() noexcept;

public:
    static void Select(const Shader& shader) noexcept;
    static void SelectNothing() noexcept;

public:
    Shader(const Shader& other) = delete;
    Shader(Shader&& other) noexcept = delete;
    Shader& operator=(const Shader& other) = delete;
    Shader& operator=(Shader&& other) noexcept = delete;

private:
    int m_NumAttribute;
    GLuint m_ProgramID;
    GLuint m_VertexShaderID;
    GLuint m_FragmentShaderID;

    //unsigned                   handleToShader = 0;
    std::map<std::string, int> uniformNameToLocation{};
};
