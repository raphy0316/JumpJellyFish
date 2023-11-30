#include "pch.h"
#include "Animation.h"
#include "Asset.h"


Animation::Animation(const wstring& path, int frame_num, float fps, bool loop)
	:current_frame_(0), fps_(fps), loop_(loop)
{
	for (int i = 0; i <= frame_num; i++) {
		Texture* t = Asset::GetInstance().GetTexture(path + L"/" + to_wstring(i) + L".png");
		textures_.push_back(t);
	}
	SetTexture(textures_[0]);
	SetRect(Rect(0, 0, GetTexture()->GetInfo().Width, GetTexture()->GetInfo().Height));
}


Animation::~Animation()
{
}

void Animation::Update(float dt)
{
	Sprite::Update(dt);

	current_frame_ += fps_ * dt;

	if (int(current_frame_) >= textures_.size()) {
		if (loop_)
			current_frame_ = 0;
		else
			current_frame_ = textures_.size() - 1;
	}

	SetTexture(textures_[int(current_frame_)]);
}