#include "pch.h"
#include "GameScene.h"
#include "Enemy.h"
#include "World.h"
#include "EndScene.h"
GameScene::GameScene()
{
	
	background_sqr[0] = new Sprite(L"../Resource/map/background.png");
	background_sqr[1] = new Sprite(L"../Resource/map/background.png");
	AddChild(background_sqr[0]);
	AddChild(background_sqr[1]);
	life_spr[0] = new Sprite(L"../Resource/Resource/life.png");
	life_spr[1] = new Sprite(L"../Resource/Resource/life.png");
	life_spr[2] = new Sprite(L"../Resource/Resource/life.png");
	AddChild(life_spr[0]);
	AddChild(life_spr[1]);
	AddChild(life_spr[2]);

	player = new Player();
	player->SetPosition(Vec3(0, -700,0));
	AddChild(player);

	ground_entities = new Entity();
	AddChild(ground_entities);

	enemy_entities = new Entity();
	AddChild(enemy_entities);


	enemy = new Enemy();
	enemy->SetPosition(Vec3(0,350, 0.0f));
	enemy_entities->AddChild(enemy);
	crashTop = false;
	prePos = enemy->GetPosition();
	backPos[0] = Vec3(0, -1900, 0);
	backPos[1] = Vec3(0, -6200, 0);
	background_sqr[0]->SetPosition(backPos[0]);
	background_sqr[1]->SetPosition(backPos[1]);
	life_spr[0]->SetPosition(Vec3(-700, 500, 0));
	life_spr[1]->SetPosition(Vec3(-600, 500, 0));
	life_spr[2]->SetPosition(Vec3(-500, 500, 0));

	a = false;
	life = 3;
}


GameScene::~GameScene()
{
}

void GameScene::Update(float dt)
{
	Scene::Update(dt);
	AttackEnemy(dt);
	score += dt;

	backPos[0].y += 450 * dt;
	backPos[1].y += 450 * dt;
	background_sqr[0]->SetPosition(backPos[0]);
	background_sqr[1]->SetPosition(backPos[1]);
	background_timer += 450 * dt;
	if (backPos[0].y >= 2900) {
		backPos[0].y -= 6450;
	}
	if (backPos[1].y >= 2900) {
		backPos[1].y -= 6450;
	}
	Vec3 pos = enemy->GetPosition();
	if (pos.y>540||pos.y<-540||pos.x>1000|| pos.x<-1000) {
		
		if (--life == 0) {
			World::GetInstance().ChangeScene(new EndScene());
			return;
		}
		RemoveChild(life_spr[life]);
		enemy->SetPosition(Vec3(0, 350, 0));
	}
	
	
}
Entity* GameScene::GetGroundEntity()
{
	return ground_entities;
}

void GameScene::AttackEnemy(float dt)
{
	if (enemy->safe) {
		prePos = enemy->GetPosition();
	}
	bool tmp = false;
	for (auto entity2 : enemy_entities->GetChildren()){
		Enemy* enemy = (Enemy*)entity2;
		crashTop = false;
		for (auto entity : ground_entities->GetChildren()){
			Ground* ground = (Ground*)entity;
			if (ground->GetRect().Offset(Vec2(ground->GetPosition().x, ground->GetPosition().y)).IntersectsRect(enemy->GetRect(), Vec2(enemy->GetPosition().x, enemy->GetPosition().y))){
				if (prePos.y-30 > ground->GetPosition().y + 30.0f){
					crashTop = true;
					enemy->safe = true;
					enemy->jump_end = true; 
					
					Vec3 pos = enemy->GetPosition();
					pos.y = ground->GetPosition().y + 70.0f;
					enemy->SetPosition(pos);

					ground->ground_time += dt;
					if (ground->ground_time > 0.3f){
						RemoveChild(ground);
					}
				}
				else {
					tmp = true;
				}
			}
		}
		if (!crashTop){
			enemy->safe = false;
		}
		prePos = enemy->GetPosition();
		enemy->crashSide = tmp;
	}

}