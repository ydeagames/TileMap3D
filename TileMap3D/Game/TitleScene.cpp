#include "pch.h"
#include "TitleScene.h"
#include "SceneCommons.h"
#include <Framework/SceneManager.h>
#include <Utilities/Input.h>
#include <Utilities/MathUtils.h>
#include <Game/BaseScene.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

// ����
void TitleScene::Build(GameContext& context)
{
	auto text = std::make_shared<FontObject>(L"Resources/Fonts/logofont.spritefont", L"");
	context << text;

	struct TextUpdater : public GameObject
	{
		std::shared_ptr<FontObject> text;
		int modeSelected[2] = { 0, 1 };
		std::wstring modes[3] = { L"�v���C���[", L"CP (��)", L"CP (��)" };
		int selected = 2;

		TextUpdater(std::shared_ptr<FontObject>& text)
			: text(text) {}

		void Update(GameContext& ctx)
		{
			if (0 <= selected && selected < 2)
			{
				if (Input::GetKeyDown(Keyboard::Keys::Left))
					modeSelected[selected] = MathUtils::Loop(modeSelected[selected] - 1, 0, 3);
				else if (Input::GetKeyDown(Keyboard::Keys::Right))
					modeSelected[selected] = MathUtils::Loop(modeSelected[selected] + 1, 0, 3);
			}
			else
			{
				if (Input::GetKeyDown(Keyboard::Keys::Space))
				{
					BaseScene::mode1p = modeSelected[0];
					BaseScene::mode2p = modeSelected[1];
					ctx.GetSceneManager().LoadScene("BaseScene");
				}
			}

			if (Input::GetKeyDown(Keyboard::Keys::Up))
				selected = MathUtils::Loop(selected - 1, 0, 3);
			else if (Input::GetKeyDown(Keyboard::Keys::Down))
				selected = MathUtils::Loop(selected + 1, 0, 3);

			std::wstringstream str;
			str << L"�I�Z��" << std::endl;
			str << (selected == 0 ? L"��" : L"�@") << L"1P : " << modes[modeSelected[0]] << std::endl;
			str << (selected == 1 ? L"��" : L"�@") << L"2P : " << modes[modeSelected[1]] << std::endl;
			str << (selected == 2 ? L"��" : L"�@") << L"�����`��" << std::endl;

			str << std::endl;
			str << L"�E�㉺�L�[�őI��" << std::endl;
			str << L"�E���E�L�[�Ń��[�h�؂�ւ�" << std::endl;
			str << L"�E�X�y�[�X�L�[�Ō���" << std::endl;

			text->SetText(str.str());
		}
	};
	context << std::make_shared<TextUpdater>(text);

	struct ResultListener : public GameObject
	{
		void Update(GameContext& ctx)
		{
			if (Input::GetKeyDown(Keyboard::Keys::Escape))
				PostQuitMessage(0);
		}
	};
	context << std::make_shared<ResultListener>();
}
