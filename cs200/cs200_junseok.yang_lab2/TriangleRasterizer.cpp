/*
 * junseok yang
 * Lab2 - TriangleRasterizer
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

const int WIDTH = 256;
const int HEIGHT = 256;
const Color BEAUTY_BUSH_PINK{ 0xf0bcd4FF };
Image gImage{ WIDTH, HEIGHT, BEAUTY_BUSH_PINK };

struct Vector
{
    Vector(int x = 0, int y = 0) : x(x), y(y) {}

    static int dot(const Vector& vec1, const Vector& vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }

    int x;
    int y;
};

struct Point
{
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    Vector operator-(const Point& rhs) const
    {
        return Vector(x - rhs.x, y - rhs.y);
    }

    int x;
    int y;
};

int ROUND(double f) { return static_cast<int>(floor(f + 0.5)); }

void SETPIXEL(int column, int row, Color intensity) { gImage.SetPixel(column, row, intensity); }

void DrawTriangle(const Point& p1, const Point& p2, const Point& p3, Color intensity);

int main(void)
{
    Point p1(128, 10);
    Point p2(246, 246);
    Point p3(10, 246);
    DrawTriangle(p1, p2, p3, DISCO_PURPLE);

    gImage.SaveToPNG("results.png");
    system("start results.png");
    return 0;
}

int Determinant(const Point& p1, const Point& p2, const Point& p)
{
    return(((p2.x - p1.x) * (p.y - p1.y)) - ((p2.y - p1.y) * (p.x - p1.x)));
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

void DrawTriangle(const Point& p1, const Point& p2,
    const Point& p3, Color intensity)
{

    int maxX = 0, maxY = 0, minX = 0, minY = 0;

    maxX = max(p1.x, p2.x, p3.x);
    maxY = max(p1.y, p2.y, p3.y);

    minX = min(p1.x, p2.x, p3.x);
    minY = min(p1.y, p2.y, p3.y);

    Point p = { minX,minY };

    int dx1 = (p2.x - p1.x);
    int dx2 = (p3.x - p2.x);
    int dx3 = (p1.x - p3.x);

    int dy1 = (p2.y - p1.y);
    int dy2 = (p3.y - p2.y);
    int dy3 = (p1.y - p3.y);

    int d_p2p1 = Determinant(p2, p1, p);
    int d_p3p1 = Determinant(p3, p1, p);
    int d_p1p3 = Determinant(p1, p3, p);

    for (p.y = minY; p.y < maxY; p.y++)
    {
        int d_p2p1_Tmp = d_p2p1;
        int d_p3p1_Tmp = d_p3p1;
        int d_p1p3_Tmp = d_p1p3;

        for (p.x = minX; p.x < maxX; p.x++)
        {
            if (d_p2p1_Tmp >= 0 && d_p3p1_Tmp <= 0 && d_p1p3_Tmp >= 0)
            {
                SETPIXEL(p.x, p.y, intensity);
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