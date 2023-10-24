/************************************************************************
*	File name : TextureArray.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once

#include <map>
#include "../Texture/GLTexture.hpp"
#include <string>


class TextureArray
{
public:
    TextureArray();
    ~TextureArray();

    GLTexture GetTexture(std::string p_TexturePath);
    static void SelectTextureForSlot(const TextureArray& texture, unsigned int slot = 0) noexcept;
private:
    std::map<std::string, GLTexture> m_TextureMap;
    GLTexture m_id;
};

