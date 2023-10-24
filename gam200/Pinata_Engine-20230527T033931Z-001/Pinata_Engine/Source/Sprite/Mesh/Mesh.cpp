/************************************************************************
*	File name : Mesh.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester
*************************************************************************/
#include "Mesh.hpp"

namespace {
    const char* VERT_SRC =
        R"(#version 330

in vec2 vtPosition;
in vec4 vtColor;

out vec2 frPosition;
out vec4 frColor;

uniform mat3 P;

void main() {
    gl_Position.xy = (P * vec4(vtPosition, 0.0, 1.0)).xy;
   
    gl_Position.z = 0.0;
    
    gl_Position.w = 1.0;
    
    frPosition = vtPosition;
    
    frColor = vtColor;
})";

    const char* FRAG_SRC =
        R"(#version 330

in vec2 frPosition;
in vec4 frColor;

out vec4 color;

void main() {

    color = frColor;
})";
}

Mesh::Mesh() {
}

Mesh::~Mesh() {
    Dispose();
}

void Mesh::Init() {

    // Shader init
    m_Program.compileShadersFromSource(VERT_SRC, FRAG_SRC);
    m_Program.AddAttribute("vtPosition");
    m_Program.AddAttribute("vtColor");
    m_Program.LinkShaders();

    // Set up buffers
    glGenVertexArrays(1, &m_Vao);
    glGenBuffers(1, &m_Vbo);
    glGenBuffers(1, &m_Ibo);

    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, color));

    glBindVertexArray(0);


}

void Mesh::End() {
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    // Orphan the buffer
    glBufferData(GL_ARRAY_BUFFER, m_Vertex.size() * sizeof(MeshVertex), nullptr, GL_DYNAMIC_DRAW);
    // Upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertex.size() * sizeof(MeshVertex), m_Vertex.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
    // Orphan the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
    // Upload the data
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_Indices.size() * sizeof(GLuint), m_Indices.data());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_NumElements = m_Indices.size();
    m_Indices.clear();
    m_Vertex.clear();
}

void Mesh::DrawLine(const Vector2<float>& p_Start, const Vector2<float>& p_Finish, const Color& color) {
    int i = m_Vertex.size();
    m_Vertex.resize(m_Vertex.size() + 2);

    m_Vertex[i].position = p_Start;
    m_Vertex[i].color = color;
    m_Vertex[i + 1].position = p_Finish;
    m_Vertex[i + 1].color = color;

    m_Indices.push_back(i);
    m_Indices.push_back(i + 1);
}

void Mesh::DrawBox(const Vector4<float>& p_PointANDSize, const Color& color, float angle) {

    int i = m_Vertex.size();
    m_Vertex.resize(m_Vertex.size() + 4);

    Vector2<float> halfSize(p_PointANDSize.z / 2.0f, p_PointANDSize.w / 2.0f);

    // Get points centered at origin
    Vector2<float> topLeft(-halfSize.x, halfSize.y);
    Vector2<float> bottomLeft(-halfSize.x, -halfSize.y);
    Vector2<float> bottomRight(halfSize.x, -halfSize.y);
    Vector2<float> topRight(halfSize.x, halfSize.y);

    Vector2<float> positionOffset(p_PointANDSize.x, p_PointANDSize.y);

    // Rotate the points
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

void Mesh::DrawCircle(const Vector2<float>& center, const Color& color, float radius) {
    static const int NUM_VERTS = 6;
    // Set up vertices
    int start = m_Vertex.size();
    m_Vertex.resize(m_Vertex.size() + NUM_VERTS);
    for (int i = 0; i < NUM_VERTS; i++) {
        float angle = ((float)i / NUM_VERTS) * PI * 2.0f;
        m_Vertex[start + i].position.x = cos(angle) * radius + center.x;
        m_Vertex[start + i].position.y = sin(angle) * radius + center.y;
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

void Mesh::Render(const Matrix3<float>& p_Matrix, float lineWidth) {
    m_Program.UseEnable();

    GLint pUniform = m_Program.GetUniformLocation("P");
    glUniformMatrix3fv(pUniform, 1, GL_FALSE, &p_Matrix.Elements[0][0]);
    glLineWidth(lineWidth);
    glBindVertexArray(m_Vao);
    glDrawElements(GL_LINES, m_NumElements, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    m_Program.UnUseDisable();
}

void Mesh::Dispose() {
    if (m_Vao) {
        glDeleteVertexArrays(1, &m_Vao);
    }
    if (m_Vbo) {
        glDeleteBuffers(1, &m_Vbo);
    }
    if (m_Ibo) {
        glDeleteBuffers(1, &m_Ibo);
    }
    m_Program.Dispose();
}
