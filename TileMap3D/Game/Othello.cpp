#include "pch.h"
#include "Othello.h"
#include <Utilities/Input.h>
#include <Utilities/Random.h>

Othello::Othello(TiledMap* board)
	: m_board(board)
	, m_think{ &Othello::think1, &Othello::think3 }
{
}


Othello::~Othello()
{
}


int Othello::putPiece(const StonePosition& pos, int turn, bool put_flag) {
	auto& board = m_board->GetData();
	int sum = 0;
	if (board[pos.y][pos.x] > 0) return 0;
	for (int dy = -1; dy <= 1; dy++) for (int dx = -1; dx <= 1; dx++) {
		int wx[8], wy[8];
		for (int wn = 0;; wn++) {
			int kx = pos.x + dx * (wn + 1); int ky = pos.y + dy * (wn + 1);
			if (kx < 0 || kx > 7 || ky < 0 || ky > 7 || board[ky][kx] == 0) break;
			if (board[ky][kx] == turn) {
				if (put_flag) for (int i = 0; i < wn; i++) board[wy[i]][wx[i]] = turn;
				sum += wn;
				break;
			}
			wx[wn] = kx; wy[wn] = ky;
		}
	}
	if (sum > 0 && put_flag)
		board[pos.y][pos.x] = turn;
	return sum;
}

bool Othello::isPass(int turn) {
	for (int y = 0; y < 8; y++) for (int x = 0; x < 8; x++) {
		if (putPiece(StonePosition{ x, y }, turn, false)) return false;
	}
	return true;
}

bool Othello::think1(int turn) {
	if (m_next)
	{
		if (putPiece(*m_next, turn, true))
		{
			m_next = nullptr;
			return true;
		}
	}
	return false;
}


bool Othello::think2(int turn) {
	int max = 0, wx = 0, wy = 0;
	for (int y = 0; y < 8; y++) for (int x = 0; x < 8; x++) {
		int num = putPiece(StonePosition{ x, y }, turn, false);
		if (max < num || (max == num && Random::Rand(1) == 0)) {
			max = num; wx = x; wy = y;
		}
	}
	putPiece(StonePosition{ wx, wy }, turn, true);
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
	int max = 0, wx = 0, wy = 0;
	for (int p = 0; p <= 6 && max == 0; p++) {
		for (int y = 0; y < 8; y++) for (int x = 0; x < 8; x++) {
			if (priority[y][x] != p) continue;
			int num = putPiece(StonePosition{ x, y }, turn, false);
			if (max < num || (max == num && Random::Rand(1) == 0)) {
				max = num; wx = x; wy = y;
			}
		}
	}
	putPiece(StonePosition{ wx, wy }, turn, true);
	return true;
}

void Othello::setMsg(int turn, int type) {
	std::wstring turn_str[] = { L"BLACK", L"WHITE", L"DRAW" };
	std::wstring type_str[] = { L"TURN", L"PASS", L"WIN!" };
	msg = turn_str[turn - 1];
	if (turn != 3) msg += L" " + type_str[type];
	msg_wait = 50;
}

int Othello::checkResult() {
	auto& board = m_board->GetData();
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
			if ((this->*m_think[m_turn - 1])(m_turn)) {
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
