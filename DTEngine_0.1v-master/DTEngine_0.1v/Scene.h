#pragma once
#include "Entity.h"
#include "Camera.h"
#include "Light.h"
#include "Timer.h"

class Scene :
	public Entity
{
public:
	Scene();
	~Scene();

	void Update(float dt);
	void Follow(Entity* target, D3DXVECTOR2 offset = D3DXVECTOR2(0, 0));
	void UnFollow();
	void Shake(int cnt, float range, float duration);

	Camera* GetCamera();
	Light* GetLight();
	
private:
	Entity* follow_target_;
	D3DXVECTOR2 offset_;
	Camera* camera_;
	Light* light_;
	Timer shake_timer_;
};

