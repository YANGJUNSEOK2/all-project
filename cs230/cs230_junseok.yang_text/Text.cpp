/*
junseok.yang
assignment7
cs230
spring 2019
*/
#include <CS230/graphics/BitmapFont.hpp>
#include <CS230/graphics/Mesh.hpp>
#include <CS230/graphics/StockShaders.hpp>
#include <CS230/graphics/Text.hpp>

namespace CS230
{
    Text::Text(std::wstring text_string, const BitmapFont& text_font) noexcept
    {
        string = text_string;
        font = &text_font;
        InitializeWithEmptyVertices();
    }

    std::vector<std::pair<const Vertices*, const Texture*>> Text::GetVerticesWithMatchingTextures() const noexcept
    {
        std::vector<std::pair<const Vertices*, const Texture*>> vec;

        for (int i = 0; i < font->GetInformation().pagesCount; i++)
        {
            std::pair vecCopy(&vertices[i], &font->GetTexture(i));
            vec.push_back(vecCopy);
        }
        BuildNewMeshesIfNeeded();
        return vec;
    }

    std::wstring Text::GetString() const noexcept
    {
        return string;
    }

    void Text::SetString(const std::wstring& text_string) noexcept
    {
        string = text_string;
    }

    const BitmapFont* Text::GetFont() const noexcept
    {
        return font;
    }

    void Text::SetFont(const BitmapFont& text_font) noexcept
    {
        font = &text_font;
    }

    void Text::InitializeWithEmptyVertices() const noexcept
    {
        for (int i = 0; i < font->GetInformation().pagesCount; i++)
        {
            Mesh page;
            Vertices my_vertices;
            my_vertices.InitializeWithMeshAndLayout(page, SHADER::textured_vertex_layout());
            vertices.insert_or_assign(i, std::move(my_vertices));
        }
    }

    void Text::BuildNewMeshesIfNeeded() const noexcept
    {
        vector2 cursor = { 0, 0 };
        std::vector<Mesh> vecMesh;
        for (int i = 0; i < font->GetInformation().pagesCount; i++)
        {
            Mesh mesh;
            vecMesh.push_back(mesh);
        }


        for (auto ch : string)
        {

            if (ch == L' ')
            {
                if(font->HasCharacter(ch)==false)
                {
                    ch = font->GetInformation().fontSize;
                }
                cursor.x += font->GetCharacter(ch).xAdvance;
            }
            else if (ch == L'\t')
            {
                cursor.x += 4 * font->GetCharacter(ch).xAdvance;
            }
            else if (ch == L'\n')
            {
                cursor.y -= font->GetInformation().lineHeight;
                cursor.x = 0;
            }
            else
            {
                float left = cursor.x + float(font->GetCharacter(ch).xOffset);
                float right = left + float(font->GetCharacter(ch).width);
                float bottom = (float(font->GetCharacter(ch).yOffset) + float(font->GetCharacter(ch).height)) * (- 1) + float(font->GetLineHeight()) + cursor.y;
                float top = bottom + float(font->GetCharacter(ch).height);

                float left_texel = float(font->GetCharacter(ch).x);
                float left_u = left_texel / float(font->GetInformation().imageWidth);
                float right_u = (font->GetCharacter(ch).x + font->GetCharacter(ch).width) / float(font->GetInformation().imageWidth);
                float bottom_v = (float(font->GetCharacter(ch).y) + float(font->GetCharacter(ch).height)) / float(font->GetInformation().imageHeight);
                float top_v = float(font->GetCharacter(ch).y) / float(font->GetInformation().imageHeight);

                vecMesh.at(font->GetCharacter(ch).page).SetPointListType(PointListPattern::Triangles);

                vecMesh.at(font->GetCharacter(ch).page).AddPoint({ left, top });
                vecMesh.at(font->GetCharacter(ch).page).AddPoint({ left, bottom });
                vecMesh.at(font->GetCharacter(ch).page).AddPoint({ right, top });

                vecMesh.at(font->GetCharacter(ch).page).AddTextureCoordinate({ left_u,top_v });
                vecMesh.at(font->GetCharacter(ch).page).AddTextureCoordinate({ left_u,bottom_v });
                vecMesh.at(font->GetCharacter(ch).page).AddTextureCoordinate({ right_u,top_v });

                vecMesh.at(font->GetCharacter(ch).page).AddPoint({ right, top });
                vecMesh.at(font->GetCharacter(ch).page).AddPoint({ left, bottom });
                vecMesh.at(font->GetCharacter(ch).page).AddPoint({ right, bottom });

                vecMesh.at(font->GetCharacter(ch).page).AddTextureCoordinate({ right_u,top_v });
                vecMesh.at(font->GetCharacter(ch).page).AddTextureCoordinate({ left_u,bottom_v });
                vecMesh.at(font->GetCharacter(ch).page).AddTextureCoordinate({ right_u,bottom_v });

                cursor.x += font->GetCharacter(ch).xAdvance;
            }
            for (int i = 0; i < font->GetInformation().pagesCount; i++)
            {
                vertices.find(i)->second.InitializeWithMeshAndLayout(vecMesh.at(i), SHADER::textured_vertex_layout());
            }

        }
    }
}
