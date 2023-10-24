/*
 * Rudy Castan
 * Graphics Library
 * CS230
 */
 /*
 junseok.yang
 assignment8
 cs230
 spring 2019
 */
#include <cassert>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#pragma warning(push)
#pragma warning(disable : 4505) // unreferenced local function has been removed
#pragma warning(disable : 4100) // unreferenced formal parameter
#include "stb_image.h"
#pragma warning(pop)

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "Image.hpp"
#include "Color4ub.hpp"

namespace CS230
{
    bool Image::LoadFromPNG(const std::experimental::filesystem::path& file_path) noexcept
    {
        int channel = ChannelsPerColor;
        unsigned char* file = stbi_load(file_path.generic_string().c_str(), &width, &height, &channel, STBI_rgb_alpha);

        for (int i = 0; i <= width * height * 4; i += 4)
        {
            Color4ub pixelColor = { file[i],file[i + 1],file[i + 2],file[i + 3] };
            pixels.push_back(pixelColor);
        }
        if (pixels.empty() == true)
        {
            return false;
        }
        return true;
    }

    int Image::GetWidth() const noexcept
    {
        return width;
    }

    int Image::GetHeight() const noexcept
    {
        return height;
    }

    void Image::SetPixel(int column, int row, Color4ub color) noexcept
    {
        assert(row >= 0 && row <= height);
        assert(column >= 0 && column <= width);
        pixels[(row *width) + column] = color;
    }

    Color4ub* Image::GetPixelsPointer() noexcept
    {
        if (pixels.empty())
        {
            return nullptr;
        }
        return &pixels.front();
    }

    const Color4ub* Image::GetPixelsPointer() const noexcept
    {
        if (pixels.empty())
        {
            return nullptr;
        }
        return &pixels.front();
    }

    int Image::GetPixelsBufferBytesSize() const noexcept
    {
        return width * height;
    }

    void Image::FlipVertically() noexcept
    {
        for (int row = 0; row < height / 2; row++)
        {
            for (int column = 0; column < width; column++)
            {
                Color4ub pixelColor = pixels[row*width + column];
                pixels[row*width + column] = pixels[(height-1 - row)*width+column];
                pixels[(height-1 - row)* width+column] = pixelColor;
            }
        }
    }
}
