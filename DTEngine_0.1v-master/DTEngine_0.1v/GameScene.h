#pragma once
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"

class GameScene :
	public Scene
{
public:
	GameScene();
	~GameScene();
	bool crashTop;
	Vec3 prePos;
	float score;
	Vec3 backPos[2];
	bool a;
	int life;
	float background_timer;
	void Update(float dt);
	void AttackEnemy(float dt);
	Sprite* life_spr[3];

	Entity* GetGroundEntity();
	

private:
	Sprite * background_sqr[2];
	Player* player;
	Enemy* enemy;
	Entity* ground_entities;
	Entity* enemy_entities;
};

