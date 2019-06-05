#pragma once

class TiledMap
{
private:
	// タイルドマップ
	std::vector<std::vector<int>> tiledMap;

public:
	bool Load(const std::wstring& filename);
	std::vector<std::vector<int>>& GetData();
	int GetRow() { return 10; }
	int GetColumn() { return 10; }
};

