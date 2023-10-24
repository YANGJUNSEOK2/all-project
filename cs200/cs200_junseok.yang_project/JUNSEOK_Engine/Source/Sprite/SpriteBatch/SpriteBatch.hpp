/************************************************************************
*	File name : SpriteBatch.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include <glew.h>
#include "../../Vertex/Vertex.hpp"
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "../../MathLibrary/MathLibrary.hpp"
#include "../../Texture/Texture.hpp"
#include "../../Main/Engine.h"

enum class SpriteDataType
{
    NONE,
    FRONT,
    BACK,
    TEXTURE

};

class SpriteData
{
public:
    SpriteData() {};
    SpriteData(const Vector4<float>& p_DestRect, const Vector4<float>& p_UVRect, GLuint p_Texture, float p_Depth, const Color& p_Color);
    SpriteData(const Vector4<float>& p_DestRect, const Vector4<float>& p_UVRect, GLuint p_Texture, float p_Depth, const Color& p_Color, float p_Angle);

    GLuint m_Texture{};
    float m_Depth{};
    Vertex m_topLeft;
    Vertex m_bottomLeft;
    Vertex m_topRight;
    Vertex m_bottomRight;

private:
    Vector2<float> rotate(const Vector2<float>& pos, float p_Angle);
};

class RenderBatch
{
public:
    RenderBatch(GLuint p_OffSet, GLuint p_NumVertices, GLuint p_Texture)
        :m_OffSet(p_OffSet), m_NumVertices(p_NumVertices), m_Texture(p_Texture)
    {}

    GLuint m_OffSet;
    GLuint m_NumVertices;
    GLuint m_Texture;
private:
};

class SpriteBatch
{
public:
    SpriteBatch();
    ~SpriteBatch() = default;

    void Init();
    void Init(float p_X, float p_Y, float p_Width, float p_Height, float frame, Color color, std::string texturePath);
    void Init(float p_X, float p_Y, float p_Width, float p_Height, float frame, float frame2, Color color, std::string texturePath);
    void Initial();
    void Begin(SpriteDataType p_SpriteDataType = SpriteDataType::TEXTURE);
    void End();

    void Draw(const Vector4<float>& p_DestRect, const Vector4<float>& p_UVRect, GLuint p_Texture, float p_Depth, const Color& p_Color);
    void Draw(const Vector4<float>& p_DestRect, const Vector4<float>& p_UVRect, GLuint p_Texture, float p_Depth, const Color& p_Color, float p_Angle);
    void Draw(const Vector4<float>& p_DestRect, const Vector4<float>& p_UVRect, GLuint p_Texture, float p_Depth, const Color& p_Color, const Vector2<float>& p_Dir);

    void Adding_Screen(Engine* game, bool animation, int set_delay);
    void Adding_Screen(Engine* game);
    void Adding_Screen(Engine* game, bool t);
    void SpriteRenderBatch();

    void Change_Color(Color color);

    std::string Path() { return m_Path; }

    void MouseCollision(bool boolean);
    bool Is_mouse_collided() const { return Is_Mouse_collide; };

    float X;
    float Y;
    float Width;
    float Height;
private:
    Color color;
    bool Has_rigidbody;
    bool Is_Ghost;
    bool Mouse_collision;
    bool Is_Mouse_collide;
    float Frame;
    float Frame2;
    float FrameCount;
    int Delay;

    void CreateRenderBatch();
    void CreateVertexArrays();
    void TypeSpriteData();

    static bool CompareFront(SpriteData* p_Data1, SpriteData* p_Data2);
    static bool CompareBack(SpriteData* p_Data1, SpriteData* p_Data2);
    static bool CompareTexture(SpriteData* p_Data1, SpriteData* p_Data2);

    GLuint m_VBO;
    GLuint m_VAO;

    SpriteDataType m_SpriteDataType;

    std::vector<SpriteData*> m_SpritsDatas;
    std::vector<SpriteData> m_SpriteData;
    std::vector<RenderBatch> m_RenderBatch;

    std::string m_Path;
};

