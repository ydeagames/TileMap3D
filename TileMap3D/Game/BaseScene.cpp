#include "pch.h"
#include "BaseScene.h"
#include "SceneCommons.h"
#include <Framework/SceneManager.h>
#include <Framework/DebugTools/DebugCameraWrapper.h>
#include <Framework/DebugTools/GridFloorWrapper.h>
#include "CubeMap.h"
#include "ResultScene.h"
#include <Utilities/Input.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

int BaseScene::mode1p = 0;
int BaseScene::mode2p = 0;

// ê∂ê¨
void BaseScene::Build(GameContext& context)
{
	auto debugCamera = std::make_shared<DebugCameraWrapper>();
	context << debugCamera;
	context << std::make_shared<GridFloorWrapper>();

	context.GetCamera().view = Matrix::CreateLookAt(Vector3(0, 5, 10), Vector3::Zero, Vector3::Up);
	debugCamera->GetDebugCamera().m_xAngle = XMConvertToRadians(60);

	auto tiledmap = std::make_shared<TiledMap>();
	tiledmap->Load(L"Resources/Maps/map.csv");
	auto tiledstone = std::make_shared<TiledMap>();
	tiledstone->Load(L"Resources/Maps/stone.csv");

	auto othello = std::make_shared<Othello>(tiledstone.get());
	othello->Initialize();
	Othello::ThinkType thinks[3] = { &Othello::think1, &Othello::think2, &Othello::think3 };
	othello->m_think[0] = thinks[mode1p];
	othello->m_think[1] = thinks[mode2p];

	auto cubemap = std::make_shared<CubeMap>(tiledmap, tiledstone, othello);
	context << cubemap;

	struct ResultListener : public GameObject
	{
		std::shared_ptr<TiledMap> tiledstone;

		ResultListener(std::shared_ptr<TiledMap>& tiledstone)
			: tiledstone(tiledstone) {}

		void Update(GameContext& ctx)
		{
			bool flag = true;
			int score_black = 0, score_white = 0;

			int row = tiledstone->GetRow();
			int column = tiledstone->GetColumn();
			auto& data = tiledstone->GetData();
			for (int iy = 0; iy < row; iy++)
			{
				for (int ix = 0; ix < column; ix++)
				{
					int& id = data[iy][ix];
					if (id == 1)
						score_black++;
					else if (id == 2)
						score_white++;
					else
						flag = false;
				}
			}

			if (flag)
			{
				ResultScene::score_black = score_black;
				ResultScene::score_white = score_white;
				ctx.GetSceneManager().LoadScene("ResultScene");
			}

			if (Input::GetKeyDown(Keyboard::Keys::Escape))
				ctx.GetSceneManager().LoadScene("TitleScene");
		}
	};
	context << std::make_shared<ResultListener>(tiledstone);

	auto text = std::make_shared<FontObject>(L"Resources/Fonts/logofont.spritefont", L"");
	context << text;

	struct TextUpdater : public GameObject
	{
		std::shared_ptr<FontObject> text;
		std::shared_ptr <Othello> othello;

		TextUpdater(std::shared_ptr<FontObject>& text, std::shared_ptr<Othello>& othello)
			: text(text)
			, othello(othello) {}

		void Update(GameContext& ctx)
		{
			text->SetText(othello->msg);
		}
	};
	context << std::make_shared<TextUpdater>(text, othello);
}
