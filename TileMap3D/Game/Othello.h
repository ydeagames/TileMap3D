/*
 * Copyright (c) 2002 naga3
 * https://ponk.jp/cpp/dxlib/othello
 */

#pragma once

class Othello
{
private:
	// 盤のデータ(0:なし 1:黒コマ 2:白コマ)
	int board[8][8];
	std::string msg;
	int msg_wait;
	int pieces[2];
	int back;
	// 1:プレイ中 2:TURNメッセージ中 3:パスメッセージ中 4:終了
	int status;
	// 1:黒ターン 2:白ターン
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

