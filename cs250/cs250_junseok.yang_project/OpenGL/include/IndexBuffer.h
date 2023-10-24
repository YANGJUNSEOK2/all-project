/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: IndexBuffer.h
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

// EBO
class IndexBuffer
{
private:
	unsigned int m_ID;
public:
	IndexBuffer(const void* data, unsigned int size);
	IndexBuffer() = delete;
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;
};

#endif // !INDEXBUFFER_H
