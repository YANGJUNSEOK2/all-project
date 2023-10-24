/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: TextureBuffer.cpp
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#include "TextureBuffer.h"

unsigned int TextureBuffer::texCount = 0;

TextureBuffer::TextureBuffer(const char* path)
{
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	unsigned char* buffer = stbi_load(path, &m_width, &m_height, &m_nrChannels, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(buffer);

	texNum = texCount;
	++texCount;
}

TextureBuffer::~TextureBuffer()
{
	glDeleteTextures(1, &m_ID);
}

void TextureBuffer::Bind() const
{
	glActiveTexture(GL_TEXTURE0 + texNum);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void TextureBuffer::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
