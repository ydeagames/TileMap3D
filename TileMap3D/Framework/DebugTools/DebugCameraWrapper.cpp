#include "pch.h"
#include "DebugCameraWrapper.h"
#include "Framework/GameContext.h"

void DebugCameraWrapper::Initialize(GameContext & context)
{
	// グリッド床作成
	m_pDebugCamera = std::make_unique<DebugCamera>();
}

void DebugCameraWrapper::Update(GameContext & context)
{
	m_pDebugCamera->update();
	context.GetCamera().view = m_pDebugCamera->getViewMatrix();
}
