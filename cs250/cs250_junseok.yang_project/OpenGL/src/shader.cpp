/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: shader.cpp
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#include "shader.h"
using namespace MyEngine;

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath, const char* tessControlPath, const char* tessEvaluationPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::string tessControlCode;
	std::string tessEvaluationCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;
	std::ifstream tCShaderFile;
	std::ifstream tEShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	tCShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	tEShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		if (geometryPath != nullptr)
		{
			gShaderFile.open(geometryPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}
		if (tessControlPath != nullptr)
		{
			tCShaderFile.open(tessControlPath);
			std::stringstream tCShaderStream;
			tCShaderStream << tCShaderFile.rdbuf();
			tCShaderFile.close();
			tessControlCode = tCShaderStream.str();
			if (tessEvaluationPath != nullptr)
			{
				tEShaderFile.open(tessEvaluationPath);
				std::stringstream tEShaderStream;
				tEShaderStream << tEShaderFile.rdbuf();
				tEShaderFile.close();
				tessEvaluationCode = tEShaderStream.str();
			}
		}
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// Create Shader and Compile
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	// Check whether compile is successful
	int success = 0;


	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error, Vertex Shader Compilation Failed ! " << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Error, Frag Shader Compilation Failed ! " << infoLog << std::endl;
	}

	unsigned int geometryShader;
	if (geometryPath != nullptr)
	{
		const char* gShaderCode = geometryCode.c_str();
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &gShaderCode, NULL);
		glCompileShader(geometryShader);
		glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
			std::cout << "Error, Geometry Shader Compilation Failed ! " << infoLog << std::endl;
		}
	}

	unsigned int TessControlShader;
	unsigned int TessEvaluationShader;
	if (tessControlPath != nullptr)
	{
		const char* tCShaderCode = tessControlCode.c_str();
		TessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(TessControlShader, 1, &tCShaderCode, NULL);
		glCompileShader(TessControlShader);
		glGetShaderiv(TessControlShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(TessControlShader, 512, NULL, infoLog);
			std::cout << "Error, TessControl Shader Compilation Failed ! " << infoLog << std::endl;
		}
	}
	if (tessEvaluationPath != nullptr)
	{
		const char* tEShaderCode = tessEvaluationCode.c_str();
		TessEvaluationShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(TessEvaluationShader, 1, &tEShaderCode, NULL);
		glCompileShader(TessEvaluationShader);
		glGetShaderiv(TessEvaluationShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(TessEvaluationShader, 512, NULL, infoLog);
			std::cout << "Error, TessEvaluation Shader Compilation Failed ! " << infoLog << std::endl;
		}
	}
	m_ID = glCreateProgram();

	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	if (geometryPath != nullptr)
		glAttachShader(m_ID, geometryShader);
	if (tessEvaluationPath != nullptr)
		glAttachShader(m_ID, TessEvaluationShader);
	if (tessControlPath != nullptr)
		glAttachShader(m_ID, TessControlShader);
	glLinkProgram(m_ID);

	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << "Error, Program Linking Failed ! " << infoLog << std::endl;
	}

	// Delete Shader after linking it to program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometryPath != nullptr)
		glDeleteShader(geometryShader);
	if (tessControlPath != nullptr)
		glDeleteShader(TessControlShader);
	if (tessEvaluationPath != nullptr)
		glDeleteShader(TessEvaluationShader);
}

void Shader::use()
{
	glUseProgram(m_ID);
}

void Shader::Unuse()
{
	glUseProgram(0);
}

void Shader::SetUniform(const std::string& name, GLboolean value) const
{
	GLint location = glGetUniformLocation(m_ID, name.c_str());

	if (location >= 0)
		glUniform1i(location, value);
	else
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
}

void Shader::SetUniform(const std::string& name, GLint value) const
{
	GLint location = glGetUniformLocation(m_ID, name.c_str());

	if (location >= 0)
		glUniform1i(location, value);
	else
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
}

void Shader::SetUniform(const std::string& name, GLuint value) const
{
	GLint location = glGetUniformLocation(m_ID, name.c_str());

	if (location >= 0)
		glUniform1ui(location, value);
	else
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
}

void Shader::SetUniform(const std::string& name, GLfloat value) const
{
	GLint location = glGetUniformLocation(m_ID, name.c_str());

	if (location >= 0)
		glUniform1f(location, value);
	else
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
}

void Shader::SetUniform(const std::string& name, const GLdouble value) const
{
	GLint location = glGetUniformLocation(m_ID, name.c_str());

	if (location >= 0)
		glUniform1d(location, value);
	else
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
}

void Shader::SetUniform(const std::string& name, const glm::vec3& value) const
{
	GLint location = glGetUniformLocation(m_ID, name.c_str());

	if (location >= 0)
		glUniform3f(location, value.x, value.y, value.z);
	else
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;

}

void Shader::SetUniform(const std::string& name, GLfloat x, GLfloat y, GLfloat z) const
{
	GLint location = glGetUniformLocation(m_ID, name.c_str());

	if (location >= 0)
		glUniform3f(location, x, y, z);
	else
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
}

void Shader::SetUniform(const std::string& name, const glm::vec4& value) const
{
	GLint location = glGetUniformLocation(m_ID, name.c_str());

	if (location >= 0)
		glUniform4f(location, value.x, value.y, value.z, value.w);
	else
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
}

void Shader::SetUniform(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const
{
	GLint location = glGetUniformLocation(m_ID, name.c_str());

	if (location >= 0)
		glUniform4f(location, x, y, z, w);
	else
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
}

void Shader::SetUniform(const std::string& name, const glm::mat4& mat) const
{
	GLint location = glGetUniformLocation(m_ID, name.c_str());

	if (location >= 0)
		glUniformMatrix4fv(location, 1, false, &mat[0][0]);
	else
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
}

void Shader::SetUniform(const std::string& name, const glm::mat3& mat) const
{
	GLint location = glGetUniformLocation(m_ID, name.c_str());

	if (location >= 0)
		glUniformMatrix3fv(location, 1, false, &mat[0][0]);
	else
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
}

void MyEngine::Shader::SetUniform1fv(const std::string& name, int count, void* data) const
{
	GLint location = glGetUniformLocation(m_ID, name.c_str());

	if (location >= 0)
		glUniform1fv(location, count, (GLfloat*)data);
	else
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
}



