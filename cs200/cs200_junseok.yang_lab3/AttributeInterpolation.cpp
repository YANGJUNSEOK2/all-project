/*
 * junseok yang
 * Lab3 - AttributeInterpolation
 * CS200
 * Fall 2019
 */
#include <CS200/Image.hpp>
#include <cstdlib>

using namespace CS200;

const Color BLACK{ 0x000000FF };
const Color WHITE{ 0xFFFFFFFF };
const Color JAGUAR_BLACK{ 0x1F0322FF };
const Color DISCO_PURPLE{ 0x8a1c7cFF };
const Color CABARET_RED{ 0xda4167FF };
const Color BATTLESHIP_GRAY{ 0x899d78FF };

const Color RED(255, 0, 0);
const Color GREEN(0, 255, 0);
const Color BLUE(0, 0, 255);

const int WIDTH = 256;
const int HEIGHT = 256;
const Color BEAUTY_BUSH_PINK{ 0xf0bcd4FF };
Image gImage{ WIDTH, HEIGHT, BEAUTY_BUSH_PINK };

struct Vector3D
{
    Vector3D(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}

    static int dot(const Vector3D& vec1, const Vector3D& vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
    }

    static Vector3D cross(const Vector3D& vec1, const Vector3D& vec2)
    {
        return Vector3D(vec1.y * vec2.z - vec1.z * vec2.y,
            vec1.z * vec2.x - vec1.x * vec2.z,
            vec1.x * vec2.y - vec1.y * vec2.x);
    }

    int x;
    int y;
    int z;
};

struct Vertex2D
{
    Vertex2D(int x, int y, const Color& color)
        : x(x), y(y), color(color) {}

    Vector3D operator-(const Vertex2D& v) const
    {
        return Vector3D(x - v.x, y - v.y, 0);
    }

    int x = 0;
    int y = 0;
    Color color;
};

struct Point3D
{
    Point3D(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
    Point3D(const Vertex2D& v) : x(v.x), y(v.y), z(0) {}

    Vector3D operator-(const Point3D& rhs) const
    {
        return Vector3D(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    int x;
    int y;
    int z;
};

int ROUND(double f) { return static_cast<int>(floor(f + 0.5f)); }

void SETPIXEL(int column, int row, Color intensity) { gImage.SetPixel(column, row, intensity); }

void DrawTriangle(const Vertex2D& v1, const Vertex2D& v2, const Vertex2D& v3);

int main(void)
{
    Vertex2D v1(128, 10, RED);
    Vertex2D v2(246, 246, GREEN);
    Vertex2D v3(10, 246, BLUE);
    DrawTriangle(v1, v2, v3);

    gImage.SaveToPNG("results.png");
    system("start results.png");
    return 0;
}

int min(int p1, int p2, int p3)
{
    int smallest = 0;
    smallest = p1 > p2 ? (p2 > p3 ? p3 : p2) : (p1 > p3 ? p3 : p1);
    return smallest;
}

int max(int p1, int p2, int p3)
{
    int largest = 0;
    largest = p1 < p2 ? (p2 < p3 ? p3 : p2) : (p1 < p3 ? p3 : p1);
    return largest;
}

int Determinant(const Vertex2D& p1, const Vertex2D& p2, const Point3D& p)
{
    return(((p2.x - p1.x) * (p.y - p1.y)) - ((p2.y - p1.y) * (p.x - p1.x)));
}

void DrawTriangle(const Vertex2D& v1, const Vertex2D& v2, const Vertex2D& v3)
{
    int maxX = 0, maxY = 0, minX = 0, minY = 0;

    maxX = max(v1.x, v2.x, v3.x);
    maxY = max(v1.y, v2.y, v3.y);

    minX = min(v1.x, v2.x, v3.x);
    minY = min(v1.y, v2.y, v3.y);

    Point3D p = { minX,minY,0 };

    int dx1 = (v2.x - v1.x);
    int dx2 = (v3.x - v2.x);
    int dx3 = (v1.x - v3.x);

    int dy1 = (v2.y - v1.y);
    int dy2 = (v3.y - v2.y);
    int dy3 = (v1.y - v3.y);

    int d_p2p1 = Determinant(v2, v1, p);
    int d_p3p1 = Determinant(v3, v1, p);
    int d_p1p3 = Determinant(v1, v3, p);

    Vector3D Red = Vector3D::cross({ v1.x - v3.x, v1.y - v3.y,v1.color.Red - v3.color.Red }, { v2.x - v3.x, v2.y - v3.y,v2.color.Red - v3.color.Red });
    Vector3D Green = Vector3D::cross({ v1.x - v3.x, v1.y - v3.y,v1.color.Green - v3.color.Green }, { v2.x - v3.x, v2.y - v3.y,v2.color.Green - v3.color.Green });
    Vector3D Blue = Vector3D::cross({ v1.x - v3.x, v1.y - v3.y, v1.color.Blue - v3.color.Blue }, { v2.x - v3.x, v2.y - v3.y, v2.color.Blue - v3.color.Blue });

    Vector3D v3_Red = { v3.x,v3.y,v3.color.Red };
    Vector3D v3_Green = { v3.x,v3.y,v3.color.Green };
    Vector3D v3_Blue = { v3.x,v3.y,v3.color.Blue };

    int RedD = Vector3D::dot(Red, v3_Red);
    int GreenD = Vector3D::dot(Green, v3_Green);
    int BlueD = Vector3D::dot(Blue, v3_Blue);

    for (p.y = minY; p.y < maxY; p.y++)
    {
        int d_p2p1_Tmp = d_p2p1;
        int d_p3p1_Tmp = d_p3p1;
        int d_p1p3_Tmp = d_p1p3;

        for (p.x = minX; p.x < maxX; p.x++)
        {
            Color::ColorChannel RedColor = static_cast<unsigned char>((Red.x * p.x + Red.y * p.y - RedD) / -Red.z);
            Color::ColorChannel GreenColor = static_cast<unsigned char>((Green.x * p.x + Green.y * p.y - GreenD) / -Green.z);
            Color::ColorChannel BlueColor = static_cast<unsigned char>((Blue.x * p.x + Blue.y * p.y - BlueD) / -Blue.z);

            Color Color = { RedColor, GreenColor, BlueColor };

            if (d_p2p1_Tmp >= 0 && d_p3p1_Tmp <= 0 && d_p1p3_Tmp >= 0)
            {
                SETPIXEL(p.x, p.y, Color);
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

