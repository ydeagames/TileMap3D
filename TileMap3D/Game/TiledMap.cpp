#include "pch.h"
#include "TiledMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

bool TiledMap::Load(const std::wstring& filename)
{
	int ROW = GetRow();
	int COLUMN = GetColumn();

	// 入力ストリーム
	std::ifstream wifs;
	// ストリームから入力された文字列
	std::string line;

	// マップデータをオープンする
	wifs.open(filename);
	// マップをオープンできたかどうか検証する
	if (wifs.is_open())
	{
		// 行配列を確保する
		tiledMap.resize(ROW);
		for (int row = 0; row < ROW; row++)
		{
			// 行配列を確保する
			tiledMap[row].resize(COLUMN);
		}
		// マップファイルからデータを読み込む
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COLUMN; j++)
			{
				// 区切り文字までの文字列を読み込む
				getline(wifs, line, ',');
				// 文字列をint型に変換し配列に格納する
				tiledMap[i][j] = stoi(line);
			}
		}
		// マップデータを表示する
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COLUMN; j++)
			{
				// 一行分のマップデータを表示する
				std::cout << std::setw(2) << tiledMap[i][j] << " ";
			}
			std::cout << std::endl;
		}

		// ストリームをクローズする
		wifs.close();
		return true;
	}
	return false;
}

std::vector<std::vector<int>>& TiledMap::GetData()
{
	return tiledMap;
}
