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

	// ���̓X�g���[��
	std::ifstream wifs;
	// �X�g���[��������͂��ꂽ������
	std::string line;

	// �}�b�v�f�[�^���I�[�v������
	wifs.open(filename);
	// �}�b�v���I�[�v���ł������ǂ������؂���
	if (wifs.is_open())
	{
		// �s�z����m�ۂ���
		tiledMap.resize(ROW);
		for (int row = 0; row < ROW; row++)
		{
			// �s�z����m�ۂ���
			tiledMap[row].resize(COLUMN);
		}
		// �}�b�v�t�@�C������f�[�^��ǂݍ���
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COLUMN; j++)
			{
				// ��؂蕶���܂ł̕������ǂݍ���
				getline(wifs, line, ',');
				// �������int�^�ɕϊ����z��Ɋi�[����
				tiledMap[i][j] = stoi(line);
			}
		}
		// �}�b�v�f�[�^��\������
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COLUMN; j++)
			{
				// ��s���̃}�b�v�f�[�^��\������
				std::cout << std::setw(2) << tiledMap[i][j] << " ";
			}
			std::cout << std::endl;
		}

		// �X�g���[�����N���[�Y����
		wifs.close();
		return true;
	}
	return false;
}

std::vector<std::vector<int>>& TiledMap::GetData()
{
	return tiledMap;
}
