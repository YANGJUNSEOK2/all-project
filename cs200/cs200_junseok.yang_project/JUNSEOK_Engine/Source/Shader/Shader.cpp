/************************************************************************
*	File name : Shader.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#include "Shader.hpp"
#include <fstream>
#include<vector>
#include "glCheck/glCheck.hpp"

Shader::Shader() : m_NumAttribute(0), m_ProgramID(0), m_VertexShaderID(0), m_FragmentShaderID(0)
{
}

Shader::Shader(const std::string& vertex_shader_source_code, const std::string& fragment_shader_source_code)
{
    compileShadersFromSource(vertex_shader_source_code.c_str(), fragment_shader_source_code.c_str());
}

void Shader::CompileShaders(const std::string& p_VertexFilePath, const std::string& p_FragmentFilePath)
{
    std::string vertSource;
    std::string fragSource;

    IOManager::ReadFile(p_VertexFilePath, vertSource);
    IOManager::ReadFile(p_FragmentFilePath, fragSource);

    compileShadersFromSource(vertSource.c_str(), fragSource.c_str());
}

void Shader::compileShadersFromSource(const char* p_VertexCode, const char* p_FragmentCode)
{
    m_ProgramID = glCreateProgram();

    //Create the vertex shader object, and store its ID
    m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (m_VertexShaderID == 0) {
        //ErrorSystem::FindError("Vertex shader failed to be created!");
    }

    //Create the fragment shader object, and store its ID
    m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_FragmentShaderID == 0) {
        //ErrorSystem::FindError("Fragment shader failed to be created!");
    }

    //Compile each shader
    CompileShader(p_VertexCode, "Vertex Shader", m_VertexShaderID);
    CompileShader(p_FragmentCode, "Fragment Shader", m_FragmentShaderID);
}

void Shader::LinkShaders()
{

    m_ProgramID = glCreateProgram();

    // Attach our shaders to our program
    glCheck(glAttachShader(m_ProgramID, m_VertexShaderID));
    glCheck(glAttachShader(m_ProgramID, m_FragmentShaderID));

    // Link our program
    glCheck(glLinkProgram(m_ProgramID));

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glCheck(glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int*)&isLinked));
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glCheck(glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength));

        // The maxLength includes the NULL character
        std::vector<char> errorLog(maxLength);
        glCheck(glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &errorLog[0]));



        // We don't need the program anymore.
        glCheck(glDeleteProgram(m_ProgramID));
        // Don't leak shaders either.
        glCheck(glDeleteShader(m_VertexShaderID));
        glCheck(glDeleteShader(m_FragmentShaderID));

        std::printf("%s\n", &(errorLog[0]));
        //ErrorSystem::FindError("Shaders failed link!");
    }

    // Always detach shaders after a successful link.
    glCheck(glDetachShader(m_ProgramID, m_VertexShaderID));
    glCheck(glDetachShader(m_ProgramID, m_FragmentShaderID));
    glCheck(glDeleteShader(m_VertexShaderID));
    glCheck(glDeleteShader(m_FragmentShaderID));
}

void Shader::UseEnable()
{
    glCheck(glUseProgram(m_ProgramID));
    for (int i = 0; i < m_NumAttribute; i++)
    {
        glCheck(glEnableVertexAttribArray(i));
    }
}

void Shader::UnUseDisable()//SelectNothing
{
    glCheck(glUseProgram(0));
    for (int i = 0; i < m_NumAttribute; i++)
    {
        glCheck(glDisableVertexAttribArray(i));
    }
}

void Shader::Dispose()
{
    if (m_ProgramID)
    {
        glCheck(glDeleteProgram(m_ProgramID));
    }
}

void Shader::AddAttribute(const std::string& p_AttributeName)
{
    glCheck(glBindAttribLocation(m_ProgramID, m_NumAttribute++, p_AttributeName.c_str()));
}

void Shader::CompileShader(const std::string& p_FilePath, GLint p_Id)
{
    std::ifstream vertexFile(p_FilePath);
    if (vertexFile.fail())
    {
        perror(p_FilePath.c_str());
        //ErrorSystem::FindError("Fail to open " + p_FilePath);
    }

    std::string fileContents = "";
    std::string line;

    while (std::getline(vertexFile, line))
    {
        fileContents += line + "\n";
    }

    vertexFile.close();

    const char* contentsPtr = fileContents.c_str();
    glCheck(glShaderSource(p_Id, 1, &contentsPtr, nullptr));

    glCheck(glCompileShader(p_Id));

    GLint success = 0;
    glCheck(glGetShaderiv(p_Id, GL_COMPILE_STATUS, &success));

    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glCheck(glGetShaderiv(p_Id, GL_INFO_LOG_LENGTH, &maxLength));

        std::vector<char> errorLog(maxLength);
        glCheck(glGetShaderInfoLog(p_Id, maxLength, &maxLength, &errorLog[0]));

        glCheck(glDeleteShader(p_Id));

        std::printf("%s\n", &(errorLog[0]));
        //ErrorSystem::FindError("Shader" + p_FilePath + " failed compiled!");
    }
}

void Shader::CompileShader(const char* code, const std::string& name, GLuint id)
{
    glCheck(glShaderSource(id, 1, &code, nullptr));

    glCheck(glCompileShader(id));

    GLint success = 0;
    glCheck(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glCheck(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength));

        std::vector<char> errorLog(maxLength);
        glCheck(glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]));

        glCheck(glDeleteShader(id));

        std::printf("%s\n", &(errorLog[0]));
        //ErrorSystem::FindError("Shader " + name + " failed to compile");
    }
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
    m_ProgramID = program = glCreateProgram();
    glCheck(m_ProgramID);


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

void Shader::SendUniformVariable(const std::string& variable_name, const Matrix3<float>& affine_matrix) noexcept
{
    GLfloat m_Affine_Matrix[9];

    m_Affine_Matrix[0] = affine_matrix.Elements[0][0];
    m_Affine_Matrix[1] = affine_matrix.Elements[0][1];
    m_Affine_Matrix[2] = affine_matrix.Elements[0][2];
    m_Affine_Matrix[3] = affine_matrix.Elements[1][0];
    m_Affine_Matrix[4] = affine_matrix.Elements[1][1];
    m_Affine_Matrix[5] = affine_matrix.Elements[1][2];
    m_Affine_Matrix[6] = affine_matrix.Elements[2][0];
    m_Affine_Matrix[7] = affine_matrix.Elements[2][1];
    m_Affine_Matrix[8] = affine_matrix.Elements[2][2];

    const GLchar* m_Name;
    m_Name = variable_name.c_str();
    GLint m_Loc = glGetUniformLocation(m_ProgramID, m_Name);
    uniformNameToLocation.insert(std::make_pair(variable_name, m_Loc));
    glCheck(m_Loc);

    glCheck(glUniformMatrix3fv(m_Loc, 1, GL_FALSE, m_Affine_Matrix));
}

void Shader::SendUniformVariable(const std::string& variable_name, float number) noexcept
{
    const GLchar* m_Name;
    m_Name = variable_name.c_str();
    GLint m_Loc = glGetUniformLocation(m_ProgramID, m_Name);
    uniformNameToLocation.insert(std::make_pair(variable_name, m_Loc));
    glCheck(m_Loc);

    glCheck(glUniform1f(m_Loc, number));
}

void Shader::SendUniformVariable(const std::string& variable_name, int number) noexcept
{
    const GLchar* m_Name;
    m_Name = variable_name.c_str();
    GLint m_Loc = glGetUniformLocation(m_ProgramID, m_Name);
    uniformNameToLocation.insert(std::make_pair(variable_name, m_Loc));
    glCheck(m_Loc);
    glCheck(glUniform1i(m_Loc, number));
}

void Shader::SendUniformVariable(const std::string& variable_name, Color color) noexcept
{
    const GLchar* m_Name;
    m_Name = variable_name.c_str();
    GLint m_Loc = glGetUniformLocation(m_ProgramID, m_Name);
    uniformNameToLocation.insert(std::make_pair(variable_name, m_Loc));
    glCheck(m_Loc);

    glCheck(glUniform4f(m_Loc, color.r, color.g, color.b, color.a));
}

void Shader::Select(const Shader& shader) noexcept
{
    glCheck(glUseProgram(shader.m_ProgramID));
}

void Shader::SelectNothing() noexcept
{
    glCheck(glUseProgram(NULL));
}

int Shader::GetUniformLocation(const std::string& name) noexcept
{
    GLuint uniformLocation = glGetUniformLocation(m_ProgramID, name.c_str());
    if (uniformLocation == GL_INVALID_INDEX)
    {
        //ErrorSystem::FindError("Uniform" + p_uniformName + "not found in shader!");
    }
    return uniformLocation;
}

void Shader::Delete() noexcept
{
    glCheck(glDeleteProgram(m_ProgramID));
}