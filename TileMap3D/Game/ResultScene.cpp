#include "pch.h"
#include "ResultScene.h"
#include "SceneCommons.h"
#include <Framework/SceneManager.h>
#include "CubeMap.h"
#include <Utilities/Input.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

int ResultScene::score_white = 0;
int ResultScene::score_black = 0;

// ê∂ê¨
void ResultScene::Build(GameContext& context)
{
	std::wstringstream str;
	str << L"èüïâÇ†ÇË" << std::endl;
	str << L"  åãâ " << std::endl;
	str << L"    çï : " << score_black << std::endl;
	str << L"    îí : " << score_white << std::endl;
	str << L"    " << ((score_black > score_white) ? L"çï" : L"îí") << L" ÇÃèüÇø" << std::endl;

	auto text = std::make_shared<FontObject>(L"Resources/Fonts/logofont.spritefont", str.str());
	context << text;

	struct ResultListener : public GameObject
	{
		void Update(GameContext& ctx)
		{
			if (Input::GetKeyDown(Keyboard::Keys::Space) || Input::GetKeyDown(Keyboard::Keys::Escape))
				ctx.GetSceneManager().LoadScene("TitleScene");
		}
	};
	context << std::make_shared<ResultListener>();
}
