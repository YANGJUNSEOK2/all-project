#include "Shader.hpp"

namespace JS_Engine {
    namespace Graphics {

        Shader::Shader(const char *p_VertexPath, const char *p_FragmentPath) : m_VertexPath(p_VertexPath), m_FragmentPath(p_FragmentPath) {
            m_ShaderID = LoadShader();
        }

        Shader::~Shader() {
            glDeleteProgram(m_ShaderID);
        }

        void Shader::ShaderEnable() const {
            glUseProgram(m_ShaderID);
        }

        void Shader::ShaderDisable() const {
            glUseProgram(0);
        }

        void Shader::SetUniformFloat(const GLchar *p_UniformVariable, float p_Value) {
            glUniform1f(GetUniformLocation(p_UniformVariable), p_Value);
        }

        void Shader::SetUniformInteger(const GLchar *p_UniformVariable, int p_Value) {
            glUniform1i(GetUniformLocation(p_UniformVariable), p_Value);
        }

        void Shader::SetUniformVector2(const GLchar *p_UniformVariable, const MathLibrary::Vector2 &p_Vector) {
            glUniform2f(GetUniformLocation(p_UniformVariable), p_Vector.XComponent, p_Vector.YComponent);
        }

        void Shader::SetUniformVector3(const GLchar *p_UniformVariable, const MathLibrary::Vector3 &p_Vector) {
            glUniform3f(GetUniformLocation(p_UniformVariable), p_Vector.XComponent, p_Vector.YComponent, p_Vector.ZComponent);
        }

        void Shader::SetUniformVector4(const GLchar *p_UniformVariable, const MathLibrary::Vector4 &p_Vector) {
            glUniform4f(GetUniformLocation(p_UniformVariable), p_Vector.XComponent, p_Vector.YComponent, p_Vector.ZComponent, p_Vector.WComponent);
        }

        void Shader::SetUniformMatrix(const GLchar *p_UniformVariable, const MathLibrary::Matrix &p_Matrix) {
            glUniformMatrix4fv(GetUniformLocation(p_UniformVariable), 1, GL_FALSE, p_Matrix.Elements);
        }
        GLuint Shader::LoadShader() {
            GLuint Program = glCreateProgram();
            GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
            GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            std::string VertexInfoString = Tools::TextReader::ReadTextFile(m_VertexPath);
            std::string FragmentInfoString = Tools::TextReader::ReadTextFile(m_FragmentPath);
            const char *VertexInfo = VertexInfoString.c_str();
            const char *FragmentInfo = FragmentInfoString.c_str();

            GLint Result;
            glShaderSource(VertexShader, 1, &VertexInfo, NULL);
            glCompileShader(VertexShader);
            glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Result);
            if (Result == GL_FALSE) {
                GLint LogLength;
                glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH, &LogLength);
                std::vector<char> LogError(LogLength);
                glGetShaderInfoLog(VertexShader, LogLength, &LogLength, &LogError[0]);
                std::cout << "[ERROR] VERTEX SHADER COMPILE FAILED" << std::endl;
                std::cout << &LogError[0] << std::endl;
                glDeleteShader(VertexShader);
                return 0;
            }
            glShaderSource(FragmentShader, 1, &FragmentInfo, NULL);
            glCompileShader(FragmentShader);
            glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Result);
            if (Result == GL_FALSE) {
                GLint LogLength;
                glGetShaderiv(FragmentShader, GL_INFO_LOG_LENGTH, &LogLength);
                std::vector<char> LogError(LogLength);
                glGetShaderInfoLog(FragmentShader, LogLength, &LogLength, &LogError[0]);
                std::cout << "[ERROR] FRAGMENT SHADER COMPILE FAILED" << std::endl;
                std::cout << &LogError[0] << std::endl;
                glDeleteShader(FragmentShader);
                return 0;
            }
            glAttachShader(Program, VertexShader);
            glAttachShader(Program, FragmentShader);
            glLinkProgram(Program);
            glDeleteShader(VertexShader);
            glDeleteShader(FragmentShader);
            return Program;
        }

        GLint Shader::GetUniformLocation(const GLchar *p_UniformVariable) {
            return glGetUniformLocation(m_ShaderID, p_UniformVariable);
        }


        MathLibrary::Vector2 Shader::GetMoving() const
        {
            return m_Moving;
        }

        void Shader::SetMoving(const MathLibrary::Vector2 p_Moving)
        {
            m_Moving = p_Moving;
        }
    }
}