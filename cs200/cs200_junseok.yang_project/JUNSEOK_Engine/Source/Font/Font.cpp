/************************************************************************
*   File name : Font.cpp
*   Project name : Pinata
* Author       Primary author : Junseok Yang
*                 Secondary author :
*                 Others :
*
*	2019 Fall Semester cs200 class project
*************************************************************************/
#include "Font.hpp"
#include "../Sprite/SpriteBatch/SpriteBatch.hpp"
#include <SDL.h>

#define MAX_TEXTURE_SIZE 4096

Font::Font(const char* font, int size, char start, char end)
{
    init(font, size, start, end);
}

void Font::init(const char* font, int size)
{
    init(font, size, FIRST, LAST);
}

void Font::init(const char* font, int size, char start, char end)
{
    if (!TTF_WasInit())
    {
        TTF_Init();
    }
    TTF_Font* ttf = TTF_OpenFont(font, size);
    if (ttf == nullptr)
    {
        fprintf(stderr, "Failed to open TTF font %s\n", font);
        fflush(stderr);
        throw 281;
    }
    m_fontH = TTF_FontHeight(ttf);
    m_Start = start;
    m_Length = end - start + 1;
    int material = size / 8;

    Vector4<int>* textRect = new Vector4<int>[m_Length];
    int i = 0, advance;
    for (char c = start; c <= end; c++)
    {
        TTF_GlyphMetrics(ttf, c, &textRect[i].x, &textRect[i].z, &textRect[i].y, &textRect[i].w, &advance);
        textRect[i].z -= textRect[i].x;
        textRect[i].x = 0;
        textRect[i].w -= textRect[i].y;
        textRect[i].y = 0;
        i++;
    }

    int rows = 1, w, h, foundWidth = 0, foundHeight = 0, foundRows = 0;
    int area = MAX_TEXTURE_SIZE * MAX_TEXTURE_SIZE;
    std::vector<int>* foundPartition = nullptr;
    while (rows <= m_Length)
    {
        h = rows * (material + m_fontH) + material;
        auto textRow = createRows(textRect, m_Length, rows, material, w);

        w--;
        int w_pi = 1;
        while (w > 0)
        {
            w >>= 1;
            w_pi <<= 1;
        }
        w = w_pi;

        h--;
        int h_pi = 1;
        while (h > 0)
        {
            h >>= 1;
            h_pi <<= 1;
        }
        h = h_pi;

        if (w > MAX_TEXTURE_SIZE || h > MAX_TEXTURE_SIZE)
        {
            rows++;
            delete[] textRow;
            continue;
        }

        if (area >= w * h)
        {
            if (foundPartition)
            {
                delete[] foundPartition;
            }
            foundPartition = textRow;
            foundWidth = w;
            foundHeight = h;
            foundRows = rows;
            area = foundWidth * foundHeight;
            rows++;
        }
        else
        {
            delete[] textRow;
            break;
        }
    }

    if (!foundPartition)
    {
        fprintf(stderr, "Failed to Map TTF font %s to texture. Try lowering resolution.\n", font);
        fflush(stderr);
        throw 282;
    }
    glGenTextures(1, &m_textID);
    glBindTexture(GL_TEXTURE_2D, m_textID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, foundWidth, foundHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    SDL_Color text_Color = { 255, 255, 255, 255 };
    int material_H = material;
    for (int row_num = 0; row_num < foundRows; row_num++) {
        int material_W = material;
        for (size_t column_num = 0; column_num < foundPartition[row_num].size(); column_num++) {
            int text_num = foundPartition[row_num][column_num];

            SDL_Surface* textSurface = TTF_RenderGlyph_Blended(ttf, (char)(start + text_num), text_Color);

            //calculate multi pixel
            unsigned char* textPixel = (unsigned char*)textSurface->pixels;
            int columnPixel = textSurface->w * textSurface->h * 4;
            for (int i = 0; i < columnPixel; i += 4) {
                float num = textPixel[i + 3] / 255.0f;
                textPixel[i] = (unsigned char)((float)textPixel[i] * num);
                textPixel[i + 1] = textPixel[i];
                textPixel[i + 2] = textPixel[i];
            }

            // image update coordinate
            glTexSubImage2D(GL_TEXTURE_2D, 0, material_W, foundHeight - material_H - 1 - textSurface->h, textSurface->w, textSurface->h, GL_BGRA, GL_UNSIGNED_BYTE, textSurface->pixels);
            textRect[text_num].x = material_W;
            textRect[text_num].y = material_H;
            textRect[text_num].z = textSurface->w;
            textRect[text_num].w = textSurface->h;

            SDL_FreeSurface(textSurface);
            textSurface = nullptr;

            material_W += textRect[text_num].z + material;
        }
        material_H += m_fontH + material;
    }

    // Draw text
    int material_Row = material - 1;
    int* pureWhiteSquare = new int[material_Row * material_Row];
    memset(pureWhiteSquare, 0xffffffff, material_Row * material_Row * sizeof(int));
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, material_Row, material_Row, GL_RGBA, GL_UNSIGNED_BYTE, pureWhiteSquare);
    delete[] pureWhiteSquare;
    pureWhiteSquare = nullptr;

    // texture parameter setting
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Create sprite text
    m_textSize = new TextSize[m_Length + 1];
    for (i = 0; i < m_Length; i++) {
        m_textSize[i].text = (char)(start + i);
        m_textSize[i].position = Vector2<float>(static_cast<float>(textRect[i].z), static_cast<float>(textRect[i].w));
        m_textSize[i].uv = Vector4<float>((float)textRect[i].x / (float)foundWidth, -(float)textRect[i].y / (float)foundHeight, (float)textRect[i].z / (float)foundWidth, -(float)textRect[i].w / (float)foundHeight);
    }
    m_textSize[m_Length].text = ' ';
    m_textSize[m_Length].position = m_textSize[0].position;
    m_textSize[m_Length].uv = Vector4<float>(0, 0, (float)material_Row / (float)foundWidth, (float)material_Row / (float)foundHeight);

    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] textRect;
    delete[] foundPartition;
    TTF_CloseFont(ttf);
}

void Font::destroy()
{
    if (m_textID != 0)
    {
        glDeleteTextures(1, &m_textID);
        m_textID = 0;
    }
    if (m_textSize)
    {
        delete[] m_textSize;
        m_textSize = nullptr;
    }
}

std::vector<int>* Font::createRows(Vector4<int>* rect, int rectLength, int row, int matarial, int& width)
{
    // Blank initialize
    std::vector<int>* list = new std::vector<int>[row]();
    int* columnW = new int[row]();
    for (int i = 0; i < row; i++)
    {
        columnW[i] = matarial;
    }

    // Loop through all glyphs
    for (int i = 0; i < rectLength; i++)
    {
        // Find row for placement
        int row = 0;
        for (int row_tmp = 1; row_tmp < row; row_tmp++)
        {
            if (columnW[row_tmp] < columnW[row])
            {
                row = row_tmp;
            }
        }

        // Add width to that row
        columnW[row] += rect[i].z + matarial;

        // Add glyph to the row list
        list[row].push_back(i);
    }

    // Find the max width
    width = 0;
    for (int i = 0; i < row; i++) {
        if (columnW[i] > width)
        {
            width = columnW[i];
        }
    }

    return list;
}

Vector2<float> Font::text_dimension_check(const char* charSize)
{
    Vector2<float> size(0.f, static_cast<float>(m_fontH));
    float columnWidth = 0;
    for (int i = 0; charSize[i] != 0; i++)
    {
        char c = charSize[i];
        if (charSize[i] == '\n')
        {
            size.y += m_fontH;
            if (size.x < columnWidth)
            {
                size.x = columnWidth;
            }
            columnWidth = 0;
        }
        else
        {
            int check = c - m_Start;
            if (check < 0 || check >= m_Length)
            {
                check = m_Length;
            }
            columnWidth += m_textSize[check].position.x;
        }
    }
    if (size.x < columnWidth)
        size.x = columnWidth;
    return size;
}

void Font::Draw(SpriteBatch& sprite, const char* str, Vector2<float> position, Vector2<float> scaling, float depth, Color font_Color, TextPosition textPositon_choice)
{
    Vector2<float> p_Position = position;
    // Apply TextPosition
    if (textPositon_choice == TextPosition::MIDDLE)
    {
        p_Position.x -= text_dimension_check(str).x * scaling.x / 2;
    }
    else if (textPositon_choice == TextPosition::RIGHT)
    {
        p_Position.x -= text_dimension_check(str).x * scaling.x;
    }
    for (int i = 0; str[i] != 0; i++)
    {
        char c = str[i];
        if (str[i] == '\n') {
            p_Position.y += m_fontH * scaling.y;
            p_Position.x = position.x;
        }
        else
        {
            // Check for correct text
            int text_row_position = c - m_Start;
            if (text_row_position < 0 || text_row_position >= m_Length)
                text_row_position = m_Length;
            Vector4<float> destRect(p_Position.x, p_Position.y, (m_textSize[text_row_position].position * scaling).x, (m_textSize[text_row_position].position * scaling).y);
            sprite.Draw(destRect, m_textSize[text_row_position].uv, m_textID, depth, font_Color);
            p_Position.x += m_textSize[text_row_position].position.x * scaling.x;
        }
    }
}
