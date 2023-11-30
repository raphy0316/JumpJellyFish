#include "pch.h"
#include "Bitmap.h"
#include "World.h"
#include "Asset.h"


Bitmap::Bitmap()
{
}


Bitmap::~Bitmap()
{
}

void Bitmap::Render(Sprite* sprite)
{
	UpdateBuffers(sprite);
	RenderBuffers(sprite->GetTexture());
}

void Bitmap::InitializeBuffers(Texture* texture)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertex_buffer_desc, index_buffer_desc;
	D3D11_SUBRESOURCE_DATA vertex_data, index_data;
	HRESULT result;

	texture->SetVertexCount(6);
	texture->SetIndexCount(texture->GetVertexCount());

	vertices = new VertexType[texture->GetVertexCount()];
	indices = new unsigned long[texture->GetIndexCount()];

	memset(vertices, 0, (sizeof(VertexType) * texture->GetVertexCount()));

	for (int i = 0; i < texture->GetIndexCount(); i++) {
		indices[i] = i;
	}

	vertex_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	vertex_buffer_desc.ByteWidth = sizeof(VertexType) * texture->GetVertexCount();
	vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertex_buffer_desc.MiscFlags = 0;
	vertex_buffer_desc.StructureByteStride = 0;

	vertex_data.pSysMem = vertices;
	vertex_data.SysMemPitch = 0;
	vertex_data.SysMemSlicePitch = 0;

	ID3D11Device* device = World::GetInstance().GetD3D()->GetDevice();
	device->CreateBuffer(&vertex_buffer_desc, &vertex_data, &texture->GetVertexBuffer());

	index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	index_buffer_desc.ByteWidth = sizeof(unsigned long) * texture->GetIndexCount();
	index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	index_buffer_desc.CPUAccessFlags = 0;
	index_buffer_desc.MiscFlags = 0;
	index_buffer_desc.StructureByteStride = 0;

	index_data.pSysMem = indices;
	index_data.SysMemPitch = 0;
	index_data.SysMemSlicePitch = 0;

	device->CreateBuffer(&index_buffer_desc, &index_data, &texture->GetIndexBuffer());

	delete[] vertices;

	delete[] indices;
}

void Bitmap::UpdateBuffers(Sprite* sprite)
{
	float halfWidth, halfHeight;
	float left, right, top, bottom;
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	VertexType* vertices_ptr;

	//if ((position_x == previous_pos_x_) && (position_y == previous_pos_y_)) {
	//	return;
	//}

	//previous_pos_x_ = position_x;
	//previous_pos_y_ = position_y;

	halfWidth = static_cast<float>(sprite->GetRect().Width()) * 0.5f;
	halfHeight = static_cast<float>(sprite->GetRect().Height()) * 0.5f;

	left = (float)((kScreenWidth / 2) * -1) + sprite->GetPosition().x;
	right = left + (float)sprite->GetRect().Width();
	top = (float)(kScreenHeight / 2) - sprite->GetPosition().y;
	bottom = top - (float)sprite->GetRect().Height();

	vertices = new VertexType[sprite->GetTexture()->GetVertexCount()];

	/*vertices[0].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[1].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[1].texture = D3DXVECTOR2(1.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(left, bottom, 0.0f);
	vertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[3].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[4].position = D3DXVECTOR3(right, top, 0.0f);
	vertices[4].texture = D3DXVECTOR2(1.0f, 0.0f);

	vertices[5].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[5].texture = D3DXVECTOR2(1.0f, 1.0f);*/

	vertices[0].position = D3DXVECTOR3(-halfWidth, halfHeight, 0.0f);
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);
	vertices[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[1].position = D3DXVECTOR3(halfWidth, -halfHeight, 0.0f);
	vertices[1].texture = D3DXVECTOR2(1.0f, 1.0f);
	vertices[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[2].position = D3DXVECTOR3(-halfWidth, -halfHeight, 0.0f);
	vertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);
	vertices[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[3].position = D3DXVECTOR3(-halfWidth, halfHeight, 0.0f);
	vertices[3].texture = D3DXVECTOR2(0.0f, 0.0f);
	vertices[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[4].position = D3DXVECTOR3(halfWidth, halfHeight, 0.0f);
	vertices[4].texture = D3DXVECTOR2(1.0f, 0.0f);
	vertices[4].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[5].position = D3DXVECTOR3(halfWidth, -halfHeight, 0.0f);
	vertices[5].texture = D3DXVECTOR2(1.0f, 1.0f);
	vertices[5].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	ID3D11DeviceContext* device_context = World::GetInstance().GetD3D()->GetDeviceContext();
	device_context->Map(sprite->GetTexture()->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);

	vertices_ptr = (VertexType*)mapped_resource.pData;
	memcpy(vertices_ptr, (void*)vertices, (sizeof(VertexType) * sprite->GetTexture()->GetVertexCount()));
	device_context->Unmap(sprite->GetTexture()->GetVertexBuffer(), 0);

	delete[] vertices;

	return;
}

void Bitmap::RenderBuffers(Texture* texture)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	ID3D11DeviceContext* device_context = World::GetInstance().GetD3D()->GetDeviceContext();
	device_context->IASetVertexBuffers(0, 1, &texture->GetVertexBuffer(), &stride, &offset);
	device_context->IASetIndexBuffer(texture->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}