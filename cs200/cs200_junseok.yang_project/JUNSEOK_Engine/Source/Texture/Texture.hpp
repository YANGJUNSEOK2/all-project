/************************************************************************
*	File name : Texture.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION cs200 class project
*************************************************************************/
#pragma once
#include "TextureArray.hpp"
#include <SDL.h>
#include <string>
#include <filesystem>
#include "../Vertex/Vertex.hpp"

class Texture
{
public:

    static GLTexture GetTexture(std::string p_TexturePath);
   
private:

    unsigned int textureHandle = 0;
    int          width = 0;
    int          height = 0;

    static TextureArray m_TextureCache;
};
