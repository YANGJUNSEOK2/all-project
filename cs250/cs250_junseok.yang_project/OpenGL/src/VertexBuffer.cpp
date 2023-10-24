/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: VertexBuffer.cpp
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glCreateBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

//VertexBuffer::VertexBuffer()
//{
//	glGenBuffers(1, &m_ID);
//	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
//}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

//void VertexBuffer::SetData(const void* data, unsigned int size) const
//{
//	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
//}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
