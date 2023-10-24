/************************************************************************
*	File name : SpriteBatch.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/
#include "SpriteBatch.hpp"
#include "../../Shader/glCheck/glCheck.hpp"

SpriteData::SpriteData(const Vector4<float>& p_DestRect, const Vector4<float>& p_UVRect, GLuint p_Texture, float p_Depth,
    const Color& p_Color) : m_Texture(p_Texture), m_Depth(p_Depth)
{
    m_topLeft.color = p_Color;
    m_topLeft.setPosition(p_DestRect.x, p_DestRect.y + p_DestRect.w);
    m_topLeft.setUV(p_UVRect.x, p_UVRect.y + p_UVRect.w);

    m_bottomLeft.color = p_Color;
    m_bottomLeft.setPosition(p_DestRect.x, p_DestRect.y);
    m_bottomLeft.setUV(p_UVRect.x, p_UVRect.y);

    m_bottomRight.color = p_Color;
    m_bottomRight.setPosition(p_DestRect.x + p_DestRect.z, p_DestRect.y);
    m_bottomRight.setUV(p_UVRect.x + p_UVRect.z, p_UVRect.y);

    m_topRight.color = p_Color;
    m_topRight.setPosition(p_DestRect.x + p_DestRect.z, p_DestRect.y + p_DestRect.w);
    m_topRight.setUV(p_UVRect.x + p_UVRect.z, p_UVRect.y + p_UVRect.w);
}

SpriteData::SpriteData(const Vector4<float>& p_DestRect, const Vector4<float>& p_UVRect, GLuint p_Texture, float p_Depth,
    const Color& p_Color, float p_Angle) : m_Texture(p_Texture), m_Depth(p_Depth)
{
    Vector2<float> halfSize(p_DestRect.z / 2.0f, p_DestRect.w / 2.0f);

    // Get points centered at origin
    Vector2<float> topLeft(-halfSize.x, halfSize.y);
    Vector2<float> bottomLeft(-halfSize.x, -halfSize.y);
    Vector2<float> bottomRight(halfSize.x, -halfSize.y);
    Vector2<float> topRight(halfSize.x, halfSize.y);

    // Rotate the points
    topLeft = rotate(topLeft, p_Angle) + halfSize;
    bottomLeft = rotate(bottomLeft, p_Angle) + halfSize;
    bottomRight = rotate(bottomRight, p_Angle) + halfSize;
    topRight = rotate(topRight, p_Angle) + halfSize;

    m_topLeft.color = p_Color;
    m_topLeft.setPosition(p_DestRect.x + topLeft.x, p_DestRect.y + topLeft.y);
    m_topLeft.setUV(p_UVRect.x, p_UVRect.y + p_UVRect.w);

    m_bottomLeft.color = p_Color;
    m_bottomLeft.setPosition(p_DestRect.x + bottomLeft.x, p_DestRect.y + bottomLeft.y);
    m_bottomLeft.setUV(p_UVRect.x, p_UVRect.y);

    m_bottomRight.color = p_Color;
    m_bottomRight.setPosition(p_DestRect.x + bottomRight.x, p_DestRect.x + bottomRight.y);
    m_bottomRight.setUV(p_UVRect.x + p_UVRect.z, p_UVRect.y);

    m_topRight.color = p_Color;
    m_topRight.setPosition(p_DestRect.x + topRight.x, p_DestRect.y + topRight.y);
    m_topRight.setUV(p_UVRect.x + p_UVRect.z, p_UVRect.y + p_UVRect.w);
}

Vector2<float> SpriteData::rotate(const Vector2<float>& pos, float p_Angle)
{
    Vector2<float> dir;
    dir.x = pos.x * cos(p_Angle) - pos.y * sin(p_Angle);
    dir.y = pos.x * sin(p_Angle) + pos.y * cos(p_Angle);
    return dir;
}

SpriteBatch::SpriteBatch() : m_VBO(0), m_VAO(0), Delay(0), Frame(0.0f), Frame2(0.0f), 
FrameCount(0.0f),Has_rigidbody(false),Height(0.0f),Is_Ghost(false),Is_Mouse_collide(false),
Mouse_collision(false),m_SpriteDataType(),Width(0.0f),X(0.0f),Y(0.0f)
{
}

void SpriteBatch::Init()
{
    CreateVertexArrays();
}

void SpriteBatch::Init(float p_X, float p_Y, float p_Width, float p_Height, float frame, Color color, std::string texturePath)
{
    X = p_X;
    Y = p_Y;
    Width = p_Width;
    Height = p_Height;
    m_Path = texturePath;
    this->color = color;
    Has_rigidbody = false;
    Is_Ghost = false;
    Frame = frame;
    Is_Mouse_collide = false;
    Mouse_collision = false;
    Delay = 0;
    CreateVertexArrays();
}

void SpriteBatch::Init(float p_X, float p_Y, float p_Width, float p_Height, float frame, float frame2, Color color, std::string texturePath)
{
    X = p_X;
    Y = p_Y;
    Width = p_Width;
    Height = p_Height;
    m_Path = texturePath;
    this->color = color;
    Has_rigidbody = false;
    Is_Ghost = false;
    Frame = frame;
    Frame2 = frame2;
    Is_Mouse_collide = false;
    Mouse_collision = false;
    Delay = 0;
    CreateVertexArrays();
}

void SpriteBatch::Initial()
{
    CreateVertexArrays();
}

void SpriteBatch::Begin(SpriteDataType p_SpriteDataType)
{
    m_SpriteDataType = p_SpriteDataType;
    m_RenderBatch.clear();
    m_SpriteData.clear();
}

void SpriteBatch::End()
{
    m_SpritsDatas.resize(m_SpriteData.size());
    for (int i = 0; i < static_cast<signed>(m_SpriteData.size()); i++)
    {
        m_SpritsDatas[i] = &m_SpriteData[i];
    }

    TypeSpriteData();
    CreateRenderBatch();
}

void SpriteBatch::Draw(const Vector4<float>& p_DestRect, const Vector4<float>& p_UVRect, GLuint p_Texture,
    float p_Depth, const Color& p_Color)
{
    m_SpriteData.emplace_back(p_DestRect, p_UVRect, p_Texture, p_Depth, p_Color);
}

void SpriteBatch::Draw(const Vector4<float>& p_DestRect, const Vector4<float>& p_UVRect, GLuint p_Texture, float p_Depth,
    const Color& p_Color, float p_Angle)
{
    m_SpriteData.emplace_back(p_DestRect, p_UVRect, p_Texture, p_Depth, p_Color, p_Angle);
}

void SpriteBatch::Draw(const Vector4<float>& p_DestRect, const Vector4<float>& p_UVRect, GLuint p_Texture, float p_Depth,
    const Color& p_Color, const Vector2<float>& p_Dir)
{
    const Vector2<float> right(1.0f, 0.0f);
    float p_Angle = acos(dot(right, p_Dir));
    if (p_Dir.y < 0.0f) p_Angle = -p_Angle;

    m_SpriteData.emplace_back(p_DestRect, p_UVRect, p_Texture, p_Depth, p_Color, p_Angle);
}

void SpriteBatch::Adding_Screen(Engine* game, bool animation, int set_delay)
{
    Delay++;
    Begin();
    Vector4<float> position(X, Y, Width, Height);
    Vector4<float> uv;
    if (animation == true)
    {
        float clip = (float)(1 / Frame);
        uv = { FrameCount * clip, 0, clip, -1 };
        if (Delay == set_delay)
        {
            FrameCount++;
            Delay = 0;
        }

        if (FrameCount / Frame >= Frame)
        {
            FrameCount = 0;
        }
    }
    else
    {
        uv = { 0, 0, 1, -1 };
    }
    GLTexture texture = Texture::GetTexture(Path());
    Draw(position, uv, texture.id, 0.0f, color);

    End();
    SpriteRenderBatch();
}

void SpriteBatch::Adding_Screen(Engine* game, bool t)
{
    Begin();
    Vector4<float> position(X, Y, Width, Height);
    Vector4<float> uv;

    float clip = (float)(1 / Frame);
    float clip2 = (float)(1 / Frame2);
    uv = { clip, clip2, clip, -clip2 };

    GLTexture texture = Texture::GetTexture(Path());
    Draw(position, uv, texture.id, 0.0f, color);

    End();
    SpriteRenderBatch();
}

void SpriteBatch::Adding_Screen(Engine* game)
{
    Begin();
    Vector4<float> position(X, Y, Width, Height);
    Vector4<float> uv = { 0, 0, 1, -1 };
    GLTexture texture = Texture::GetTexture(Path());
    Draw(position, uv, texture.id, 0.0f, color);

    End();
    SpriteRenderBatch();
}

void SpriteBatch::SpriteRenderBatch()
{
    glCheck(glBindVertexArray(m_VAO));

    for (int i = 0; i < static_cast<signed>(m_RenderBatch.size()); i++)
    {
        glBindTexture(GL_TEXTURE_2D, m_RenderBatch[i].m_Texture);

        glDrawArrays(GL_TRIANGLES, m_RenderBatch[i].m_OffSet, m_RenderBatch[i].m_NumVertices);
    }

    glCheck(glBindVertexArray(0));
}

void SpriteBatch::Change_Color(Color color)
{
    this->color = color;
}

void SpriteBatch::MouseCollision(bool boolean)
{
    Mouse_collision = boolean;
}

void SpriteBatch::CreateRenderBatch()
{
    std::vector<Vertex> p_Vertices;
    p_Vertices.resize(m_SpritsDatas.size() * 6);

    if (m_SpritsDatas.empty())
    {
        return;
    }

    int offset = 0;
    int currVertex = 0;
    m_RenderBatch.emplace_back(offset, 6, m_SpritsDatas[0]->m_Texture);
    p_Vertices[currVertex++] = m_SpritsDatas[0]->m_topLeft;
    p_Vertices[currVertex++] = m_SpritsDatas[0]->m_bottomLeft;
    p_Vertices[currVertex++] = m_SpritsDatas[0]->m_bottomRight;
    p_Vertices[currVertex++] = m_SpritsDatas[0]->m_bottomRight;
    p_Vertices[currVertex++] = m_SpritsDatas[0]->m_topRight;
    p_Vertices[currVertex++] = m_SpritsDatas[0]->m_topLeft;
    offset += 6;

    for (int currSprite = 1; currSprite < static_cast<signed>(m_SpritsDatas.size()); currSprite++)
    {
        if (m_SpritsDatas[currSprite]->m_Texture != m_SpritsDatas[currSprite - 1]->m_Texture)
        {
            m_RenderBatch.emplace_back(offset, 6, m_SpritsDatas[currSprite]->m_Texture);
        }
        else
        {
            m_RenderBatch.back().m_NumVertices += 6;
        }
        p_Vertices[currVertex++] = m_SpritsDatas[currSprite]->m_topLeft;
        p_Vertices[currVertex++] = m_SpritsDatas[currSprite]->m_bottomLeft;
        p_Vertices[currVertex++] = m_SpritsDatas[currSprite]->m_bottomRight;
        p_Vertices[currVertex++] = m_SpritsDatas[currSprite]->m_bottomRight;
        p_Vertices[currVertex++] = m_SpritsDatas[currSprite]->m_topRight;
        p_Vertices[currVertex++] = m_SpritsDatas[currSprite]->m_topLeft;
        offset += 6;
    }
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
    glCheck(glBufferData(GL_ARRAY_BUFFER, p_Vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW));
    glCheck(glBufferSubData(GL_ARRAY_BUFFER, 0, p_Vertices.size() * sizeof(Vertex), p_Vertices.data()));
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void SpriteBatch::CreateVertexArrays()
{
    if (m_VAO == 0)
    {
        glCheck(glGenVertexArrays(1, &m_VAO));
    }
    glCheck(glBindVertexArray(m_VAO));
    if (m_VBO == 0)
    {
        glCheck(glGenBuffers(1, &m_VBO));
    }
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));

    glCheck(glEnableVertexAttribArray(0));
    glCheck(glEnableVertexAttribArray(1));
    glCheck(glEnableVertexAttribArray(2));

    //This is position attribute pointer
    glCheck(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)));
    //This is color attribute pointer
    glCheck(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)));
    //This is uv attribute pointer
    glCheck(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv)));

    glCheck(glBindVertexArray(0));
}

void SpriteBatch::TypeSpriteData()
{
    switch (m_SpriteDataType)
    {
    case SpriteDataType::FRONT:
        std::stable_sort(m_SpritsDatas.begin(), m_SpritsDatas.end(), CompareFront);
        break;
    case SpriteDataType::BACK:
        std::stable_sort(m_SpritsDatas.begin(), m_SpritsDatas.end(), CompareBack);
        break;
    case SpriteDataType::TEXTURE:
        std::stable_sort(m_SpritsDatas.begin(), m_SpritsDatas.end(), CompareTexture);
        break;
    }
}

bool SpriteBatch::CompareFront(SpriteData* p_Data1, SpriteData* p_Data2)
{
    return (p_Data1->m_Depth < p_Data2->m_Depth);
}

bool SpriteBatch::CompareBack(SpriteData* p_Data1, SpriteData* p_Data2)
{
    return (p_Data1->m_Depth > p_Data2->m_Depth);
}

bool SpriteBatch::CompareTexture(SpriteData* p_Data1, SpriteData* p_Data2)
{
    return (p_Data1->m_Texture < p_Data2->m_Texture);
}


