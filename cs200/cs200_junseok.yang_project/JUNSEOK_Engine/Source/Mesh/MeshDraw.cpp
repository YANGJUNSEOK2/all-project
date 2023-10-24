/************************************************************************
*	File name : Mesh.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/

#include"MeshDraw.hpp"
#include "../Shader/glCheck/glCheck.hpp"
#include "../Texture/Texture.hpp"

namespace {
    const char* VERT =
        R"(#version 330 core
layout (location = 0) in vec2 vtPosition;
layout (location = 1) in vec4 vtColor;

out vec4 frColor;

uniform mat3 P;

void main(){
    vec3 p = P * vec3(vtPosition, 1.0);
    gl_Position = vec4(p.xy, 0.0, 1.0);
    frColor = vtColor;
})";

    const char* FRAG =
        R"(#version 330 core

in vec4 frColor;

out vec4 color;

void main(){
    color = frColor ;
})";
}

MeshDraw::MeshDraw()
{
    m_Texture.id = NULL;
    m_Texture.width = NULL;
    m_Texture.height = NULL;
}

MeshDraw::~MeshDraw() 
{
}

void MeshDraw::Init() {

    // Shader init
    m_Program.compileShadersFromSource(VERT, FRAG);
    m_Program.AddAttribute("vtPosition");
    m_Program.AddAttribute("vtColor");
    m_Program.LinkShaders();

    // Set up buffers
    glCheck(glGenVertexArrays(1, &m_Vao));
    glCheck(glGenBuffers(1, &m_Vbo));
    glCheck(glGenBuffers(1, &m_Ibo));

    glCheck(glBindVertexArray(m_Vao));
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_Vbo));
    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo));

    glCheck(glEnableVertexAttribArray(0));
    glCheck(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, position)));
    glCheck(glEnableVertexAttribArray(1));
    glCheck(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, color)));

    glCheck(glBindVertexArray(0));
}

void MeshDraw::End() {
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_Vbo));
    // Missing the buffer
    glCheck(glBufferData(GL_ARRAY_BUFFER, m_Vertex.size() * sizeof(MeshVertex), nullptr, GL_DYNAMIC_DRAW));
    // Upload the data
    glCheck(glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertex.size() * sizeof(MeshVertex), m_Vertex.data()));
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));

    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo));
    // Missing the buffer
    glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW));
    // Upload the data
    glCheck(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_Indices.size() * sizeof(GLuint), m_Indices.data()));
    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    m_NumElements = static_cast<int>(m_Indices.size());
    m_Indices.clear();
    m_Vertex.clear();
}

void MeshDraw::DrawLine(const Vector2<float>& p_Start, const Vector2<float>& p_Finish, const Color& color) {

    int i = static_cast<int>(m_Vertex.size());
    m_Vertex.resize(m_Vertex.size() + 2);

    m_Vertex[i].position = p_Start;
    m_Vertex[i].color = color;

    m_Vertex[i + 1].position = p_Finish;
    m_Vertex[i + 1].color = color;

    m_Indices.push_back(i);
    m_Indices.push_back(i + 1);
}

void MeshDraw::DrawBox(const Vector4<float>& p_PointANDSize, const Color& color, float angle) {

    int i = static_cast<int>(m_Vertex.size());
    m_Vertex.resize(m_Vertex.size() + 4);

    Vector2<float> halfSize(p_PointANDSize.z / 2.0f, p_PointANDSize.w / 2.0f);

    // Get points centered at origin
    Vector2<float> topLeft(-halfSize.x, halfSize.y);
    Vector2<float> bottomLeft(-halfSize.x, -halfSize.y);
    Vector2<float> bottomRight(halfSize.x, -halfSize.y);
    Vector2<float> topRight(halfSize.x, halfSize.y);

    //this point move?
    m_X = topLeft;
    m_Y = bottomLeft;
    m_Z = bottomRight;
    m_W = topRight;

    Vector2<float> positionOffset(p_PointANDSize.x, p_PointANDSize.y);

    //Rotate the points
    m_Vertex[i].position = rotate_By(angle, topLeft) + halfSize + positionOffset;
    m_Vertex[i + 1].position = rotate_By(angle, bottomLeft) + halfSize + positionOffset;
    m_Vertex[i + 2].position = rotate_By(angle, bottomRight) + halfSize + positionOffset;
    m_Vertex[i + 3].position = rotate_By(angle, topRight) + halfSize + positionOffset;


    for (int j = i; j < i + 4; j++) {
        m_Vertex[j].color = color;
    }

    m_Indices.reserve(m_Indices.size() + 8);

    m_Indices.push_back(i);
    m_Indices.push_back(i + 1);

    m_Indices.push_back(i + 1);
    m_Indices.push_back(i + 2);

    m_Indices.push_back(i + 2);
    m_Indices.push_back(i + 3);

    m_Indices.push_back(i + 3);
    m_Indices.push_back(i);
}

void MeshDraw::DrawTriangle(const Vector2<float>& p_PointANDSize,const Vector2<float> radius, const Color& color)
{
    static const int NUM_VERTS = 3;
    // Set up vertices
    int start = static_cast<int>(m_Vertex.size());
    m_Vertex.resize(m_Vertex.size() + NUM_VERTS);
    for (int i = 0; i < NUM_VERTS; i++)
    {
        float angle = ((float)i / NUM_VERTS) * PI * 2.0f;
        m_Vertex[start + i].position.x = sin(angle) * radius.x + p_PointANDSize.x;
        m_Vertex[start + i].position.y = cos(angle) * radius.y + p_PointANDSize.y;
        m_Vertex[start + i].color = color;
    }
    // Set up indices for indexed drawing
    m_Indices.reserve(m_Indices.size() + NUM_VERTS * 2);
    for (int i = 0; i < NUM_VERTS - 1; i++) {
        m_Indices.push_back(start + i);
        m_Indices.push_back(start + i + 1);
    }
    m_Indices.push_back(start + NUM_VERTS - 1);
    m_Indices.push_back(start);
}

void MeshDraw::DrawCircle(const Vector2<float>& center, const Vector2<float>& radius, const Color& color) {

    static const int NUM_VERTS = 500;
    // Set up vertices
    int start = static_cast<int>(m_Vertex.size());
    m_Vertex.resize(m_Vertex.size() + NUM_VERTS);
    for (int i = 0; i < NUM_VERTS; i++) {
        float angle = (static_cast<float> (i) / NUM_VERTS) * PI * 2.0f;
        m_Vertex[start + i].position.x = cos(angle) * radius.x + center.x;
        m_Vertex[start + i].position.y = sin(angle) * radius.y + center.y;
        m_Vertex[start + i].color = color;
    }

    // Set up indices for indexed drawing
    m_Indices.reserve(m_Indices.size() + NUM_VERTS * 2);
    for (int i = 0; i < NUM_VERTS - 1; i++) {
        m_Indices.push_back(start + i);
        m_Indices.push_back(start + i + 1);
    }
    m_Indices.push_back(start + NUM_VERTS - 1);
    m_Indices.push_back(start);
}

void MeshDraw::Render_Lines(const Matrix3<float>& p_Matrix, float lineWidth) {
    m_Program.UseEnable();
    GLint pUniform = m_Program.GetUniformLocation("P");
    glCheck(glUniformMatrix3fv(pUniform, 1, GL_FALSE, &p_Matrix.Elements[0][0]));
    glCheck(glLineWidth(lineWidth));
    glCheck(glBindVertexArray(m_Vao));
    glCheck(glDrawElements(GL_LINES, m_NumElements, GL_UNSIGNED_INT, 0));
    glCheck(glBindVertexArray(0));
    m_Program.UnUseDisable();
}

void MeshDraw::Render_TRIANGLE_FAN(const Matrix3<float>& p_Matrix)
{
    m_Program.UseEnable();
    GLint pUniform = m_Program.GetUniformLocation("P");
    glCheck(glUniformMatrix3fv(pUniform, 1, GL_FALSE, &p_Matrix.Elements[0][0]));
    glCheck(glBindVertexArray(m_Vao));
    glCheck(glDrawElements(GL_TRIANGLE_FAN, m_NumElements, GL_UNSIGNED_INT, 0));
    glCheck(glBindVertexArray(0));
    m_Program.UnUseDisable();
}

void MeshDraw::Dispose() {
    if (m_Vao) {
        glCheck(glDeleteVertexArrays(1, &m_Vao));
    }
    if (m_Vbo) {
        glCheck(glDeleteBuffers(1, &m_Vbo));
    }
    if (m_Ibo) {
        glCheck(glDeleteBuffers(1, &m_Ibo));
    }
    m_Program.Dispose();
}