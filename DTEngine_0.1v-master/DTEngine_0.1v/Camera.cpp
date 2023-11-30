#include "pch.h"
#include "Camera.h"


Camera::Camera()
{
	position_x_ = 0.0f;
	position_y_ = 0.0f;
	position_z_ = 0.0f;

	rotation_x_ = 0.0f;
	rotation_y_ = 0.0f;
	rotation_z_ = 0.0f;
}


Camera::~Camera()
{
}

void Camera::SetPosition(float x, float y, float z)
{
	position_x_ = x;
	position_y_ = y;
	position_z_ = z;
}

void Camera::SetRotation(float x, float y, float z)
{
	rotation_x_ = x;
	rotation_y_ = y;
	rotation_z_ = z;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return D3DXVECTOR3(position_x_, position_y_, position_z_);
}

D3DXVECTOR3 Camera::GetRotation()
{
	return D3DXVECTOR3(rotation_x_, rotation_y_, rotation_z_);
}

void Camera::Render()
{
	D3DXVECTOR3 up, position, look_at;
	float yaw, pitch, roll;
	D3DXMATRIX rotation_matrix;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	position.x = position_x_;
	position.y = position_y_;
	position.z = position_z_;

	look_at.x = 0.0f;
	look_at.y = 0.0f;
	look_at.z = 1.0f;

	pitch = rotation_x_ * 0.0174532925f;
	yaw   = rotation_y_ * 0.0174532925f;
	roll  = rotation_z_ * 0.0174532925f;

	D3DXMatrixRotationYawPitchRoll(&rotation_matrix, yaw, pitch, roll);

	D3DXVec3TransformCoord(&look_at, &look_at, &rotation_matrix);
	D3DXVec3TransformCoord(&up, &up, &rotation_matrix);

	look_at = position + look_at;

	D3DXMatrixLookAtLH(&view_matrix_, &position, &look_at, &up);
}

D3DXMATRIX Camera::GetViewMatrix()
{
	return view_matrix_;
}