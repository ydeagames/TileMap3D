#include "pch.h"
#include "Othello.h"
#include <Utilities/Input.h>
#include <Utilities/Random.h>

Othello::Othello()
{
}


Othello::~Othello()
{
}


int Othello::putPiece(int x, int y, int turn, bool put_flag) {
	int sum = 0;
	if (board[y][x] > 0) return 0;
	for (int dy = -1; dy <= 1; dy++) for (int dx = -1; dx <= 1; dx++) {
		int wx[8], wy[8];
		for (int wn = 0;; wn++) {
			int kx = x + dx * (wn + 1); int ky = y + dy * (wn + 1);
			if (kx < 0 || kx > 7 || ky < 0 || ky > 7 || board[ky][kx] == 0) break;
			if (board[ky][kx] == turn) {
				if (put_flag) for (int i = 0; i < wn; i++) board[wy[i]][wx[i]] = turn;
				sum += wn;
				break;
			}
			wx[wn] = kx; wy[wn] = ky;
		}
	}
	if (sum > 0 && put_flag) board[y][x] = turn;
	return sum;
}

bool Othello::isPass(int turn) {
	for (int y = 0; y < 8; y++) for (int x = 0; x < 8; x++) {
		if (putPiece(x, y, turn, false)) return false;
	}
	return true;
}

bool Othello::think1(int turn) {
	static bool mouse_flag = false;
	if (Input::GetMouseButtonDown(Input::Buttons::MouseLeft)) {
		if (!mouse_flag) {
			mouse_flag = true;
			auto mouse = Input::GetMousePosition();
			if (putPiece(int(mouse.x) / 48, int(mouse.y) / 48, turn, true)) return true;
		}
	}
	else mouse_flag = false;
	return false;
}


bool Othello::think2(int turn) {
	int max = 0, wx, wy;
	for (int y = 0; y < 8; y++) for (int x = 0; x < 8; x++) {
		int num = putPiece(x, y, turn, false);
		if (max < num || (max == num && Random::Rand(1) == 0)) {
			max = num; wx = x; wy = y;
		}
	}
	putPiece(wx, wy, turn, true);
	return true;
}

bool Othello::think3(int turn) {
	int priority[8][8] = {
	  {0, 6, 2, 1, 1, 2, 6, 0},
	  {6, 6, 5, 4, 4, 5, 6, 6},
	  {2, 5, 2, 3, 3, 2, 5, 2},
	  {1, 4, 3, 3, 3, 3, 4, 1},
	  {1, 4, 3, 3, 3, 3, 4, 1},
	  {2, 5, 2, 3, 3, 2, 5, 2},
	  {6, 6, 5, 4, 4, 5, 6, 6},
	  {0, 6, 2, 1, 1, 2, 6, 0},
	};
	int max = 0, wx, wy;
	for (int p = 0; p <= 6 && max == 0; p++) {
		for (int y = 0; y < 8; y++) for (int x = 0; x < 8; x++) {
			if (priority[y][x] != p) continue;
			int num = putPiece(x, y, turn, false);
			if (max < num || (max == num && Random::Rand(1) == 0)) {
				max = num; wx = x; wy = y;
			}
		}
	}
	putPiece(wx, wy, turn, true);
	return true;
}

void Othello::setMsg(int turn, int type) {
	std::string turn_str[] = { "BLACK", "WHITE", "DRAW" };
	std::string type_str[] = { "TURN", "PASS", "WIN!" };
	msg = turn_str[turn - 1];
	if (turn != 3) msg += " " + type_str[type];
	msg_wait = 50;
}

int Othello::checkResult() {
	int pnum[2] = {};
	int result = 0;
	for (int y = 0; y < 8; y++) for (int x = 0; x < 8; x++) {
		if (board[y][x] > 0) pnum[board[y][x] - 1]++;
	}
	if (isPass(1) && isPass(2)) {
		if (pnum[0] > pnum[1]) result = 1;
		else if (pnum[0] < pnum[1]) result = 2;
		else result = 3;
	}
	if (result) setMsg(result, 2);
	return result;
}

void Othello::Initialize()
{
	status = 2;
	m_turn = 1;
	setMsg(m_turn, 0);
}

void Othello::Update()
{
	switch (status) {
	case 1:
		if (isPass(m_turn)) {
			setMsg(m_turn, 1);
			status = 3;
		}
		else {
			bool (Othello::*think[])(int) = { &Othello::think1, &Othello::think2 };
			if ((this->*think[m_turn - 1])(m_turn)) {
				m_turn = 3 - m_turn; status = 2;
				setMsg(m_turn, 0);
			}
		}
		if (checkResult()) status = 4;
		break;
	case 2:
		if (msg_wait > 0) msg_wait--;
		else status = 1;
		break;
	case 3:
		if (msg_wait > 0) msg_wait--;
		else {
			m_turn = 3 - m_turn; status = 2;
			setMsg(m_turn, 0);
		}
		break;
	}
}
