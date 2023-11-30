#include "pch.h"
#include "Player.h"
#include "World.h"
#include "Ground.h"
#include "GameScene.h"

Player::Player() : move_speed(30.0f), attack_timer(0.0f)
{
	player_spr = new Sprite(L"../Resource/player/bodyFinal/5.png");
	AddChild(player_spr);

	SetRect(player_spr->GetRect());	
}


Player::~Player()
{
}

void Player::Update(float dt)
{
	Entity::Update(dt);
	Move(dt);
	Attack(dt);
}

void Player::Move(float dt)
{
	Vec3 pos = GetPosition();
	
	int r = Random(1, 2);
	if (move_support){
		r = move_support;
	}
	if (r == 1){
		if (pos.x + move_speed > 240){
			move_support = 2;
		}

		pos.x += move_speed;
		if (move_support)
			move_support = 0;
		else
			move_support = 1;
	}
	else{
		if (pos.x - move_speed < -240){
			move_support = 1;
		}
		pos.x -= move_speed;
		if (move_support)
			move_support = 0;
		else
			move_support = 2;
	}

	SetPosition(pos);
	
}

void Player::Attack(float dt)
{
	attack_timer += dt;
	if (1){
		if (attack_timer >= 0.3f){
			attack_timer = 0.0f;

			GameScene* gs = (GameScene*)World::GetInstance().GetCurrentScene();
			Ground* ground = new Ground();
			Vec3 pos = GetPosition() + Vec3(0.0f , GetRect().Center().y, 0.0f);
			ground->SetPosition(pos);
			gs->GetGroundEntity()->AddChild(ground);
		}
	}
}