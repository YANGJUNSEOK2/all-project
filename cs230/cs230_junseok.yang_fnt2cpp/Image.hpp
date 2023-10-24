/*
 * Rudy Castan
 * Graphics Library
 * CS230
 * Spring 2018
 */
#pragma once
#include "Color4ub.hpp"
#include <filesystem>
#include <vector>

namespace CS230
{
    class Image
    {
    public:
        void ResizeToPixelWidthHeight(int pixel_width, int pixel_height) noexcept;
        bool LoadFromPNG(const std::experimental::filesystem::path& file_path) noexcept;
        void SaveToPNG(const std::experimental::filesystem::path& file_path) const noexcept;

        int GetWidth() const noexcept;
        int GetHeight() const noexcept;

        void            SetPixel(int column, int row, Color4ub color) noexcept;
        Color4ub*       GetPixelsPointer() noexcept;
        const Color4ub* GetPixelsPointer() const noexcept;
        int             GetPixelsBufferBytesSize() const noexcept;
        void            FlipVertically() noexcept;

    private:
        int                   width  = 0;
        int                   height = 0;
        std::vector<Color4ub> pixels{};

        static const int ChannelsPerColor = 4;
    };
}
