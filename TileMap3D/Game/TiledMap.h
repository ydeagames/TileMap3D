#pragma once

class TiledMap
{
private:
	// �^�C���h�}�b�v
	std::vector<std::vector<int>> tiledMap;

public:
	bool Load(const std::wstring& filename);
	std::vector<std::vector<int>>& GetData();
	int GetRow();
	int GetColumn();
};

