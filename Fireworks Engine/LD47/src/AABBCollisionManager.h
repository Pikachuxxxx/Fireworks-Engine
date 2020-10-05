#pragma once

#include <fireworks.h>
using namespace fireworks;

class AABBCollisionManager
{
public:
	bool CheckCollision(Sprite& gameObject_1, Sprite& gameObject_2)
	{
		bool collisionX = gameObject_1.position.x + gameObject_1.size.x >= gameObject_2.position.x && gameObject_2.position.x + gameObject_2.size.x >= gameObject_1.position.x;
		bool collisionY = gameObject_1.position.y + gameObject_1.size.y >= gameObject_2.position.y && gameObject_2.position.y + gameObject_2.size.y >= gameObject_1.position.y;

		return collisionX && collisionY;

	}
};