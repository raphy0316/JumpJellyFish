#pragma once
#include "Define.h"
#include "Sprite.h"

class Bitmap
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};
public:
	Bitmap();
	~Bitmap();

	void InitializeBuffers(Texture* texture);
	void Render(Sprite* sprite);

private:
	void UpdateBuffers(Sprite* sprite);
	void RenderBuffers(Texture* texture);
};

