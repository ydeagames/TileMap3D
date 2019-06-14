#pragma once
#include <Framework/ISceneBuilder.h>

// ゲームロジック
class TitleScene : public ISceneBuilder
{
public:
	// 生成
	void Build(GameContext& context);
};

