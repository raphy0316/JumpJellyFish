#pragma once
#include "Entity.h"
#include "Sprite.h"
class Ground :
	public Entity
{
public:
	Ground();
	~Ground();
	float ground_time;
	void Update(float dt);
	void Move(float dt);

private:
	Sprite* ground_spr;
	float move_speed;
};

