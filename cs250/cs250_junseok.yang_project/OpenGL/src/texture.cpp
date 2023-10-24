/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: texture.cpp
Project: cs250_project
Author: common
Creation date: 5/4/21
******************************************************************/
#define STB_IMAGE_IMPLEMENATION

#include "stb_image.h"

int width, height, nrChannels;
unsigned char* data = stbi_load("resources\\container.jpg", &width, &height, &nrChannels, 0);