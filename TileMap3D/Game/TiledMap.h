#pragma once

class TiledMap
{
private:
	// タイルドマップ
	std::vector<std::vector<int>> tiledMap;

public:
	bool Load(const std::wstring& filename);
	std::vector<std::vector<int>>& GetData();
	int GetRow();
	int GetColumn();
};

