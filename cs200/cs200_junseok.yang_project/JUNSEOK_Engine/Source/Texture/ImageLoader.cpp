/************************************************************************
*	File name : ImageLoader.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION 2019 Fall Semester cs200 class project
*************************************************************************/
#include "ImageLoader.hpp"
#include "../Shader/glCheck/glCheck.hpp"
#include <cassert>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#pragma warning(push)
#pragma warning(disable : 4505) // unreferenced local function has been removed
#pragma warning(disable : 4100) // unreferenced formal parameter
#include <stb_image.h>
#pragma warning(pop)

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include <stb_image_write.h>

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

    glCheck(glGenTextures(1, &(texture.id)));

    glCheck(glBindTexture(GL_TEXTURE_2D, texture.id));
    glCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out_File[0])));

    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));

    glCheck(glGenerateMipmap(GL_TEXTURE_2D));

    glCheck(glBindTexture(GL_TEXTURE_2D, 0));

    texture.width = width;
    texture.height = height;

    return  texture;
}



Image::Image(int pixel_width, int pixel_height, Color color)
    : width(pixel_width), height(pixel_height), pixels(pixel_width * pixel_height, color)
{
}

void Image::ResizeToPixelWidthHeight(int pixel_width, int pixel_height) noexcept
{
    assert(pixel_height > 0 && pixel_width > 0);

    width = pixel_width;
    height = pixel_height;
    pixels.resize(width*height);
}

bool Image::LoadFromPNG(const std::filesystem::path& file_path) noexcept
{
    int channel = ChannelsPerColor;
    unsigned char* file = stbi_load(file_path.generic_string().c_str(), &width, &height, &channel, STBI_rgb_alpha);

    for (int i = 0; i <= width * height * 4; i += 4)
    {
        Color pixelColor = { file[i],file[i + 1],file[i + 2],file[i + 3] };
        pixels.push_back(pixelColor);
    }
    if (pixels.empty() == true)
    {
        return false;
    }
    return true;
}


void Image::SaveToPNG(const std::string& file_path) const
{
    if (pixels.empty())
        return;
    const int stride = 0;
    stbi_write_png(file_path.c_str(), width, height, ChannelsPerColor, &pixels[0], stride);
}

void Image::SetPixel(int column, int row, Color color)
{
    assert(column >= 0 && column < width);
    assert(row >= 0 && row < height);
    pixels[column + row * width] = color;
}

Color* Image::GetPixelsPointer() noexcept
{
    if (pixels.empty() == true)
    {
        return nullptr;
    }
    return &pixels[0];
}

const Color* Image::GetPixelsPointer() const noexcept
{
    if (pixels.empty() == true)
    {
        return nullptr;
    }
    return &pixels[0];
}

int Image::GetPixelsBufferBytesSize() const noexcept
{
    return sizeof(Color)*width*height;
}

void Image::FlipVertically() noexcept
{
    for (int row = 0; row < height / 2; row++)
    {
        for (int column = 0; column < width; column++)
        {
            Color pixelColor = pixels[row*width + column];
            pixels[row*width + column] = pixels[(height - 1 - row)*width + column];
            pixels[(height - 1 - row)* width + column] = pixelColor;
        }
    }
}