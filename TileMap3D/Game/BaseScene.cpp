#include "pch.h"
#include "BaseScene.h"
#include "SceneCommons.h"
#include <Framework/SceneManager.h>
#include <Framework/DebugTools/DebugCameraWrapper.h>
#include <Framework/DebugTools/GridFloorWrapper.h>
#include "CubeMap.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 生成
void BaseScene::Build(GameContext& context)
{
	context << std::make_shared<DebugCameraWrapper>();
	context << std::make_shared<GridFloorWrapper>();

	context.GetCamera().view = Matrix::CreateLookAt(Vector3(0, 5, 10), Vector3::Zero, Vector3::Up);

	auto tiledmap = std::make_shared<TiledMap>();
	tiledmap->Load(L"map.csv");
	auto tiledstone = std::make_shared<TiledMap>();
	tiledstone->Load(L"stone.csv");
	//context << std::make_shared<CubeMap>(tiledmap, tiledstone);

	// レイのテスト
	struct RayTest : public GameObject
	{
		std::unique_ptr<PrimitiveBatch<VertexPositionColor>> m_batch;
		Ray m_ray;

		void Initialize(GameContext& ctx)
		{
			m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(ctx.GetDR().GetD3DDeviceContext());
		}

		void Update(GameContext& ctx)
		{
			if (Keyboard::Get().GetState().IsKeyDown(Keyboard::Space))
			{
				auto mouse = Mouse::Get().GetState();
				auto point = Vector2(float(mouse.x), float(mouse.y));
				m_ray = ctx.GetCamera().ScreenPointToRay(Vector3(point));
			}
		}

		void Render(GameContext& ctx)
		{
			auto plane = Plane(Vector3(0, -2, 0), Vector3::Down);
			float dist;
			auto ray = m_ray;
			if (ray.Intersects(plane, dist))
			{
				auto pos = ray.position + ray.direction * dist;
				m_batch->Begin();
				m_batch->DrawLine(VertexPositionColor(Vector3::Zero, Colors::Green), VertexPositionColor(pos, Colors::Yellow));
				m_batch->End();
			}

			m_batch->Begin();
			m_batch->DrawLine(VertexPositionColor(ray.position, Colors::Red), VertexPositionColor(ray.position + ray.direction, Colors::Blue));
			m_batch->End();
		}
	};
	context << std::make_shared<RayTest>();
}
