#include "pch.h"
#include "Ground.h"



Ground::Ground() : move_speed(450.0f)
{
	ground_spr = new Sprite(L"../Resource/ground_small.png");
	AddChild(ground_spr);

	SetRect(ground_spr->GetRect());
	ground_time = 0;
}


Ground::~Ground()
{
}


void Ground::Update(float dt)
{
	Entity::Update(dt);

	Move(dt);
}

void Ground::Move(float dt)
{
	D3DXVECTOR3 pos = GetPosition();
	pos.y += move_speed * dt;
	SetPosition(pos);
}
