#pragma once
#include "Define.h"

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render();

	D3DXMATRIX GetViewMatrix();

private:
	float position_x_, position_y_, position_z_;
	float rotation_x_, rotation_y_, rotation_z_;
	D3DXMATRIX view_matrix_;
};

