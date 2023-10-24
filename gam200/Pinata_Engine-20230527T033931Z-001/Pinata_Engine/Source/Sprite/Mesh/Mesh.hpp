/************************************************************************
*	File name : Mesh.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester
*************************************************************************/
#pragma once
#include "../../Shader/Shader.hpp"
#include "../../Vertex/Vertex.hpp"
#include "../../MathLibrary/MathLibrary.hpp"
#include <vector>


class Mesh {
public:
    Mesh();
    ~Mesh();

    void Init();
    void End();
    void DrawLine(const Vector2<float>& p_Start, const Vector2<float>& p_Finish, const Color& p_Color);
    void DrawBox(const Vector4<float>& p_PointANDSize, const  Color& color, float p_Angle);
    void DrawCircle(const Vector2<float>& center, const  Color& color, float radius);
    void Render(const Matrix3<float>& projectionMatrix, float lineWidth);
    void Dispose();

private:
    struct MeshVertex {
        Vector2<float> position;
        Color color;
    };
    Shader m_Program;
    std::vector<MeshVertex> m_Vertex;
    std::vector<GLuint> m_Indices;
    GLuint m_Vbo = 0, m_Vao = 0, m_Ibo = 0;
    int m_NumElements = 0;
};
