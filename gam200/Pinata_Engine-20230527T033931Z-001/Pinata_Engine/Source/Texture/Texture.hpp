/************************************************************************
*	File name : Texture.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION
*************************************************************************/
#pragma once
#include "TextureArray.hpp"
#include <SDL.h>
#include <string>


class Texture
{
public:
    static GLTexture GetTexture(std::string p_TexturePath);

private:
    static TextureArray m_TextureCache;
};
