#include "StaticSprite.hpp"

namespace JS_Engine {
    namespace Graphics {
        using namespace MathLibrary;
        StaticSprite::StaticSprite(float p_XComponent, float p_YComponent, float p_Width, float p_Height, const Vector4 &p_Color, Shader &p_Shader)
            : Render(Vector3(p_XComponent, p_YComponent, 0), Vector2(p_Width, p_Height), p_Color), m_Shader(p_Shader) {
            m_VertexArray = new VertexArray();
            GLfloat Vertices[] = {
                0,		 0,		   0,
                0,		 p_Height, 0,
                p_Width, p_Height, 0,
                p_Width, 0,		   0
            };
            GLfloat Colors[] = {
                p_Color.XComponent, p_Color.YComponent, p_Color.ZComponent, p_Color.WComponent,
                p_Color.XComponent, p_Color.YComponent, p_Color.ZComponent, p_Color.WComponent,
                p_Color.XComponent, p_Color.YComponent, p_Color.ZComponent, p_Color.WComponent,
                p_Color.XComponent, p_Color.YComponent, p_Color.ZComponent, p_Color.WComponent
            };
            m_VertexArray->AddBuffer(new VertexBuffer(Vertices, 4 * 3, 3), 0);
            m_VertexArray->AddBuffer(new VertexBuffer(Colors, 4 * 4, 4), 1);

            GLuint Indices[] = {
                0, 1, 2,
                2, 3, 0
            };
            m_IndexBuffer = new IndexBuffer(Indices, 6);
        }

        StaticSprite::~StaticSprite() {
            delete m_VertexArray;
            delete m_IndexBuffer;
        }
    }
}