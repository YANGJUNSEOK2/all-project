#pragma once
#include "../Engine/Engine.h"
class Engine;
class SpriteBatch;

class Physics
{
public:
	static bool IsCollidingWith_Mouse(Engine* game, SpriteBatch* sprite);
	static void IsCollidingWith_Object(Engine* game, std::vector<SpriteBatch*> objects);
	static void Collision_Check(SpriteBatch* Obj1, std::vector<SpriteBatch*> objects, const unsigned int size);

private:
};