#include "pch.h"
#include "Sprite.h"
#include "World.h"
#include "Asset.h"


Sprite::Sprite() : texture_(nullptr), light_enabled_(false)
{
}

Sprite::Sprite(wstring path) : texture_(nullptr), light_enabled_(false)
{
	SetPath(path);
}


Sprite::~Sprite()
{
}

void Sprite::SetPath(wstring path)
{
	texture_ = Asset::GetInstance().GetTexture(path);
	SetRect(Rect(0, 0, texture_->GetInfo().Width, texture_->GetInfo().Height));
}

void Sprite::Render()
{
	if (!GetVisible() || texture_ == nullptr) return;
	Entity::Render();

	World::GetInstance().GetBitmap()->Render(this);

	if(light_enabled_)
		World::GetInstance().RenderLightShader(GetWorldMatrix(), texture_->GetIndexCount(), texture_->GetTexture());
	else
		World::GetInstance().RenderTextureShader(GetWorldMatrix(), texture_->GetIndexCount(), texture_->GetTexture());
}

Texture* Sprite::GetTexture()
{
	return texture_;
}

void Sprite::SetTexture(Texture* texture)
{
	texture_ = texture;
}

bool Sprite::GetLightEnabled()
{
	return light_enabled_;
}

void Sprite::SetLightEnabled(bool light_enabled)
{
	light_enabled_ = light_enabled;
}