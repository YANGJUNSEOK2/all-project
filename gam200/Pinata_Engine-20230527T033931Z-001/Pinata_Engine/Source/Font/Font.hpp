#pragma once
#include <SDL_ttf.h>
#include "../MathLibrary/MathLibrary.hpp"
#include <map>
#include <vector>
#include "../Vertex/Vertex.hpp"

struct GLTexture;
class SpriteBatch;

struct TextSize
{
public:
    char text;
    Vector4<float> uv;
    Vector2<float> position;
};

#define FIRST ((char)32)
#define LAST ((char)126)

enum class TextPosition 
{
    LEFT, MIDDLE, RIGHT
};

class Font {
public:
    Font() {};
    Font(const char* font, int size, char start, char end);
    Font(const char* font, int size) :
        Font(font, size, FIRST, LAST) {}

    void init(const char* font, int size);
    void init(const char* font, int size, char start, char end);

    /// dispose font information
    void destroy();

    int getFontHeight() const 
    {
        return m_fontH;
    }

    Vector2<float> text_dimension_check(const char* charSize);

    /// Drawing font
    void Draw(SpriteBatch& sprite, const char* str, Vector2<float> position, Vector2<float> scaling, float depth, Color font_Color, TextPosition textPositon_choice = TextPosition::LEFT);
private:
    static std::vector<int>* createRows(Vector4<int>* rect, int rectLength, int row, int matarial, int& width);

    int m_Start, m_Length;
    TextSize *m_textSize;
    int m_fontH;

    unsigned int m_textID;
};