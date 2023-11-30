#include "pch.h"
#include "LightShader.h"
#include "World.h"
#include "System.h"


LightShader::LightShader() : vertex_shader_(nullptr),
pixel_shader_(nullptr), layout_(nullptr), sampler_state_(nullptr),
matrix_buffer_(nullptr), light_buffer_(nullptr)
{
	InitializeShader(const_cast<WCHAR*>(L"../Shader/light.vs"), const_cast<WCHAR*>(L"../Shader/light.ps"));
}


LightShader::~LightShader()
{
	light_buffer_->Release();
	matrix_buffer_->Release();
	sampler_state_->Release();
	layout_->Release();
	pixel_shader_->Release();
	vertex_shader_->Release();
}

void LightShader::Render(int index_context, D3DXMATRIX world_matrix, D3DXMATRIX view_matrix,
	D3DXMATRIX projection_matrix, ID3D11ShaderResourceView* texture, D3DXVECTOR3 light_direction,
	D3DXVECTOR4 ambient_color, D3DXVECTOR4 diffuse_color)
{
	SetShaderParameters(world_matrix, view_matrix, projection_matrix, texture, light_direction, ambient_color, diffuse_color);
	RenderShader(index_context);
}

void LightShader::InitializeShader(WCHAR* vs_filename, WCHAR* ps_filename)
{
	HRESULT result;
	ID3D10Blob* error_message;
	ID3D10Blob* vertex_shader_buffer;
	ID3D10Blob* pixel_shader_buffer;
	D3D11_INPUT_ELEMENT_DESC polygon_layout[3];
	unsigned int num_elements;
	D3D11_SAMPLER_DESC sampler_desc;
	D3D11_BUFFER_DESC matrix_buffer_desc;
	D3D11_BUFFER_DESC light_buffer_desc;

	error_message = nullptr;
	vertex_shader_buffer = nullptr;
	pixel_shader_buffer = nullptr;

	result = D3DX11CompileFromFile(vs_filename, NULL, NULL, "LightVertexShader", "vs_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertex_shader_buffer, &error_message, NULL);

	if (FAILED(result)) {
		if (error_message) {
			OutputShaderErrorMessage(error_message, vs_filename);
		}
		else {
			MessageBox(application_handle_->GetHwnd(), vs_filename, L"Missing Shader File", MB_OK);
		}

		return;
	}

	result = D3DX11CompileFromFile(ps_filename, NULL, NULL, "LightPixelShader", "ps_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixel_shader_buffer, &error_message, NULL);

	if (FAILED(result)) {
		if (error_message) {
			OutputShaderErrorMessage(error_message, ps_filename);
		}
		else {
			MessageBox(application_handle_->GetHwnd(), ps_filename, L"Missing Shader File", MB_OK);
		}
	}

	ID3D11Device* device = World::GetInstance().GetD3D()->GetDevice();
	
	result = device->CreateVertexShader(vertex_shader_buffer->GetBufferPointer(), vertex_shader_buffer->GetBufferSize(), NULL, &vertex_shader_);
	if (FAILED(result)) {
		return;
	}

	result = device->CreatePixelShader(pixel_shader_buffer->GetBufferPointer(), pixel_shader_buffer->GetBufferSize(), NULL, &pixel_shader_);
	if (FAILED(result)) {
		return;
	}

	polygon_layout[0].SemanticName = "POSITION";
	polygon_layout[0].SemanticIndex = 0;
	polygon_layout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygon_layout[0].InputSlot = 0;
	polygon_layout[0].AlignedByteOffset = 0;
	polygon_layout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygon_layout[0].InstanceDataStepRate = 0;

	polygon_layout[1].SemanticName = "TEXCOORD";
	polygon_layout[1].SemanticIndex = 0;
	polygon_layout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygon_layout[1].InputSlot = 0;
	polygon_layout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygon_layout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygon_layout[1].InstanceDataStepRate = 0;

	polygon_layout[2].SemanticName = "NORMAL";
	polygon_layout[2].SemanticIndex = 0;
	polygon_layout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygon_layout[2].InputSlot = 0;
	polygon_layout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygon_layout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygon_layout[2].InstanceDataStepRate = 0;

	num_elements = sizeof(polygon_layout) / sizeof(polygon_layout[0]);

	result = device->CreateInputLayout(polygon_layout, num_elements, vertex_shader_buffer->GetBufferPointer(), vertex_shader_buffer->GetBufferSize(), &layout_);

	if (FAILED(result)) {
		return;
	}

	vertex_shader_buffer->Release();
	vertex_shader_buffer = nullptr;

	pixel_shader_buffer->Release();
	pixel_shader_buffer = nullptr;

	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MipLODBias = 0.0f;
	sampler_desc.MaxAnisotropy = 1;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampler_desc.BorderColor[0] = 0;
	sampler_desc.BorderColor[1] = 0;
	sampler_desc.BorderColor[2] = 0;
	sampler_desc.BorderColor[3] = 0;
	sampler_desc.MinLOD = 0;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	result = device->CreateSamplerState(&sampler_desc, &sampler_state_);
	if (FAILED(result)) {
		return;
	}

	matrix_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	matrix_buffer_desc.ByteWidth = sizeof(MatrixBufferType);
	matrix_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrix_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrix_buffer_desc.MiscFlags = 0;
	matrix_buffer_desc.StructureByteStride = 0;

	result = device->CreateBuffer(&matrix_buffer_desc, NULL, &matrix_buffer_);
	if (FAILED(result)) {
		return;
	}

	light_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	light_buffer_desc.ByteWidth = sizeof(LightBufferType);
	light_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	light_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	light_buffer_desc.MiscFlags = 0;
	light_buffer_desc.StructureByteStride = 0;

	result = device->CreateBuffer(&light_buffer_desc, NULL, &light_buffer_);
	if (FAILED(result)) {
		return;
	}
}

void LightShader::OutputShaderErrorMessage(ID3D10Blob* error_message, WCHAR* shader_filename)
{
	char* compile_errors;
	unsigned long buffer_size, i;
	ofstream fout;

	compile_errors = (char*)(error_message->GetBufferPointer());

	buffer_size = error_message->GetBufferSize();

	fout.open("shader-error.txt");

	for (i = 0; i < buffer_size; i++) {
		fout << compile_errors[i];
	}

	fout.close();

	error_message->Release();
	error_message = nullptr;

	MessageBox(application_handle_->GetHwnd(), L"Error compiling shader. Check shader-error.txt for message.", shader_filename, MB_OK);
}

void LightShader::SetShaderParameters(D3DXMATRIX world_matrix, D3DXMATRIX view_matrix, D3DXMATRIX projection_matrix,
	ID3D11ShaderResourceView* texture, D3DXVECTOR3 light_direction, D3DXVECTOR4 ambient_color, D3DXVECTOR4 diffuse_color)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	unsigned int buffer_number;
	MatrixBufferType* data_ptr;
	LightBufferType* data_ptr2;

	D3DXMatrixTranspose(&world_matrix, &world_matrix);
	D3DXMatrixTranspose(&view_matrix, &view_matrix);
	D3DXMatrixTranspose(&projection_matrix, &projection_matrix);

	ID3D11DeviceContext* device_context = World::GetInstance().GetD3D()->GetDeviceContext();

	result = device_context->Map(matrix_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
	if (FAILED(result)) {
		return;
	}

	data_ptr = (MatrixBufferType*)mapped_resource.pData;
	data_ptr->world = world_matrix;
	data_ptr->view = view_matrix;
	data_ptr->projection = projection_matrix;
	device_context->Unmap(matrix_buffer_, 0);

	buffer_number = 0;

	device_context->VSSetConstantBuffers(buffer_number, 1, &matrix_buffer_);
	device_context->PSSetShaderResources(0, 1, &texture);

	device_context->Map(light_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
	if (FAILED(result)) {
		return;
	}

	data_ptr2 = (LightBufferType*)mapped_resource.pData;
	data_ptr2->ambientColor = ambient_color;
	data_ptr2->diffuseColor = diffuse_color;
	data_ptr2->lightDirection = light_direction;
	data_ptr2->padding = 0.0f;

	device_context->Unmap(light_buffer_, 0);
	buffer_number = 0;
	device_context->PSSetConstantBuffers(buffer_number, 1, &light_buffer_);
}

void LightShader::RenderShader(int index_count)
{
	ID3D11DeviceContext* device_context = World::GetInstance().GetD3D()->GetDeviceContext();

	device_context->IASetInputLayout(layout_);

	device_context->VSSetShader(vertex_shader_, NULL, 0);
	device_context->PSSetShader(pixel_shader_, NULL, 0);

	device_context->PSSetSamplers(0, 1, &sampler_state_);
	device_context->DrawIndexed(index_count, 0, 0);
}