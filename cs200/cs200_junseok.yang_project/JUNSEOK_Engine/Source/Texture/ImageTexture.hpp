/************************************************************************
*	File name : ImageTexture.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once

#include <filesystem>

class Image;
class Color4ub;

class[[nodiscard]] Texture230
{
public:
    Texture230() = default;

    bool LoadFromPNG(const std::filesystem::path& file_path) noexcept;
    bool LoadFromImage(const Image& image) noexcept;
    bool LoadFromMemory(int image_width, int image_height, const Color* colors) noexcept;

    static void SelectTextureForSlot(const Texture230& texture, unsigned int slot = 0) noexcept;

    void DeleteTexture() noexcept;

    unsigned int GetTextureHandle() const noexcept { return textureHandle; }
    int          GetWidth() const noexcept { return width; }
    int          GetHeight() const noexcept { return height; }

    ~Texture230() noexcept;
    Texture230(Texture230 && other) noexcept;
    Texture230& operator=(Texture230&& other) noexcept;

public:
    Texture230(const Texture230& other) = delete;
    Texture230& operator=(const Texture230& other) = delete;

private:
    unsigned int textureHandle = 0;
    int          width = 0;
    int          height = 0;
};
