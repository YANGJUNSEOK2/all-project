/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: TextureBuffer.h
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#ifndef TEXTUREBUFFER_H
#define TEXTUREBUFFER_H

#include <glad/glad.h>
#include "stb_image.h"

class TextureBuffer
{
private:
	unsigned int m_ID;

	unsigned int texNum;

	int m_width;
	int m_height;
	int m_nrChannels;

	static unsigned int texCount;

public:
	inline int getTextNum() const {
		return texNum;
	}

	TextureBuffer(const char* path);
	~TextureBuffer();

	void Bind() const;
	void UnBind() const;
};

#endif // !TEXTUREBUFFER_H
