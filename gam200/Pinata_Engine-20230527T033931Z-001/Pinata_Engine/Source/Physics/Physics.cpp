#include "Physics.h"


bool Physics::IsCollidingWith_Mouse(Engine* game, SpriteBatch* sprite)
{
	int mouse_x = static_cast<int>(game->getMouse().Get_Mouse_Pos().x);
	int mouse_y = static_cast<float>(game->getMouse().Get_Mouse_Pos().y);

    int left = sprite->X;
    int right = sprite->X + sprite->Width;
    int up = sprite->Y + sprite->Height;
    int down = sprite->Y;

    if (left <= mouse_x && right >= mouse_x
        && down <= -mouse_y && up >= -mouse_y)
    {
        return true;
    }

    return false;
}

void Physics::IsCollidingWith_Object(Engine* game, std::vector<SpriteBatch*> objects)
{	
	if (!objects.empty())
	{
		const unsigned int size = objects.size();
		for(unsigned __int64 i=0 ; i <size
			;++i)
		{
			Collision_Check(objects[i], objects,size);
		}
	}
	else
	{
		std::cout << "there is no rigidbody objects\n";
	}
}

void Physics::Collision_Check(SpriteBatch* Obj1, std::vector<SpriteBatch*> objects, const unsigned int size)
{
	const float obj1_min_X = Obj1->X;
	const float obj1_max_X = obj1_min_X + Obj1->Width;
	const float obj1_min_Y = Obj1->Y;
	const float obj1_max_Y = obj1_min_Y + Obj1->Height;

	float obj2_max_X = 0;
	float obj2_max_Y = 0;
	float obj2_min_X = 0;
	float obj2_min_Y = 0;
	Obj1->Object_colliding(false);
	if (size > 1)
	{
		for (unsigned __int64 i = 0; i < size; i++)
		{ // AABB
			
			obj2_min_X = objects[i]->X;
			obj2_max_X = obj2_min_X + objects[i]->Width;
			obj2_min_Y = objects[i]->Y;
			obj2_max_Y = obj2_min_Y + objects[i]->Height;
			
			if (
				obj1_max_X == obj2_max_X && 
				obj1_min_X == obj2_min_X && 
				obj1_max_Y == obj2_max_Y && 
				obj1_min_Y == obj2_min_Y)
			{
				// Object's own collision detection exception
			}
			else
			{
				// AABB collision detection
				
				//-B.Left + B.Width > A.Left && A.Left + A.Width > B.left

				//	- B.Bottom + B.Height > A.Bottom && A.Bottom + A.Height > B.Bottom

				if ((obj1_max_X > obj2_min_X && obj2_max_X > obj1_min_X) &&
					(obj1_max_Y > obj2_min_Y && obj2_max_Y > obj1_min_Y))
				{
					//std::cout << " Collide!! \n";
					Obj1->Object_colliding(true);
					objects[i]->Object_colliding(true);
				}
			}
		}
	}
}
