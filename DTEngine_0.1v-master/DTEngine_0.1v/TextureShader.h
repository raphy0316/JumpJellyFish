#pragma once
#include "Define.h"

class TextureShader
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

public:
	TextureShader();
	~TextureShader();

	void Render(int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);

private:
	void InitializeShader(WCHAR*, WCHAR*);
	void OutputShaderErrorMessage(ID3D10Blob*, WCHAR*);

	void SetShaderParameters(D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);
	void RenderShader(int);

private:
	ID3D11VertexShader * vertex_shader_;
	ID3D11PixelShader* pixel_shader_;
	ID3D11InputLayout* layout_;
	ID3D11Buffer* matrix_buffer_;

	ID3D11SamplerState* sampler_state_;
};

