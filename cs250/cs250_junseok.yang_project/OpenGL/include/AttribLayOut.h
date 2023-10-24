/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: AttribLayOut.h
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#ifndef ATTRIBLAYOUT_H
#define ATTRIBLAYOUT_H

#include <vector>
#include <glad/glad.h>

struct VertexBufferElement
{
	unsigned int count;
	unsigned int type;
	unsigned char b_isNormalized;

	static unsigned int SizeOf(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT		  : return sizeof(GLfloat);
			case GL_INT			  : return sizeof(GLint);
			case GL_UNSIGNED_INT  : return sizeof(GLuint);
			case GL_UNSIGNED_BYTE : return sizeof(GLbyte);
		}

		_ASSERT(0);
		return 0;
	}
};

class AttribLayOut
{
private:
	std::vector<VertexBufferElement> m_layout;
	
	unsigned int m_stride;
public:

	inline std::vector<VertexBufferElement> GetLayOut() const { return m_layout; }
	inline unsigned int GetStride() const { return m_stride; }

	/*
	* @par
	*/
	template<unsigned int T>
	void Add(unsigned int count, unsigned char normalized = GL_FALSE)
	{
		m_layout.push_back({ count, T, normalized });
		m_stride += count * VertexBufferElement::SizeOf(T);
	}
};

#endif // !ATTRIBLAYOUT_H



