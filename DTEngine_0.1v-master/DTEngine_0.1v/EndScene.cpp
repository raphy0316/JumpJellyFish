#include "pch.h"
#include "EndScene.h"


EndScene::EndScene()
{
	endSceneimg = new Sprite(L"../Resource/game_over.jpg");
	AddChild(endSceneimg);
}


EndScene::~EndScene()
{
}
