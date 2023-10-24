/************************************************************************
*	File name : ImageLoader.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION
*************************************************************************/
#include "ImageLoader.hpp"


GLTexture ImageLoader::LoadPNG(std::string p_FilePath)
{
    GLTexture texture = {};

    std::vector<unsigned char> in_File;
    std::vector<unsigned char> out_File;

    unsigned long width, height;

    if (IOManager::ReadFile(p_FilePath, in_File) == false)
    {
        FindError("Failed to load PNG");
    }

    int errorCode = decodePNG(out_File, width, height, &(in_File[0]), in_File.size());
    if (errorCode != 0)
    {
        FindError("decodePNG failed : " + std::to_string(errorCode));
    }

    glGenTextures(1, &(texture.id));

    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out_File[0]));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    texture.width = width;
    texture.height = height;

    return  texture;
}

