#include "pch.h"
#include "World.h"
#include "Asset.h"
#include "System.h"
#include "GameScene.h"


World::World()
{
}


World::~World()
{
}

void World::Initialize(int screenWidth, int screenHeight)
{
	Asset::GetInstance().Initialize();
	cout.precision(3);
	ZeroMemory(current_keys_, sizeof(current_keys_));
	ZeroMemory(last_keys_, sizeof(last_keys_));
	start_clock_ = current_clock_ = last_clock_ = clock();
	d3d_ = new D3D();
	bitmap_ = new Bitmap();
	texture_shader_ = new TextureShader();
	light_shader_ = new LightShader();
	ChangeScene(new GameScene());
}

void World::Dispose()
{
	Asset::GetInstance().Dispose();
	if (current_scene_)
		delete current_scene_;

	delete d3d_;
	delete bitmap_;
	delete texture_shader_;
	delete light_shader_;
}

void World::Render()
{
	D3DXMATRIX world_matrix, view_matrix, projection_matrix, ortho_matrix;

	d3d_->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	current_scene_->GetCamera()->Render();

	//view_matrix = current_scene_->GetCamera()->GetViewMatrix();
	//world_matrix = d3d_->GetWorldMatrix();
	//projection_matrix = d3d_->GetProjectionMatrix();
	//ortho_matrix = d3d_->GetOrthoMatrix();

	d3d_->TurnZBufferOff();
	current_scene_->Render();
	d3d_->TurnZBufferOn();
	d3d_->EndScene();
}

void World::Update()
{
	last_clock_ = current_clock_;
	current_clock_ = clock();
	dt_ = (float)(current_clock_ - last_clock_) / CLOCKS_PER_SEC;

	for (int i = 0; i < 256; i++) {
		last_keys_[i] = current_keys_[i];
		current_keys_[i] = GetAsyncKeyState(i) & 0x8000;
	}

	GetCursorPos(&mouse_pos_);
	ScreenToClient(application_handle_->GetHwnd(), &mouse_pos_);

	for (auto* timer : timers_)
		if(timer->GetIsActive())
			timer->Update(dt_);

	if (current_scene_)
		current_scene_->Update(dt_);
}

void World::ChangeScene(Scene* scene)
{
	if (current_scene_) delete current_scene_;
	current_scene_ = scene;
}

int World::GetKeyState(int vk)
{
	if (current_keys_[vk] && last_keys_[vk]) return 2;
	if (current_keys_[vk] && !last_keys_[vk]) return 1;
	if (!current_keys_[vk] && last_keys_[vk]) return -1;
	return -2;
}

D3DXVECTOR2 World::GetMousePos()
{
	return D3DXVECTOR2(mouse_pos_.x, mouse_pos_.y) + current_scene_->Center();
}

void World::RenderTextureShader(D3DXMATRIX world_matrix, int index_count, ID3D11ShaderResourceView* texture)
{
	texture_shader_->Render(index_count, world_matrix, current_scene_->GetCamera()->GetViewMatrix(), d3d_->GetOrthoMatrix(), texture);
}

void World::RenderLightShader(D3DXMATRIX world_matrix, int index_count, ID3D11ShaderResourceView* texture)
{
	light_shader_->Render(index_count, world_matrix, current_scene_->GetCamera()->GetViewMatrix(), d3d_->GetOrthoMatrix(), texture, 
		current_scene_->GetLight()->GetDirection(), current_scene_->GetLight()->GetAmbientColor(), current_scene_->GetLight()->GetDiffuseColor());
}

Scene* World::GetCurrentScene()
{
	return current_scene_;
}

D3D* World::GetD3D()
{
	return d3d_;
}

vector<Timer*>* World::GetTimers()
{
	return &timers_;
}

Bitmap* World::GetBitmap()
{
	return bitmap_;
}

TextureShader* World::GetTextureShader()
{
	return texture_shader_;
}