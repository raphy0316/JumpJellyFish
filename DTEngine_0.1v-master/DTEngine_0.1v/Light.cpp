#include "pch.h"
#include "Light.h"


Light::Light()
{
}


Light::~Light()
{
}

void Light::SetAmbientColor(float red, float green, float blue, float alpha)
{
	ambient_color_ = D3DXVECTOR4(red, green, blue, alpha);
}

void Light::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	diffuse_color_ = D3DXVECTOR4(red, green, blue, alpha);
}

void Light::SetDirection(float x, float y, float z)
{
	direction_ = D3DXVECTOR3(x, y, z);
}

D3DXVECTOR4 Light::GetAmbientColor()
{
	return ambient_color_;
}

D3DXVECTOR4 Light::GetDiffuseColor()
{
	return diffuse_color_;
}

D3DXVECTOR3 Light::GetDirection()
{
	return direction_;
}