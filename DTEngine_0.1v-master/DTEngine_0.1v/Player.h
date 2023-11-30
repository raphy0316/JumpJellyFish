#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Ground.h"

class Player :
	public Entity
{
public:
	Player();
	~Player();
	int move_support;
	void Update(float dt);
	void Move(float dt);
	void Attack(float dt);

private:
	Sprite* player_spr;
	float move_speed;
	float attack_timer;
};

