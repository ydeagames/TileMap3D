#pragma once
#include <Framework/ISceneBuilder.h>

// ゲームロジック
class ResultScene : public ISceneBuilder
{
public:
	static int score_white;
	static int score_black;

public:
	// 生成
	void Build(GameContext& context);
};

