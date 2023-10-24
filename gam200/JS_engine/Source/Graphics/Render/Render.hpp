#pragma once
#include "../Shader/Shader.hpp"
#include "../Buffer/BufferLibrary.hpp"
#include "../../MathLibrary/MathLibrary.hpp"

namespace JS_Engine {
    namespace Graphics {
        using namespace MathLibrary;
        struct VertexData {
            Vector3 Vertex;
            //Vector4 Color;
            unsigned int Color;
        };
        class Render {
        public:
            inline const Vector3 &GetPosition() const { return m_Position; }
            inline const Vector2 &GetSize()		const { return m_Size; }
            inline const Vector4 &GetColor()	const { return m_Color; }

            Render(Vector3 p_Position, Vector2 p_Size, Vector4 p_Color) : m_Position(p_Position), m_Size(p_Size), m_Color(p_Color) { }

            virtual ~Render() { }
        protected:
            Vector3	m_Position;
            Vector2	m_Size;
            Vector4	m_Color;
        };
    }
}