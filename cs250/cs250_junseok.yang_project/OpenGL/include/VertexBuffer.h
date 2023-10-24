/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: VertexBuffer.h
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <glad/glad.h>

//VBO
class VertexBuffer
{
private:
	unsigned int m_ID;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer() = delete;
	~VertexBuffer();

	//void SetData(const void* data, unsigned int size) const;

	void Bind() const;
	void UnBind() const;
};

#endif // !VERTEXBUFFER_H
