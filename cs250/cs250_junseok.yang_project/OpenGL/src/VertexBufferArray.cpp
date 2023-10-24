/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: VertexBufferArray.cpp
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#include "VertexBufferArray.h"
#include "VertexBuffer.h"
#include "AttribLayOut.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ID);
	glBindVertexArray(m_ID);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &m_ID);
}


void VertexArray::AddBuffer(VertexBuffer& vbo, AttribLayOut& layout)
{
	Bind();
	vbo.Bind();

	const std::vector<VertexBufferElement> elements = layout.GetLayOut();

	unsigned int lastIndex = static_cast<unsigned int>(elements.size());
	unsigned int offset = 0;
	for (unsigned int i = 0; i < lastIndex; ++i)
	{
		const VertexBufferElement elem = elements[i];
		glVertexAttribPointer(i, elem.count, elem.type, elem.b_isNormalized, layout.GetStride(), (const void*)offset);
		glEnableVertexAttribArray(i);
		offset += elem.count * VertexBufferElement::SizeOf(elem.type);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_ID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}
