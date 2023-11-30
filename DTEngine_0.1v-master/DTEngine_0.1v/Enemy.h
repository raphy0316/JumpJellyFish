#pragma once
#include "Entity.h"
#include "Animation.h"
class Enemy :
	public Entity
{
public:
	Enemy();
	~Enemy();

	float gravity;
	bool safe;
	bool jump_support;
	float jump_time;
	float jump_power;
	int y;
	float jump_end;
	bool crashSide;
	int move_support;
	void Update(float dt);
	void Move(float dt);
	void Jump(float dt);

private:
	Animation* enemy_ani;
	float move_speed;	
};

