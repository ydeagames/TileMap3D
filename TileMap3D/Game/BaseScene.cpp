#include "pch.h"
#include "BaseScene.h"
#include "SceneCommons.h"
#include "Framework/SceneManager.h"
#include <Framework/DebugTools/DebugCameraWrapper.h>
#include <Framework/DebugTools/GridFloorWrapper.h>
#include "CubeMap.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// ê∂ê¨
void BaseScene::Build(GameContext& context)
{
	context << std::make_shared<DebugCameraWrapper>();
	//context << std::make_shared<GridFloorWrapper>();

	context.GetCamera().view = Matrix::CreateLookAt(Vector3(0, 5, 10), Vector3::Zero, Vector3::Up);

	auto tiledmap = std::make_shared<TiledMap>();
	tiledmap->Load(L"map.csv");
	auto tiledstone = std::make_shared<TiledMap>();
	tiledstone->Load(L"stone.csv");
	context << std::make_shared<CubeMap>(tiledmap, tiledstone);
}
