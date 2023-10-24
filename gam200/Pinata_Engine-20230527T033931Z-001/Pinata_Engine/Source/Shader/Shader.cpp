/************************************************************************
*	File name : Shader.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester
*************************************************************************/
#include "Shader.hpp"
#include <fstream>
#include<vector>

    Shader::Shader() : m_NumAttribute(0), m_ProgramID(0), m_VertexShaderID(0), m_FragmentShaderID(0)
    {
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
        glAttachShader(m_ProgramID, m_VertexShaderID);
        glAttachShader(m_ProgramID, m_FragmentShaderID);

        // Link our program
        glLinkProgram(m_ProgramID);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int*)& isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<char> errorLog(maxLength);
            glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &errorLog[0]);



            // We don't need the program anymore.
            glDeleteProgram(m_ProgramID);
            // Don't leak shaders either.
            glDeleteShader(m_VertexShaderID);
            glDeleteShader(m_FragmentShaderID);

            std::printf("%s\n", &(errorLog[0]));
            //ErrorSystem::FindError("Shaders failed link!");
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_ProgramID, m_VertexShaderID);
        glDetachShader(m_ProgramID, m_FragmentShaderID);
        glDeleteShader(m_VertexShaderID);
        glDeleteShader(m_FragmentShaderID);
    }

    void Shader::AddAttribute(const std::string& p_AttributeName)
    {
        glBindAttribLocation(m_ProgramID, m_NumAttribute++, p_AttributeName.c_str());
    }

    GLint Shader::GetUniformLocation(const std::string& p_uniformName)
    {
        GLuint uniformLocation = glGetUniformLocation(m_ProgramID, p_uniformName.c_str());
        if (uniformLocation == GL_INVALID_INDEX)
        {
            //ErrorSystem::FindError("Uniform" + p_uniformName + "not found in shader!");
        }
        return uniformLocation;
    }

    void Shader::UseEnable()
    {
        glUseProgram(m_ProgramID);
        for (int i = 0; i < m_NumAttribute; i++)
        {
            glEnableVertexAttribArray(i);
        }
    }

    void Shader::UnUseDisable()
    {
        glUseProgram(0);
        for (int i = 0; i < m_NumAttribute; i++)
        {
            glDisableVertexAttribArray(i);
        }
    }

    void Shader::Dispose()
    {
        if (m_ProgramID)
        {
            glDeleteProgram(m_ProgramID);
        }
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
        glShaderSource(p_Id, 1, &contentsPtr, nullptr);

        glCompileShader(p_Id);

        GLint success = 0;
        glGetShaderiv(p_Id, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(p_Id, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(p_Id, maxLength, &maxLength, &errorLog[0]);

            glDeleteShader(p_Id);

            std::printf("%s\n", &(errorLog[0]));
            //ErrorSystem::FindError("Shader" + p_FilePath + " failed compiled!");
        }
    }

    void Shader::CompileShader(const char* code, const std::string& name, GLuint id)
    {
        glShaderSource(id, 1, &code, nullptr);

        glCompileShader(id);

        GLint success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

            glDeleteShader(id);

            std::printf("%s\n", &(errorLog[0]));
            //ErrorSystem::FindError("Shader " + name + " failed to compile");
        }
    }
