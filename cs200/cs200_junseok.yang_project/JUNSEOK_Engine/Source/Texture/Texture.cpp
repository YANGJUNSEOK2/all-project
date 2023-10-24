/************************************************************************
*	File name : Texture.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION cs200 class project
*************************************************************************/
#include "Texture.hpp"

TextureArray Texture::m_TextureCache;


GLTexture Texture::GetTexture(std::string p_TexturePath)
{
    return m_TextureCache.GetTexture(p_TexturePath);
}
