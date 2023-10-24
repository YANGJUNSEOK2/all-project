#pragma once

#include<string>
#include <glew.h>
#include "../../Error/Error.hpp"

namespace JS_Engine {
    namespace MainSystem {
        class GLSLProgram
        {
        public:
            GLSLProgram();
            ~GLSLProgram();

            void compileShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath);

            void linkShaders();

            void addAttribute(const std::string& attributeName);

            GLint getUniformLocation(const std::string& p_uniformName);

            void useEnable();
            void unUseDiable();
        private:
            void compileShader(const std::string& filePath, GLint id);

            int m_NumAttribute;
            GLuint m_ProgramID;
            GLuint m_VertexShaderID;
            GLuint m_FragmentShaderID;
        };
    }
}
