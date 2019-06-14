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
	// 盤のデータ(0:なし 1:黒コマ 2:白コマ)
	TiledMap* m_board;
	std::string msg;
	int msg_wait;
	int pieces[2];
	int back;
	// 1:プレイ中 2:TURNメッセージ中 3:パスメッセージ中 4:終了
	int status;
	// 1:黒ターン 2:白ターン
	// 次の手
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

