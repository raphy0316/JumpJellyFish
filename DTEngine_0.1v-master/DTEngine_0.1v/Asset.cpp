#include "pch.h"
#include "Asset.h"
#include "World.h"


Asset::Asset()
{
}

Asset::~Asset()
{
}

void Asset::Initialize()
{

}

void Asset::Dispose()
{
	for (auto iter : textures_)
		delete iter.second;
}

void Asset::Ready(string root_file_path)
{
	for (auto iter : textures_)
		delete iter.second;

	files_to_load_ = 0;
	paths_.clear();

	for (recursive_directory_iterator iter(root_file_path); iter != recursive_directory_iterator(); iter++) {
		string extension = iter->path().extension().string();
		if (extension == ".png" || extension == ".dds") {
			wstring wstr;
			wstr.assign(iter->path().string().begin(), iter->path().string().end());
			paths_.push_back(wstr);
		}
	}

	files_to_load_ = paths_.size();
	pathIter_ = paths_.begin();
}

void Asset::LoadNext()
{
	GetTexture(pathIter_->data());
	pathIter_++;
}

Texture* Asset::GetTexture(wstring p)
{
	if (!exists(p))
		cout << "파일 없음 : " << p << endl;

	if (!textures_[p]) {
		textures_[p] = new Texture();
		D3DX11CreateShaderResourceViewFromFile(
			World::GetInstance().GetD3D()->GetDevice(), p.data(), NULL, NULL, &textures_[p]->GetTexture(), NULL);
		D3DX11GetImageInfoFromFile(p.data(), NULL, &textures_[p]->GetInfo(), NULL);
		
		World::GetInstance().GetBitmap()->InitializeBuffers(textures_[p]);

		files_loaded_++;
	}

	return textures_[p];
}

int Asset::GetFilesLoaded()
{
	return files_loaded_;
}

int Asset::GetFilesToLoad()
{
	return files_to_load_;
}