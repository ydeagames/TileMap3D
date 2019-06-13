#include <Framework/GameObject.h>
#include "DebugCamera.h"

class DebugCamera;

class DebugCameraWrapper : public GameObject
{
	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_pDebugCamera;
	// 生成
	void Initialize(GameContext& context);
	// 更新
	void Update(GameContext& context);
};