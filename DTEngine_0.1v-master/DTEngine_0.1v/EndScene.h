#pragma once
#include "Scene.h"
#include "Sprite.h";
class EndScene :
	public Scene
{
public:
	EndScene();
	~EndScene();
	Sprite* endSceneimg;
};

