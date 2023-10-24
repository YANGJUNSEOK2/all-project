/*
junseok.yang
assignment7
cs230
spring 2019
*/
#include <CS230/graphics/BitmapFont.hpp>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <sstream>


namespace CS230
{
    bool BitmapFont::LoadFromFile(const std::filesystem::path& filename)
    {
        if (CanParseFile(filename) == false)
        {
            return false;
        }
        const std::filesystem::path fileDir = filename.parent_path();
        for (const std::wstring& pageName : details.pageNames)
        {
            const std::filesystem::path filePath = fileDir / pageName;
            if (!exists(filePath))
            {
                return false;
            }
            pageTextures.emplace_back();
            const bool loaded = pageTextures.back().LoadFromPNG(filePath.string());

            if (!loaded)
            {
                return false;
            }
        }
        return true;
    }

    bool BitmapFont::LoadDefinition(const std::wstring& font_definition, std::vector<Texture> page_textures)
    {
        std::wistringstream stream(font_definition);
        if (!CanParseStream(stream))
            return false;
        pageTextures = std::move(page_textures);
        return pageTextures.size() == details.pagesCount;
    }

    const BitmapFont::information& BitmapFont::GetInformation() const noexcept
    {
        return details;
    }

    BitmapFont::character BitmapFont::GetCharacter(wchar_t character_id) const noexcept
    {
        auto check = characters.find(character_id);

        if (check == characters.end())
        {
            check = characters.find(wchar_t(-1));
            if (check == characters.end())
            {
                return character{};
            }
            return characters.at(wchar_t(-1));
        }
        return characters.at(character_id);
    }

    unsigned short BitmapFont::GetLineHeight() const noexcept
    {
        return details.lineHeight;
    }

    const Texture& BitmapFont::GetTexture(int page_index) const noexcept
    {
        //1.details.pagesCount;
        assert(details.pagesCount > 0);
        assert(page_index >= 0 && page_index < details.pagesCount);
        return pageTextures[page_index];
    }

    bool BitmapFont::HasCharacter(wchar_t character_id) const noexcept
    {
        auto character = characters.find(character_id);
        if (character == characters.end())
        {
            return false;
        }
        return true;
    }

    bool BitmapFont::CanParseFile(const std::filesystem::path& filename)
    {
        std::wifstream winfile(filename);

        return CanParseStream(winfile);
    }

    bool BitmapFont::CanParseStream(std::wistream& stream)
    {
        std::wstring Line;
        std::wstring Read, Key, Value;
        std::size_t i;

        while (!stream.eof())
        {
            information my_information;
            character my_character;
            std::wstringstream LineStream;
            std::getline(stream, Line);
            LineStream << Line;

            //read the line's type
            LineStream >> Read;
            if (Read == L"info")
            {
                while (!LineStream.eof())
                {
                    std::wstringstream Converter;
                    LineStream >> Read;
                    i = Read.find('=');
                    Key = Read.substr(0, i);
                    Value = Read.substr(i + 1);

                    //assign the correct value
                    Converter << Value;
                    if (Key == L"face") {
                        Value = Read.substr(i);
                        LineStream >> Read;
                        std::size_t size = Read.find(L"\"", i);
                        Value += L" ";
                        Value += Read.substr(0, size);
                        Converter << Value;
                        Converter >> details.fontName; 
                    }
                    else if (Key == L"size") {
                        Converter >> details.fontSize;
                    }
                }
            }
            else if (Read == L"common")
            {
                //this holds common data
                while (!LineStream.eof())
                {
                    std::wstringstream Converter;
                    LineStream >> Read;
                    i = Read.find('=');
                    Key = Read.substr(0, i);
                    Value = Read.substr(i + 1);

                    //assign the correct value
                    Converter << Value;
                    if (Key == L"lineHeight") {
                        Converter >> details.lineHeight;
                    }
                    else if (Key == L"scaleW") {
                        Converter >> details.imageWidth;
                    }
                    else if (Key == L"scaleH") {
                        Converter >> details.imageHeight;
                    }
                    else if (Key == L"pages") {
                        Converter >> details.pagesCount;
                    }
                }
            }
            else if (Read == L"page")
            {

                while (!LineStream.eof())
                {
                    std::wstringstream Converter;
                    LineStream >> Read;
                    i = Read.find('=');
                    Key = Read.substr(0, i);
                    Value = Read.substr(i + 1);

                    //assign the correct value
                    Converter << Value;
                    if (Key == L"file") {
                        details.pageNames.push_back(Value);
                        details.pageNames.back().pop_back();
                        details.pageNames.back() = details.pageNames.back().substr(1);
                    }
                }
            }
            else if (Read == L"char")
            {
                while (!LineStream.eof())
                {
                    std::wstringstream Converter;
                    LineStream >> Read;
                    i = Read.find('=');
                    Key = Read.substr(0, i);
                    Value = Read.substr(i + 1);
                    Converter << Value;
                    if (Key == L"id") {
                        my_character.id = wchar_t(std::stoi(Value));
                    }
                    else if (Key == L"x"){
                        Converter >> my_character.x;
                    }
                    else if (Key == L"y") {
                        Converter >> my_character.y;
                    }
                    else if (Key == L"width") {
                        Converter >> my_character.width;
                    }
                    else if (Key == L"height") {
                        Converter >> my_character.height;
                    }
                    else if (Key == L"xoffset") {
                        Converter >> my_character.xOffset;
                    }
                    else if (Key == L"yoffset") {
                        Converter >> my_character.yOffset;
                    }
                    else if (Key == L"xadvance") {
                        Converter >> my_character.xAdvance;
                    }
                    else if (Key == L"page") {
                        short page;
                        Converter >> page;
                        my_character.page = static_cast<unsigned char>(page);
                    }
                }
                characters.insert_or_assign(my_character.id, my_character);
            }
        }
        return true;
    }
}


