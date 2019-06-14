#pragma once
#include <Framework/ISceneBuilder.h>

// ゲームロジック
class ResultScene : public ISceneBuilder
{
public:
	// 生成
	void Build(GameContext& context);
};

