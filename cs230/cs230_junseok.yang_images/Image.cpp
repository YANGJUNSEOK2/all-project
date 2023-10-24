/*
 * Rudy Castan
 * Graphics Library
 * CS230
 */
 /*
 junseok.yang
 assignment6 
 cs230
 spring 2019
 */
#include <CS230/graphics/Image.hpp>
#include <algorithm>
#include <cassert>
#include <filesystem>

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

namespace CS230
{
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
            Color4ub pixelColor = { file[i],file[i + 1],file[i + 2],file[i + 3] };
            pixels.push_back(pixelColor);
        }
        if (pixels.empty() == true)
        {
            return false;
        }
        return true;
    }

    void Image::SaveToPNG(const std::filesystem::path& file_path) const noexcept
    {
        int channel = ChannelsPerColor;
        stbi_write_png(file_path.generic_string().c_str(), width, height, channel, &pixels[0], sizeof(Color4ub)*width);
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
        if (pixels.empty() == true)
        {
            return nullptr;
        }
        return &pixels[0];
    }

    const Color4ub* Image::GetPixelsPointer() const noexcept
    {
        if (pixels.empty() == true)
        {
            return nullptr;
        }
        return &pixels[0];
    }

    int Image::GetPixelsBufferBytesSize() const noexcept
    {
        return sizeof(Color4ub)*width*height;
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
