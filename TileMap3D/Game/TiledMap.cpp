#include "pch.h"
#include "TiledMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <istream>

bool TiledMap::Load(const std::wstring& filename)
{
	tiledMap.clear();

	std::ifstream ifs;
	std::string line;
	ifs.open(filename);
	if (ifs.is_open())
	{
		while (getline(ifs, line))
		{
			std::string token;
			std::istringstream stream(line);
			std::vector<int> tileLine;
			while (getline(stream, token, ','))
			{
				tileLine.push_back(atoi(token.c_str()));
			}
			tiledMap.push_back(tileLine);
		}
		return true;
	}
	return false;
}

std::vector<std::vector<int>>& TiledMap::GetData()
{
	return tiledMap;
}

int TiledMap::GetRow()
{
	return tiledMap.size();
}

int TiledMap::GetColumn()
{
	return tiledMap[0].size();
}
