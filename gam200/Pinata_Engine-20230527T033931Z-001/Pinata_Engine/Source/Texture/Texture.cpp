/************************************************************************
*	File name : Texture.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION
*************************************************************************/
#include "Texture.hpp"

TextureArray Texture::m_TextureCache;

GLTexture Texture::GetTexture(std::string p_TexturePath)
{
    return m_TextureCache.GetTexture(p_TexturePath);
}

//void Texture::loadFromFile(std::string path)
//{
//    //Load image at specified path
//    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

//        //Color key image
//        SDL_SetColorKey(loadedSurface, SDL_trUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

//        //Create texture from surface pixels

//            //Get image dimensions
//          m_Width = loadedSurface->w;
//            m_Height = loadedSurface->h;

//        //Get rid of old loaded surface
//        SDL_FreeSurface(loadedSurface);
//    }


