#include "pch.h"
#include "Scene.h"


Scene::Scene() : follow_target_(nullptr), offset_(0, 0),camera_(nullptr)
{
	camera_ = new Camera();
	camera_->SetPosition(0.0f, 0.0f, -5.0f);

	light_ = new Light();
	light_->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);//ºûÀÌ ¾ÈºñÄ¥‹š ÃÖ¼ÒÇÑ ¿µÇâ¹Þ´Â ºûÀÇ Å©±â
	light_->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);//¿ÏÀüÈ÷ºñÃÆÀ»¶§  ¹Þ´Â ºûÀÇ »ö±ò
	light_->SetDirection(10.0f, 10.0f, 10.0f);
}


Scene::~Scene()
{
	delete camera_;
	delete light_;
}

void Scene::Update(float dt)
{
	Entity::Update(dt);

	D3DXVECTOR2 target_pos = offset_;
	
	if (follow_target_) {
		target_pos = D3DXVECTOR2(follow_target_->GetPosition().x, follow_target_->GetPosition().y);
	}
	
	D3DXVECTOR2 camera_pos = D3DXVECTOR2(camera_->GetPosition().x, camera_->GetPosition().y);
	D3DXVECTOR2 p = (target_pos + offset_ - camera_pos) * 0.15f + camera_pos;
	camera_->SetPosition(p.x, p.y, camera_->GetPosition().z);
}

void Scene::Follow(Entity* target, D3DXVECTOR2 offset)
{
	follow_target_ = target;
	offset_ = offset;
}

void Scene::UnFollow()
{
	follow_target_ = nullptr;
	offset_ = D3DXVECTOR2(0.0f, 0.0f);
}

void Scene::Shake(int cnt, float range, float duration)
{
	shake_timer_.Reset(duration, cnt);
	shake_timer_.OnTick = [=]() {
		D3DXVECTOR3 pos = camera_->GetPosition();
		camera_->SetPosition(pos.x + Random(-range, range), pos.y + Random(-range, range), pos.z);
	};
}

Camera* Scene::GetCamera()
{
	return camera_;
}

Light* Scene::GetLight()
{
	return light_;
}