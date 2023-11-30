#pragma once
#include "Define.h"

class Texture
{
public:
	Texture();
	~Texture();

	ID3D11ShaderResourceView*& GetTexture();
	D3DX11_IMAGE_INFO& GetInfo();
	
	ID3D11Buffer*& GetVertexBuffer();
	void SetVertexBuffer(ID3D11Buffer* vertex_buffer);

	ID3D11Buffer*& GetIndexBuffer();
	void SetIndexBuffer(ID3D11Buffer* index_buffer);

	int GetVertexCount();
	void SetVertexCount(int vertex_count);

	int GetIndexCount();
	void SetIndexCount(int index_count);

	D3DXMATRIX GetPreviousMatrix();
	void SetPreviousMatrix(D3DXMATRIX matrix);

private:
	ID3D11ShaderResourceView* texture_;
	D3DX11_IMAGE_INFO info_;

	ID3D11Buffer* vertex_buffer_, *index_buffer_;
	int vertex_count_, index_count_;
	D3DXMATRIX previous_matrix_;
};

