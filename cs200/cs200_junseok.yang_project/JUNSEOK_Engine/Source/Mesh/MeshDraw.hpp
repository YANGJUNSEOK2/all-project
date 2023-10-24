/************************************************************************
*	File name : Mesh.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include "../Vertex/Vertex.hpp"
#include "../MathLibrary/MathLibrary.hpp"
#include <vector>
#include "../Shader/Shader.hpp"
#include "../Camera/CameraView.h"
#include "../Camera/CameraSet.h"
#include "../Camera/Transtorm.h"
#include "../Texture/GLTexture.hpp"


class MeshDraw {
public:
    MeshDraw();
    ~MeshDraw();

    void Init();
    void End();
    void DrawLine(const Vector2<float>& p_Start, const Vector2<float>& p_Finish, const Color& p_Color);
    void DrawBox(const Vector4<float>& p_PointANDSize, const  Color& color, float p_Angle);
    void DrawTriangle(const Vector2<float>& p_PointANDSize, const Vector2<float> radius, const Color& color);
    void DrawCircle(const Vector2<float>& center, const Vector2<float>& radius, const Color& color);
    void Render_Lines(const Matrix3<float>& p_Matrix, float lineWidth);
    void Render_TRIANGLE_FAN(const Matrix3<float>& p_Matrix);
    void Dispose();

    Vector2<float> X() { return m_X; }
    void ChangeX(Vector2<float> x) { m_X = x; }
    Vector2<float> Y() { return m_Y; }
    void ChangeY(Vector2<float> y) { m_Y = y; }

    Vector2<float> Z() { return m_Z; }
    void ChangeZ(Vector2<float> z) { m_Z = z; }
    Vector2<float> W() { return m_W; }
    void ChangeW(Vector2<float> w) { m_W = w; }



protected:

private:
    Vector2<float> m_X;
    Vector2<float> m_Y;
    Vector2<float> m_Z;
    Vector2<float> m_W;

    Shader m_Program;
    struct MeshVertex 
    {
        Vector2<float> position;
        Color color;
        Vector2<float> uv;
    };
    GLTexture m_Texture;
    std::vector<MeshVertex> m_Vertex;
    std::vector<GLuint> m_Indices;
    //Vertex buffer object, Vertex array object, Index buffer object initialize.
    GLuint m_Vbo = 0, m_Vao = 0, m_Ibo = 0;
    int m_NumElements = 0;

    Transform m_transform;
};
