#pragma once
#include <iostream>
#include <vector>
#include <glew.h>
#include "../../MathLibrary/MathLibrary.hpp"
#include "../../Tools/TextReader.hpp"

namespace JS_Engine {
    namespace Graphics {
        class Shader {
        public:

            Shader(const char *p_VertexPath, const char *p_FragmentPath);
            ~Shader();
            //Enable Shader
            void ShaderEnable() const;
            //Disable Shader
            void ShaderDisable() const;
            //Set Uniform Information For Float
            void SetUniformFloat(const GLchar *p_UniformVariable, float p_Value);
            //Set Uniform Information For Integer
            void SetUniformInteger(const GLchar *p_UniformVariable, int p_Value);
            //Set Uniform Information For Vector2
            void SetUniformVector2(const GLchar *p_UniformVariable, const MathLibrary::Vector2 &p_Vector);
            //Set Uniform Information For Vector3
            void SetUniformVector3(const GLchar *p_UniformVariable, const MathLibrary::Vector3 &p_Vector);
            //Set Uniform Information For Vector4
            void SetUniformVector4(const GLchar *p_UniformVariable, const MathLibrary::Vector4 &p_Vector);
            //Set Uniform Information For Matrix
            void SetUniformMatrix(const GLchar *p_UniformVariable, const MathLibrary::Matrix &p_Matrix);

            MathLibrary::Vector2 GetMoving() const;
            void SetMoving(const MathLibrary::Vector2 p_Moving);
        private:
            GLuint      m_ShaderID;
            const char *m_VertexPath;
            const char *m_FragmentPath;
            //Load Shader
            GLuint LoadShader();
            //Get Uniform Location
            GLint GetUniformLocation(const GLchar *p_UniformVariable);

            MathLibrary::Vector2 m_Moving{};
        };
    }
}