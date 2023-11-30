#include "pch.h"
#include "Texture.h"


Texture::Texture() : texture_(nullptr)
{
}


Texture::~Texture()
{
	texture_->Release();
	vertex_buffer_->Release();
	index_buffer_->Release();
}

ID3D11ShaderResourceView*& Texture::GetTexture()
{
	return texture_;
}

D3DX11_IMAGE_INFO& Texture::GetInfo()
{
	return info_;
}

ID3D11Buffer*& Texture::GetVertexBuffer()
{
	return vertex_buffer_;
}

void Texture::SetVertexBuffer(ID3D11Buffer* vertex_buffer)
{
	vertex_buffer_ = vertex_buffer;
}

ID3D11Buffer*& Texture::GetIndexBuffer()
{
	return index_buffer_;
}

void Texture::SetIndexBuffer(ID3D11Buffer* index_buffer)
{
	index_buffer_ = index_buffer;
}

int Texture::GetVertexCount()
{
	return vertex_count_;
}

void Texture::SetVertexCount(int vertex_count)
{
	vertex_count_ = vertex_count;
}

int Texture::GetIndexCount()
{
	return index_count_;
}

void Texture::SetIndexCount(int index_count)
{
	index_count_ = index_count;
}

D3DXMATRIX Texture::GetPreviousMatrix()
{
	return previous_matrix_;
}

void Texture::SetPreviousMatrix(D3DXMATRIX previous_matrix)
{
	previous_matrix_ = previous_matrix;
}