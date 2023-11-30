#pragma once
#include "Sprite.h"

class Animation :
	public Sprite
{
public:
	Animation(const wstring& path, int frame_num, float fps = 20, bool loop = true);
	~Animation();

	void Update(float dt);

private:
	vector<Texture*> textures_;
	float current_frame_;
	float fps_;
	float loop_;
};

