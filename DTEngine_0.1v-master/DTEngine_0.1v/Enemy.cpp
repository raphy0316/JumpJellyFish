#include "pch.h"
#include "Enemy.h"
#include "World.h"
#include "GameScene.h"


Enemy::Enemy() : move_speed(450.0f)
{
	enemy_ani = new Animation(L"../Resource/enemy/jellyfish/small", 10);
	AddChild(enemy_ani);

	SetRect(enemy_ani->GetRect());

	safe = false;
	jump_support = false;
	jump_time = 0.0f;
	jump_power = 60.0f;
	gravity = 5.0f;
	crashSide = false;
}


Enemy::~Enemy()
{
}

void Enemy::Update(float dt)
{
	Entity::Update(dt);
	Move(dt);
	if (World::GetInstance().GetKeyState(VK_SPACE) > 0&&jump_end){
		jump_support = true;
		y = GetPosition().y;
	}
	if (jump_support)
		Jump(dt);
	

}

void Enemy::Move(float dt)
{
	Vec3 pos = GetPosition();
	if (!safe){
		pos.y -= 450 * dt;
	}
	else {
		pos.y += move_speed * dt;
	}
		
	if (!crashSide){
		if (pos.x <= -240) {
			pos.x = -240;
		}
		else if (World::GetInstance().GetKeyState(VK_LEFT) > 0){
			pos.x -= move_speed * dt;
		}
		if (pos.x >= 240) {
			pos.x = 240;
		}
		else if (World::GetInstance().GetKeyState(VK_RIGHT) > 0){
			pos.x += move_speed * dt;
		}
	}
	
	SetPosition(pos);
}
void Enemy::Jump(float dt){
	Vec3 pos = GetPosition();
	jump_end = false;
	float height = (jump_time * jump_time * (-450) / 2) + (jump_time * jump_power);
	pos.y += height;
	jump_time += dt;
	
	if (height <0){
		jump_support = false;
		jump_time = 0.0f;
	}
	SetPosition(pos);
}


