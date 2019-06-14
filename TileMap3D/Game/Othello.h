/*
 * Copyright (c) 2002 naga3
 * https://ponk.jp/cpp/dxlib/othello
 */

#pragma once
#include "TiledMap.h"
#include <Utilities/Optional.h>

class Othello
{
public:
	struct StonePosition
	{
		int x, y;
	};

private:
	// �Ղ̃f�[�^(0:�Ȃ� 1:���R�} 2:���R�})
	TiledMap* m_board;
	std::string msg;
	int msg_wait;
	int pieces[2];
	int back;
	// 1:�v���C�� 2:TURN���b�Z�[�W�� 3:�p�X���b�Z�[�W�� 4:�I��
	int status;
	// 1:���^�[�� 2:���^�[��
	// ���̎�
	Optional<StonePosition> m_next;

public:
	int m_turn;

public:
	Othello(TiledMap* board);
	~Othello();
	void Place(const StonePosition& pos) { m_next = pos; }
	int putPiece(const StonePosition& pos, int turn, bool put_flag);
	bool isPass(int turn);
	bool think1(int turn);
	bool think2(int turn);
	bool think3(int turn);
	void setMsg(int turn, int type);
	int checkResult();
	void Initialize();
	void Update();
};

