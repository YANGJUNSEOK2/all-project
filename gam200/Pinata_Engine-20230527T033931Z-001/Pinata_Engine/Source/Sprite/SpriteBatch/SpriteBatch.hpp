/************************************************************************
*	File name : SpriteBatch.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester
*************************************************************************/
#pragma once
#include <glew.h>
#include "../../Vertex/Vertex.hpp"
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "../../MathLibrary/MathLibrary.hpp"
#include "../../Texture/Texture.hpp"
#include "../../Engine/Engine.h"
#include "../../Physics/Physics.h"
#include "../../Sound/Sound.hpp"
#include "../../IO_Manager/file_IO.h"

class SoundEffect;
class BackgroundSound;

class Engine;

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

class SpriteBatch : public SoundEffect, public BackgroundSound
{
public:
    SpriteBatch();
    ~SpriteBatch() = default;


    void SpriteInit(std::string DataPath, Engine* game);
    void SpriteInit();

    void Begin(SpriteDataType p_SpriteDataType = SpriteDataType::TEXTURE);
    void End();

    void Draw(const Vector4<float>& p_DestRect, const Vector4<float>& p_UVRect, GLuint p_Texture, float p_Depth, const Color& p_Color);
    void Draw(const Vector4<float>& p_DestRect, const Vector4<float>& p_UVRect, GLuint p_Texture, float p_Depth, const Color& p_Color, float p_Angle);
    void Draw(const Vector4<float>& p_DestRect, const Vector4<float>& p_UVRect, GLuint p_Texture, float p_Depth, const Color& p_Color, const Vector2<float>& p_Dir);

    void Adding_Animation(Engine* game, float fram, int set_delay);
    void Adding_Screen(Engine* game);
    void SpriteRenderBatch();

    void Change_Color(Color color);

    std::string Path() { return m_Path; }
    void SetPath(std::string path) { m_Path = path; }

    void MouseCollision(bool boolean);
    bool Is_mouse_collided() const { return Is_Mouse_collide; }

	bool Has_Object_Rigidbody() const { return Has_rigidbody; }
	bool Is_Object_Collide() const { return Is_Collide; }

	void Object_colliding(bool collide) { Is_Collide = collide; }

    float X;
    float Y;
    float Width;
    float Height;

private:
    Color color;

    bool Has_rigidbody;
    bool Is_Collide;

    bool Mouse_collision;
    bool Is_Mouse_collide;
    float Frame;
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

