#pragma once
#include <Framework/ISceneBuilder.h>

class BuildSettings : public ISceneBuilder
{
public:
	void Build(GameContext& context) override;
};

