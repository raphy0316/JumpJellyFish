#pragma once
#include "Define.h"
#include "Singleton.h"
#include "Texture.h"

class Asset :
	public Singleton<Asset>
{
public:
	Asset();
	~Asset();

	void Initialize();
	void Dispose();
	void Ready(string root_file_path);
	void LoadNext();

	Texture* GetTexture(wstring p);

	int GetFilesToLoad();
	int GetFilesLoaded();

private:
	map<wstring, Texture*> textures_;

	vector<wstring> paths_;
	vector<wstring>::iterator pathIter_;

	int files_to_load_;
	int files_loaded_;
};

