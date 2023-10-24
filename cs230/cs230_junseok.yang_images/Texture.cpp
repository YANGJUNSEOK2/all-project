/*
junseok.yang
assignment6
cs230
spring 2019
*/
#include <CS230/graphics/Image.hpp>
#include <CS230/graphics/Texture.hpp>
#include <CS230/graphics/glCheck.hpp>
#include <GL/glew.h>
#include <cassert>
#include <filesystem>

namespace CS230
{
    Texture::Texture(Texture&& other) noexcept
        : textureHandle{ other.textureHandle }, width{ other.width }, height{ other.height }
    {
        other.textureHandle = 0;
        other.width = 0;
        other.height = 0;
    }

    Texture& Texture::operator=(Texture&& other) noexcept
    {
        if (this == &other)
            return *this;
        DeleteTexture();
        textureHandle = other.textureHandle;
        width = other.width;
        height = other.height;
        other.textureHandle = 0;
        other.width = 0;
        other.height = 0;
        return *this;
    }
    bool Texture::LoadFromPNG(const std::filesystem::path& file_path) noexcept
    {
        Image loadFromPNG;
        loadFromPNG.LoadFromPNG(file_path);
        return LoadFromImage(loadFromPNG);
    }

    bool Texture::LoadFromImage(const Image& image) noexcept
    {
        return LoadFromMemory(image.GetWidth(), image.GetHeight(), image.GetPixelsPointer());
    }

    bool Texture::LoadFromMemory(int image_width, int image_height, const Color4ub* colors) noexcept
    {
        assert(image_width > 0 && image_height > 0);
        assert(colors != nullptr);
        width = image_width;
        height = image_height;
        glCheck(glGenTextures(1, &textureHandle));
        glCheck(glBindTexture(GL_TEXTURE_2D, textureHandle));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        glCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, colors));
        glCheck(glBindTexture(GL_TEXTURE_2D, textureHandle));

        if (textureHandle == NULL)
        {
            return false;
        }
        return glGetError()==GL_NO_ERROR;
    }

    void Texture::SelectTextureForSlot(const Texture& texture, unsigned int slot) noexcept
    {
        glCheck(glActiveTexture(GL_TEXTURE0-slot));
        glCheck(glBindTexture(GL_TEXTURE_2D, texture.textureHandle));
    }

    void Texture::DeleteTexture() noexcept
    {
        glCheck(glDeleteTextures(1, &textureHandle));
    }

    Texture::~Texture() noexcept
    {
        DeleteTexture();
    }

}
