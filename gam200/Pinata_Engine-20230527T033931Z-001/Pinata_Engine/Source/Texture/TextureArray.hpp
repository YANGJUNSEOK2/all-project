/************************************************************************
*	File name : TextureArray.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester
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

private:
    std::map<std::string, GLTexture> m_TextureMap;
};

