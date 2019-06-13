/*
 * Copyright (c) 2002 naga3
 * https://ponk.jp/cpp/dxlib/othello
 */

#pragma once

class Othello
{
private:
	// �Ղ̃f�[�^(0:�Ȃ� 1:���R�} 2:���R�})
	int board[8][8];
	std::string msg;
	int msg_wait;
	int pieces[2];
	int back;
	// 1:�v���C�� 2:TURN���b�Z�[�W�� 3:�p�X���b�Z�[�W�� 4:�I��
	int status;
	// 1:���^�[�� 2:���^�[��
	int turn;

public:
	Othello();
	~Othello();
	int putPiece(int x, int y, int turn, bool put_flag);
	bool isPass(int turn);
	bool think1(int turn);
	bool think2(int turn);
	bool think3(int turn);
	void setMsg(int turn, int type);
	int checkResult();
	void Initialize();
	void Update();
};

