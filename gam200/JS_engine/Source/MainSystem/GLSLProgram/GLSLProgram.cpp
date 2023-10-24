#include "GLSLProgram.hpp"
#include <fstream>
#include<vector>

namespace JS_Engine {
    namespace MainSystem {
        GLSLProgram::GLSLProgram() : m_NumAttribute(0),m_ProgramID(0),m_VertexShaderID(0),m_FragmentShaderID(0)
        {
        }

        GLSLProgram::~GLSLProgram()
        {
        }

        void GLSLProgram::compileShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath)
        {
            m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            if(m_VertexShaderID == 0)
            {
                ErrorSystem::FatalError("Vertex shader is not Created");
            }

            m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
            if (m_FragmentShaderID == 0)
            {
                ErrorSystem::FatalError("Vertex shader is not Created");
            }

            compileShader(vertexFilePath, m_VertexShaderID);
            compileShader(fragmentFilePath, m_FragmentShaderID);
        }

        void GLSLProgram::linkShaders()
        {

            m_ProgramID = glCreateProgram();

            // Attach our shaders to our program
            glAttachShader(m_ProgramID, m_VertexShaderID);
            glAttachShader(m_ProgramID, m_FragmentShaderID);

            // Link our program
            glLinkProgram(m_ProgramID);

            // Note the different functions here: glGetProgram* instead of glGetShader*.
            GLint isLinked = 0;
            glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int *)&isLinked);
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
                ErrorSystem::FatalError("Shaders failed link!");
            }

            // Always detach shaders after a successful link.
            glDetachShader(m_ProgramID, m_VertexShaderID);
            glDetachShader(m_ProgramID, m_FragmentShaderID);
            glDeleteShader(m_VertexShaderID);
            glDeleteShader(m_FragmentShaderID);
        }

        void GLSLProgram::addAttribute(const std::string& attributeName)
        {
            glBindAttribLocation(m_ProgramID, m_NumAttribute++, attributeName.c_str());
        }

        GLint GLSLProgram::getUniformLocation(const std::string& p_uniformName)
        {
            GLuint uniformLocation = glGetUniformLocation(m_ProgramID, p_uniformName.c_str());
            if(uniformLocation == GL_INVALID_INDEX)
            {
                ErrorSystem::FatalError("Uniform" + p_uniformName + "not found in shader!");
            }
            return uniformLocation;
        }

        void GLSLProgram::useEnable()
        {
            glUseProgram(m_ProgramID);
            for(int i=0;i<m_NumAttribute;i++)
            {
                glEnableVertexAttribArray(i);
            }
        }

        void GLSLProgram::unUseDiable()
        {
            glUseProgram(0);
            for (int i = 0; i < m_NumAttribute; i++)
            {
                glDisableVertexAttribArray(i);
            }
        }

        void GLSLProgram::compileShader(const std::string& filePath, GLint id)
        {
            std::ifstream vertexFile(filePath);
            if (vertexFile.fail())
            {
                perror(filePath.c_str());
                ErrorSystem::FatalError("Fail to open " + filePath);
            }

            std::string fileContents = "";
            std::string line;

            while (std::getline(vertexFile, line))
            {
                fileContents += line + "\n";
            }

            vertexFile.close();

            const char* contentsPtr = fileContents.c_str();
            glShaderSource(id, 1, &contentsPtr, nullptr);

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
                ErrorSystem::FatalError("Shader" + filePath + " failed compiled!");
            }
        }
    }
}