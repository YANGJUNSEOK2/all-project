/*
junseok.yang
assignment4
cs230
spring 2019
Vertices.cpp
*/
#include <CS230/graphics/Mesh.hpp>                       //include Mesh file
#include <CS230/graphics/VertexLayoutDescription.hpp>    //include LayoutDescription
#include <CS230/graphics/Vertices.hpp>                   //include vertices
#include <CS230/graphics/glCheck.hpp>                    //use glCheck()
#include <GL/glew.h>                                     //use glfunc()
#include <cassert>                                       //use assert()
#include <corecrt_memcpy_s.h>                            //use memcpy

namespace CS230
{
    Vertices::Vertices(const Mesh& mesh, const VertexLayoutDescription& vertex_layout) noexcept
    {
        InitializeWithMeshAndLayout(mesh, vertex_layout);
    }

    Vertices::~Vertices() noexcept
    {
        DeleteVerticesOnGPU();
    }

    Vertices::Vertices(Vertices&& other) noexcept
    {
        verticesHandle = other.verticesHandle;
        dataBufferHandle = other.dataBufferHandle;
        verticesCount = other.verticesCount;
        verticesListPattern = other.verticesListPattern;
        layout = other.layout;
        bufferVertexCapacity = other.bufferVertexCapacity;
        other.verticesHandle = 0;
        other.dataBufferHandle = 0;
        other.verticesCount = 0;
        other.bufferVertexCapacity = 0;
    }

    void Vertices::operator=(Vertices&& other) noexcept
    {
        if (this == &other)
            return;
        DeleteVerticesOnGPU();
        verticesHandle = other.verticesHandle;
        dataBufferHandle = other.dataBufferHandle;
        verticesCount = other.verticesCount;
        verticesListPattern = other.verticesListPattern;
        layout = other.layout;
        bufferVertexCapacity = other.bufferVertexCapacity;
        other.verticesHandle = 0;
        other.dataBufferHandle = 0;
        other.verticesCount = 0;
        other.bufferVertexCapacity = 0;
    }

    void Vertices::InitializeWithMeshAndLayout(const Mesh& mesh, const VertexLayoutDescription& vertex_layout) noexcept
    {
        switch (mesh.GetPointListPattern())
        {
        case PointListPattern::TriangleFan:
            verticesListPattern = GL_TRIANGLE_FAN;
            break;
        case PointListPattern::TriangleStrip:
            verticesListPattern = GL_TRIANGLE_STRIP;
            break;
        case PointListPattern::Triangles:
            verticesListPattern = GL_TRIANGLES;
            break;
        case PointListPattern::LineLoop:
            verticesListPattern = GL_LINE_LOOP;
            break;
        case PointListPattern::LineStrip:
            verticesListPattern = GL_LINE_STRIP;
            break;
        case PointListPattern::Lines:
            verticesListPattern = GL_LINES;
            break;
        default:
            break;
        }
        glCheck(glGenVertexArrays(1, &verticesHandle));
        glCheck(glGenBuffers(1, &dataBufferHandle));
        Select(*this);
        glCheck(glBufferData(GL_ARRAY_BUFFER,
            vertex_layout.GetVertexSize()*mesh.GetPointCount(),
            NULL, GL_STATIC_DRAW));

        verticesCount = static_cast<int>(mesh.GetPointCount());
        layout = vertex_layout;

        vertex_layout.SendVertexDescriptionToOpenGL();
        WriteMeshDataToVertexBuffer(mesh);
    }

    void Vertices::UpdateVerticesFromMesh(const Mesh& mesh)
    {
        if(mesh.GetPointCount()*layout.GetVertexSize()>=bufferVertexCapacity)
        {
            DeleteVerticesOnGPU();
            glCheck(glGenVertexArrays(1, &verticesHandle));
            glCheck(glGenBuffers(1, &dataBufferHandle));
            Select(*this);
            layout.SendVertexDescriptionToOpenGL();
            glCheck(glBufferData(GL_ARRAY_BUFFER, layout.GetVertexSize()*mesh.GetPointCount(), NULL, GL_DYNAMIC_DRAW));
            verticesCount = static_cast<int>(mesh.GetPointCount());
            bufferVertexCapacity = static_cast<int>(layout.GetVertexSize()*mesh.GetPointCount());
            WriteMeshDataToVertexBuffer(mesh);
        }
        else
        {
            WriteMeshDataToVertexBuffer(mesh);
        }
    }

    void Vertices::Select(const Vertices& vertices)
    {
        glCheck(glBindVertexArray(vertices.verticesHandle));
        glCheck(glBindBuffer(GL_ARRAY_BUFFER, vertices.dataBufferHandle));
    }

    void Vertices::SelectNothing()
    {
        glCheck(glBindVertexArray(0));
        glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void Vertices::DeleteVerticesOnGPU() noexcept
    {
        glCheck(glDeleteVertexArrays(1, &verticesHandle));
        glCheck(glDeleteBuffers(1, &dataBufferHandle));
    }

    void Vertices::WriteMeshDataToVertexBuffer(const Mesh& mesh) const noexcept
    {
        vector2 m_Position;
        Color4ub m_Color;
        vector2 m_Texture;

        std::vector<VertexLayoutDescription::FieldType> field_Types = layout.GetFieldTypes();
        std::vector<VertexLayoutDescription::FieldType>::iterator m_iterator;

        int offSet_Count = 0;
        void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        glCheck(ptr);

        for (int i = 0; i < verticesCount; i++)
        {
            for (m_iterator = field_Types.begin(); m_iterator < field_Types.end(); m_iterator++)
            {
                switch (*m_iterator)
                {
                case VertexLayoutDescription::Position2WithFloats:
                    m_Position = mesh.GetPoint(i);
                    memcpy(reinterpret_cast<char*>(ptr) + offSet_Count, &m_Position, sizeof(m_Position));
                    offSet_Count += sizeof(m_Position);
                    break;
                case VertexLayoutDescription::Color4WithUnsignedBytes:
                    m_Color = mesh.GetColor(i);
                    memcpy(reinterpret_cast<char*>(ptr) + offSet_Count, &m_Color, sizeof(m_Color));
                    offSet_Count += sizeof(m_Color);
                    break;
                case VertexLayoutDescription::TextureCoordinates2WithFloats:
                    m_Texture = mesh.GetTextureCoordinate(i);
                    memcpy(reinterpret_cast<char*>(ptr) + offSet_Count, &m_Texture, sizeof(m_Texture));
                    offSet_Count += sizeof(m_Texture);
                    break;
                default:
                    break;
                }
            }
        }
        glCheck(glUnmapBuffer(GL_ARRAY_BUFFER));
        SelectNothing();
    }
}
