/*
 * junseok yang
 * Lab4 - TextureMapping
 * CS200
 * Fall 2019
 */
#include <CS200/Image.hpp>
#include <cstdlib>
#include <algorithm>
#include "CS200/RenderOption.hpp"

using namespace CS200;

const Color BLACK{ 0x000000FF };
const Color WHITE{ 0xFFFFFFFF };
const Color JAGUAR_BLACK{ 0x1F0322FF };
const Color DISCO_PURPLE{ 0x8a1c7cFF };
const Color CABARET_RED{ 0xda4167FF };
const Color BATTLESHIP_GRAY{ 0x899d78FF };
const Color BEAUTY_BUSH_PINK{ 0xf0bcd4FF };

const Color RED(255, 0, 0);
const Color GREEN(0, 255, 0);
const Color BLUE(0, 0, 255);

const int WIDTH = 512;
const int HEIGHT = 512;

Image gImage{ WIDTH, HEIGHT, BEAUTY_BUSH_PINK };

struct Vector3D
{
    Vector3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    static float dot(const Vector3D& vec1, const Vector3D& vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
    }

    static Vector3D cross(const Vector3D& vec1, const Vector3D& vec2)
    {
        return Vector3D(vec1.y * vec2.z - vec1.z * vec2.y,
            vec1.z * vec2.x - vec1.x * vec2.z,
            vec1.x * vec2.y - vec1.y * vec2.x);
    }

    float x;
    float y;
    float z;
};

struct Vertex2D
{
    Vertex2D(float x, float y, const Color& color, float u, float v)
        : x(x), y(y), color(color), u(u), v(v) {}

    Vector3D operator-(const Vertex2D& vertex) const
    {
        return Vector3D(x - vertex.x, y - vertex.y, 0);
    }

    float x = 0;
    float y = 0;
    Color color;
    float u = 0;
    float v = 0;
};

struct Point3D
{
    Point3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    Point3D(const Vertex2D& v) : x(v.x), y(v.y), z(0) {}

    Vector3D operator-(const Point3D& rhs) const
    {
        return Vector3D(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    float x;
    float y;
    float z;
};

int ROUND(float f) { return static_cast<int>(floor(f + 0.5f)); }

void SETPIXEL(int column, int row, Color intensity) { gImage.SetPixel(column, row, intensity); }

void DrawTriangle(const Vertex2D& v1, const Vertex2D& v2, const Vertex2D& v3, const RenderOption & option);

int main(void)
{
    //Vertices
    Vertex2D v1(0, 0, RED, 0, 0); // top left
    Vertex2D v2(WIDTH - 1, HEIGHT - 1, BLUE, 3, 3); // bottom right
    Vertex2D v3(WIDTH - 1, 0, GREEN, 3, 0); // top right
    Vertex2D v4(0, HEIGHT - 1, BLACK, 0, 3); // bottom left

    //Render option
    Texture texture("awesomeface.png");
    RenderOption option;
    option.texture = &texture;
    option.texture_func = TextureFunction::REPEAT;
    option.cc_mode = ColorCombineMode::DECAL;
    DrawTriangle(v1, v2, v3, option);
    DrawTriangle(v1, v4, v2, option);
    gImage.SaveToPNG("repeat_decal.png");

    option.texture_func = TextureFunction::REPEAT;
    option.cc_mode = ColorCombineMode::MODULATE;
    DrawTriangle(v1, v2, v3, option);
    DrawTriangle(v1, v4, v2, option);
    gImage.SaveToPNG("repeat_modulate.png");

    option.texture_func = TextureFunction::REPEAT;
    option.cc_mode = ColorCombineMode::REPLACE;
    DrawTriangle(v1, v2, v3, option);
    DrawTriangle(v1, v4, v2, option);
    gImage.SaveToPNG("repeat_replace.png");

    option.texture_func = TextureFunction::MIRROR;
    option.cc_mode = ColorCombineMode::DECAL;
    DrawTriangle(v1, v2, v3, option);
    DrawTriangle(v1, v4, v2, option);
    gImage.SaveToPNG("mirror_decal.png");

    option.texture_func = TextureFunction::MIRROR;
    option.cc_mode = ColorCombineMode::MODULATE;
    DrawTriangle(v1, v2, v3, option);
    DrawTriangle(v1, v4, v2, option);
    gImage.SaveToPNG("mirror_modulate.png");

    option.texture_func = TextureFunction::MIRROR;
    option.cc_mode = ColorCombineMode::REPLACE;
    DrawTriangle(v1, v2, v3, option);
    DrawTriangle(v1, v4, v2, option);
    gImage.SaveToPNG("mirror_replace.png");

    option.texture_func = TextureFunction::CLAMP;
    option.cc_mode = ColorCombineMode::DECAL;
    DrawTriangle(v1, v2, v3, option);
    DrawTriangle(v1, v4, v2, option);
    gImage.SaveToPNG("clamp_decal.png");

    option.texture_func = TextureFunction::CLAMP;
    option.cc_mode = ColorCombineMode::MODULATE;
    DrawTriangle(v1, v2, v3, option);
    DrawTriangle(v1, v4, v2, option);
    gImage.SaveToPNG("clamp_modulate.png");

    option.texture_func = TextureFunction::CLAMP;
    option.cc_mode = ColorCombineMode::REPLACE;
    DrawTriangle(v1, v2, v3, option);
    DrawTriangle(v1, v4, v2, option);
    gImage.SaveToPNG("clamp_replace.png");

    return 0;
}

float min(float p1, float p2, float p3)
{
    float smallest = 0.0f;
    smallest = p1 > p2 ? (p2 > p3 ? p3 : p2) : (p1 > p3 ? p3 : p1);
    return smallest;
}

float max(float p1, float p2, float p3)
{
    float largest = 0.0f;
    largest = p1 < p2 ? (p2 < p3 ? p3 : p2) : (p1 < p3 ? p3 : p1);
    return largest;
}

float min(float p1, float p2)
{
    float smallest = 0.0f;
    smallest = ((p1) < (p2) ? (p1) : (p2));
    return smallest;
}

float max(float p1, float p2)
{
    float largest = 0.0f;
    largest = ((p1) > (p2) ? (p1) : (p2));
    return largest;
}

float Determinant(const Vertex2D& p1, const Vertex2D& p2, const Point3D& p)
{
    return (((p2.x - p1.x) * (p.y - p1.y)) - ((p2.y - p1.y) * (p.x - p1.x)));
}

Vector3D Texture_Func(const RenderOption& option, float Texture_U, float Texture_V)
{
    float Clamp_U = 0.0f, Clamp_V = 0.0f, Texel_U = 0.0f, Texel_V = 0.0f;
    float Mirror_Even_U = 0.0f, Mirror_Odd_U = 0.0f, 
    Mirror_Even_V = 0.0f, Mirror_Odd_V = 0.0f, Wrap_U = 0.0f, Wrap_V = 0.0f;
    switch (option.texture_func)
    {
    case TextureFunction::CLAMP: {
        Clamp_U = fmax(fmin(Texture_U, 1.0f), 0.0f);
        Clamp_V = fmax(fmin(Texture_V, 1.0f), 0.0f);
        Texel_U = (option.texture->GetTextureWidth() * Clamp_U) - 0.5f;
        Texel_V = (option.texture->GetTextureHeight() * Clamp_V) - 0.5f;
        break;
    }
    case TextureFunction::MIRROR: {
        if (static_cast<int>(Texture_U) % 2 == 0)
        {
            Mirror_Even_U = Texture_U - static_cast<int>(Texture_U);
            Texel_U = (option.texture->GetTextureWidth()* Mirror_Even_U) - 0.5f;
        }
        else if (static_cast<int>(Texture_U) % 2 == 1)
        {
            Mirror_Odd_U = 1.0f - (Texture_U - static_cast<int>(Texture_U));
            Texel_U = (option.texture->GetTextureWidth()* Mirror_Odd_U) - 0.5f;
        }
        if (static_cast<int>(Texture_V) % 2 == 0)
        {
            Mirror_Even_V = Texture_V - static_cast<int>(Texture_V);
            Texel_V = (option.texture->GetTextureWidth()* Mirror_Even_V) - 0.5f;
        }
        else if (static_cast<int>(Texture_V) % 2 == 1)
        {
            Mirror_Odd_V = 1.0f - (Texture_V - static_cast<int>(Texture_V));
            Texel_V = (option.texture->GetTextureWidth()* Mirror_Odd_V) - 0.5f;
        }
        break;
    }
    case TextureFunction::REPEAT: {
        Wrap_U = Texture_U - static_cast<int>(Texture_U);
        Wrap_V = Texture_V - static_cast<int>(Texture_V);

        Texel_U = (option.texture->GetTextureWidth()* Wrap_U) - 0.5f;
        Texel_V = (option.texture->GetTextureHeight()* Wrap_V) - 0.5f;
        break;
    }
    }
    return Vector3D{ Texel_U,Texel_V,0.0f };
}

Color Cc_Mode_TextureColor(const RenderOption& option, Color::ColorChannel& RedColor, Color::ColorChannel& GreenColor, Color::ColorChannel& BlueColor , Vector3D& Texel)
{
    Color::ColorChannel TextureRed = 0;
    Color::ColorChannel TextureBlue = 0;
    Color::ColorChannel TextureGreen = 0;
	Color::ColorChannel TextureAlpha = 255;

    int Texel_U = static_cast<int>(Texel.x);
    int Texel_V = static_cast<int>(Texel.y);

    switch (option.cc_mode)
    {
    case ColorCombineMode::DECAL:
	{
        TextureRed = RedColor + static_cast<unsigned char>(option.texture->GetTextureColor(Texel_U,Texel_V).Alpha * (option.texture->GetTextureColor(Texel_U, Texel_V).Red - RedColor) / 255.0f);
        TextureBlue = BlueColor + static_cast<unsigned char>(option.texture->GetTextureColor(Texel_U, Texel_V).Alpha * (option.texture->GetTextureColor(Texel_U, Texel_V).Blue - BlueColor) / 255.0f);
        TextureGreen = GreenColor + static_cast<unsigned char>(option.texture->GetTextureColor(Texel_U, Texel_V).Alpha * (option.texture->GetTextureColor(Texel_U, Texel_V).Green - GreenColor) / 255.0f);
        break;
    }
    case ColorCombineMode::MODULATE:
    {
        TextureRed = static_cast<unsigned char>((option.texture->GetTextureColor(Texel_U, Texel_V).Red / 255.0f) * RedColor);
        TextureBlue = static_cast<unsigned char>((option.texture->GetTextureColor(Texel_U, Texel_V).Blue / 255.0f) * BlueColor);
        TextureGreen = static_cast<unsigned char>((option.texture->GetTextureColor(Texel_U, Texel_V).Green / 255.0f) * GreenColor);
        break;
    }
    case ColorCombineMode::REPLACE:
    {
        TextureRed = option.texture->GetTextureColor(Texel_U, Texel_V).Red;
        TextureBlue = option.texture->GetTextureColor(Texel_U, Texel_V).Blue;
        TextureGreen = option.texture->GetTextureColor(Texel_U, Texel_V).Green;
		TextureAlpha = option.texture->GetTextureColor(Texel_U, Texel_V).Alpha;
        break;
    }
    }
	return Color{ TextureRed,TextureGreen,TextureBlue,TextureAlpha };
}

void DrawTriangle(const Vertex2D& v1, const Vertex2D& v2, const Vertex2D& v3, const RenderOption& option)
{
    float maxX = 0.0f, maxY = 0.0f, minX = 0.0f, minY = 0.0f;

    maxX = max(v1.x, v2.x, v3.x);
    maxY = max(v1.y, v2.y, v3.y);

    minX = min(v1.x, v2.x, v3.x);
    minY = min(v1.y, v2.y, v3.y);

    float dx1 = (v2.x - v1.x);
    float dx2 = (v3.x - v2.x);
    float dx3 = (v1.x - v3.x);

    float dy1 = (v1.y - v2.y);
    float dy2 = (v2.y - v3.y);
    float dy3 = (v3.y - v1.y);

    Vector3D Red = Vector3D::cross({ static_cast<float>(v1.x - v3.x), static_cast<float>(v1.y - v3.y), static_cast<float>(v1.color.Red - v3.color.Red) },
        { static_cast<float>(v2.x - v3.x), static_cast<float>(v2.y - v3.y),static_cast<float>(v2.color.Red - v3.color.Red) });
    Vector3D Green = Vector3D::cross({ static_cast<float>(v1.x - v3.x), static_cast<float>(v1.y - v3.y),static_cast<float>(v1.color.Green - v3.color.Green) },
        { static_cast<float>(v2.x - v3.x), static_cast<float>(v2.y - v3.y),static_cast<float>(v2.color.Green - v3.color.Green) });
    Vector3D Blue = Vector3D::cross({ static_cast<float>(v1.x - v3.x), static_cast<float>(v1.y - v3.y), static_cast<float>(v1.color.Blue - v3.color.Blue) },
        { static_cast<float>(v2.x - v3.x), static_cast<float>(v2.y - v3.y), static_cast<float>(v2.color.Blue - v3.color.Blue) });

    Vector3D U = Vector3D::cross({ static_cast<float>(v1.x - v3.x), static_cast<float>(v1.y - v3.y), static_cast<float>(v1.u - v3.u) },
        { static_cast<float>(v2.x - v3.x), static_cast<float>(v2.y - v3.y), static_cast<float>(v2.u - v3.u) });
    Vector3D V = Vector3D::cross({ static_cast<float>(v1.x - v3.x), static_cast<float>(v1.y - v3.y), static_cast<float>(v1.v - v3.v) },
        { static_cast<float>(v2.x - v3.x), static_cast<float>(v2.y - v3.y), static_cast<float>(v2.v - v3.v) });

    Vector3D v3_Red = { static_cast<float>(v3.x),static_cast<float>(v3.y),static_cast<float>(v3.color.Red) };
    Vector3D v3_Green = { static_cast<float>(v3.x),static_cast<float>(v3.y),static_cast<float>(v3.color.Green) };
    Vector3D v3_Blue = { static_cast<float>(v3.x),static_cast<float>(v3.y),static_cast<float>(v3.color.Blue) };

    Vector3D v3_U = { static_cast<float>(v3.x),static_cast<float>(v3.y),static_cast<float>(v3.u) };
    Vector3D v3_V = { static_cast<float>(v3.x),static_cast<float>(v3.y),static_cast<float>(v3.v) };

    float RedD = Vector3D::dot(Red, v3_Red);
    float GreenD = Vector3D::dot(Green, v3_Green);
    float BlueD = Vector3D::dot(Blue, v3_Blue);

    float U_D = Vector3D::dot(U, v3_U);
    float V_D = Vector3D::dot(V, v3_V);

    Point3D p = { minX,minY };

    float d_p2p1 = Determinant(v1, v2, p);
    float d_p3p1 = Determinant(v2, v3, p);
    float d_p1p3 = Determinant(v3, v1, p);

    for (p.y = minY; p.y <= maxY; p.y++)
    {

        float d_p2p1_Tmp = d_p2p1;
        float d_p3p1_Tmp = d_p3p1;
        float d_p1p3_Tmp = d_p1p3;

        for (p.x = minX; p.x <= maxX; p.x++)
        {
            Color::ColorChannel RedColor = static_cast<unsigned char>((Red.x * p.x + Red.y * p.y - RedD) / -Red.z);
            Color::ColorChannel GreenColor = static_cast<unsigned char>((Green.x * p.x + Green.y * p.y - GreenD) / -Green.z);
            Color::ColorChannel BlueColor = static_cast<unsigned char>((Blue.x * p.x + Blue.y * p.y - BlueD) / -Blue.z);

            float Texture_U = ((U.x * p.x + U.y * p.y - U_D) / -U.z);
            float Texture_V = ((V.x * p.x + V.y * p.y - V_D) / -V.z);
            float Texel_U = 0.0f;
            float Texel_V = 0.0f;
            Vector3D Texel{ Texel_U,Texel_V,0.0f };
            Texel = Texture_Func(option, Texture_U, Texture_V);

            Color Color = Cc_Mode_TextureColor(option, RedColor, GreenColor, BlueColor, Texel);

            if (d_p2p1_Tmp <= 0 && d_p3p1_Tmp <= 0 && d_p1p3_Tmp <= 0)
            {
                SETPIXEL(ROUND(p.x), ROUND(p.y), Color);
            }

            d_p2p1_Tmp += dy1;
            d_p3p1_Tmp += dy2;
            d_p1p3_Tmp += dy3;
        }
        d_p2p1 += dx1;
        d_p3p1 += dx2;
        d_p1p3 += dx3;
    }
}