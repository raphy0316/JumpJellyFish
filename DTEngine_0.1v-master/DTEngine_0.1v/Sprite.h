#pragma once
#include "Entity.h"
#include "Texture.h"

class Sprite :
	public Entity
{
public:
	Sprite();
	Sprite(wstring path);
	~Sprite();

	void SetPath(wstring path);
	void Render();

	Texture* GetTexture();
	void SetTexture(Texture* texture);

	bool GetLightEnabled();
	void SetLightEnabled(bool enable_light);

private:
	Texture* texture_;
	bool light_enabled_;
};

