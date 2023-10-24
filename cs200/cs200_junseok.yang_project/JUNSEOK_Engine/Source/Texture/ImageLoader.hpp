/************************************************************************
*	File name : ImageLoader.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION 2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include "../Texture/GLTexture.hpp"
#include <string>
#include "../Texture/picoPNG.hpp"
#include "../IO_Manager/Image_IO.hpp"
#include "../Error/Error.h"
#include "../Vertex/Vertex.hpp"
#include <vector>
#include "Texture.hpp"
#include "../MathLibrary/Vector3.hpp"

class ImageLoader
{
public:
    static GLTexture LoadPNG(std::string p_FilePath);

};

class Image
{
public:
    explicit Image(int pixel_width = 0, int pixel_height = 0, Color color = Color{});
    void SaveToPNG(const std::string& file_path) const;
    void SetPixel(int column, int row, Color color);
    Color TextureColor(const Texture& option, Color& Color, Vector3<float>& Texel);
    void ResizeToPixelWidthHeight(int pixel_width, int pixel_height) noexcept;
    bool LoadFromPNG(const std::filesystem::path& file_path) noexcept;
    Color* GetPixelsPointer() noexcept;
    const Color* GetPixelsPointer() const noexcept;
    int GetPixelsBufferBytesSize() const noexcept;
    void FlipVertically() noexcept;
    int GetWidth() const noexcept { return width; }
    int GetHeight() const noexcept { return height; }
private:
    int width = 0;
    int height = 0;
    std::vector<Color> pixels{};
    GLubyte r, g, b, a;
    static const int ChannelsPerColor = sizeof(Color{ r, g, b, a });
};
