/************************************************************************
*	File name : TextureArray.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester
*************************************************************************/
#include "TextureArray.hpp"
#include "../Texture/ImageLoader.hpp"
#include <iostream>

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
