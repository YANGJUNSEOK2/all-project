/************************************************************************
*	File name : SpriteBatch.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author : Minho Chae
*			        Others : Wonyong Lee
*
*	File description :
*	2019 Fall Semester
*************************************************************************/
#include "SpriteBatch.hpp"

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
    topLeft = rotate_By(p_Angle, topLeft) + halfSize;
    bottomLeft = rotate_By(p_Angle, bottomLeft) + halfSize;
    bottomRight = rotate_By(p_Angle, bottomRight) + halfSize;
    topRight = rotate_By(p_Angle, topRight) + halfSize;

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

SpriteBatch::SpriteBatch() : m_VBO(0), m_VAO(0)
{
}

void SpriteBatch::SpriteInit(std::string DataPath, Engine* game)
{
    FileIO m_file;

    m_file.OpenReadFile(DataPath);

    m_file.GetFloat(&X);
    m_file.GetFloat(&Y);
    m_file.GetFloat(&Width);
    m_file.GetFloat(&Height);
    m_file.GetColor(&color);
    m_file.GetString(&m_Path);
    m_file.GetBool(&Has_rigidbody);
    m_file.GetBool(&Is_Collide);
    m_file.GetBool(&Is_Mouse_collide);
    m_file.GetBool(&Mouse_collision);
    m_file.GetInt(&Delay);

    m_file.CloseReadFile();

    CreateVertexArrays();
    if (Has_rigidbody)
    {
        game->Adding_Objects_To_ObjectsFactory(this);
    }
}

void SpriteBatch::SpriteInit()
{
    CreateVertexArrays();
}

void SpriteBatch::Begin(SpriteDataType p_SpriteDataType)
{
    m_SpriteDataType = p_SpriteDataType;
    m_SpriteData.clear();
    m_RenderBatch.clear();
}

void SpriteBatch::End()
{
    m_SpritsDatas.resize(m_SpriteData.size());
    for (int i = 0; i < m_SpriteData.size(); i++)
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

void SpriteBatch::Adding_Animation(Engine* game, float frame, int set_delay)
{
    Delay++;
    Begin();
    Vector4<float> position(X, Y, Width, Height);
    Vector4<float> uv;

    float clip = (float)(1 / frame);
    uv = { FrameCount * clip, 0, clip, -1 };
    if (Delay == set_delay)
    {
        FrameCount++;
        Delay = 0;
    }

    if (FrameCount / frame >= frame)
    {
        FrameCount = 0;
    }

    GLTexture texture = Texture::GetTexture(Path());
    Draw(position, uv, texture.id, 0.0f, color);
    if (Mouse_collision == true)
    {
        Is_Mouse_collide = Physics::IsCollidingWith_Mouse(game, this);
    }
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
    if (Mouse_collision == true)
    {
        Is_Mouse_collide = Physics::IsCollidingWith_Mouse(game, this);
    }
    End();
    SpriteRenderBatch();
}

void SpriteBatch::SpriteRenderBatch()
{
    glBindVertexArray(m_VAO);

    for (int i = 0; i < m_RenderBatch.size(); i++)
    {
        glBindTexture(GL_TEXTURE_2D, m_RenderBatch[i].m_Texture);

        glDrawArrays(GL_TRIANGLES, m_RenderBatch[i].m_OffSet, m_RenderBatch[i].m_NumVertices);
    }

    glBindVertexArray(0);
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

    for (int currSprite = 1; currSprite < m_SpritsDatas.size(); currSprite++)
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
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, p_Vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, p_Vertices.size() * sizeof(Vertex), p_Vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::CreateVertexArrays()
{
    if (m_VAO == 0)
    {
        glGenVertexArrays(1, &m_VAO);
    }
    glBindVertexArray(m_VAO);
    if (m_VBO == 0)
    {
        glGenBuffers(1, &m_VBO);
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    //This is position attribute pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    //This is color attribute pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    //This is uv attribute pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);
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


