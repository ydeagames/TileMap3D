#pragma once

// ���ʃC���N���[�h
#include "GameContext.h"
#include "GameObject.h"
#include "GameCamera.h"

class ISceneBuilder
{
public:
	virtual ~ISceneBuilder() = default;
	virtual void Build(GameContext& context) = 0;
};

