/*
junseok.yang
assignment4
cs230
spring 2019
VertexLayoutDescription.cpp
*/
#include <CS230/graphics/Mesh.hpp>                       //include mesh
#include <CS230/graphics/VertexLayoutDescription.hpp>    //include layoutDescription
#include <CS230/graphics/glCheck.hpp>                    //use glCheck()
#include <GL/glew.h>                                     //use glfunc()
#include <cassert>                                       //use assert
#include <cstdint>                                       //uintptr_t

namespace CS230
{
    VertexLayoutDescription::VertexLayoutDescription(std::initializer_list<FieldType> fields) noexcept
    {
        std::initializer_list<FieldType>::iterator m_Iterator;
        for (m_Iterator = fields.begin(); m_Iterator != fields.end(); m_Iterator++)
        {
            AddField(*m_Iterator);
        }
    }

    void VertexLayoutDescription::AddField(FieldType field_type) noexcept
    {
        field_description m_Field_Description;

        if(field_type==FieldType::Position2WithFloats)
        {
            m_Field_Description.elementType = GL_FLOAT;
            m_Field_Description.elementCount = 2;
            m_Field_Description.sizeInBytes = sizeof(float)*m_Field_Description.elementCount;
        }
        else if(field_type == FieldType::TextureCoordinates2WithFloats)
        {
            m_Field_Description.elementType = GL_FLOAT;
            m_Field_Description.elementCount = 2;
            m_Field_Description.sizeInBytes = sizeof(float)*m_Field_Description.elementCount;
        }
        else if(field_type == FieldType::Color4WithUnsignedBytes)
        {
            m_Field_Description.elementType = GL_UNSIGNED_BYTE;
            m_Field_Description.elementCount = 4;
            m_Field_Description.sizeInBytes = sizeof(unsigned char) * m_Field_Description.elementCount;
            m_Field_Description.shouldNormalize = true;
        }

        fields.push_back(field_type);
        vertexDescription.push_back(m_Field_Description);
        vertexSize += m_Field_Description.sizeInBytes;
    }

    void VertexLayoutDescription::SendVertexDescriptionToOpenGL() const noexcept
    {
        uintptr_t offSet_Count = 0;
        for(int i=0;i<vertexDescription.size();i++)
        {
            glCheck(glEnableVertexAttribArray(i));

            glCheck(glVertexAttribPointer(i,
                vertexDescription[i].elementCount, 
                vertexDescription[i].elementType, 
                vertexDescription[i].shouldNormalize, 
                vertexSize, (void*)offSet_Count));

            offSet_Count += vertexDescription[i].sizeInBytes;
        }
    }

}
