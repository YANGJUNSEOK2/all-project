/************************************************************************
*	File name : ImageLoader.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION
*************************************************************************/
#pragma once
#include "../Texture/GLTexture.hpp"
#include <string>
#include "../Texture/picoPNG.hpp"
#include "../IO_Manager/Image_IO.hpp"
#include "../Error/Error.h"


class ImageLoader
{
public:
    static GLTexture LoadPNG(std::string p_FilePath);
};

