#pragma once
#include <Framework/ISceneBuilder.h>

// �Q�[�����W�b�N
class ResultScene : public ISceneBuilder
{
public:
	static int score_white;
	static int score_black;

public:
	// ����
	void Build(GameContext& context);
};

