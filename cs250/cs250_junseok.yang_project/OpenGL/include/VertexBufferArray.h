/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: TextureBufferArray.h
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#ifndef VERTEXBUFFERARRAY_H
#define VERTEXBUFFERARRAY_H

class VertexBuffer;
class AttribLayOut;

class VertexArray
{
private:
	unsigned int m_ID;

public:

	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vbo, AttribLayOut& layout);

	void Bind() const;
	void UnBind() const;
};

#endif // !VERTEXBUFFERARRAY_H
