/************************************************************************
*	File name : TextureArray.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/
#include "TextureArray.hpp"
#include "../Texture/ImageLoader.hpp"
#include <iostream>
#include "../Shader/glCheck/glCheck.hpp"

TextureArray::TextureArray()
{
}

TextureArray::~TextureArray()
{
}

GLTexture TextureArray::GetTexture(std::string p_TexturePath)
{
    auto temp = m_TextureMap.find(p_TexturePath);

    //check if its not in the map
    if (temp == m_TextureMap.end())
    {
        //Load texture
        GLTexture new_PNG = ImageLoader::LoadPNG(p_TexturePath);
        //Insert it into the map
        m_TextureMap.insert(make_pair(p_TexturePath, new_PNG));

        std::cout << "Used cache textured." << std::endl;
        return new_PNG;
    }
    return temp->second;
}

void TextureArray::SelectTextureForSlot(const TextureArray& texture, unsigned slot) noexcept
{
    glCheck(glActiveTexture(GL_TEXTURE0 - slot));
    glCheck(glBindTexture(GL_TEXTURE_2D, texture.m_id.id));
}