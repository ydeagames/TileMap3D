#include "pch.h"
#include "BuildSettings.h"
#include <Framework/SceneManager.h>
#include "TitleScene.h"
#include "BaseScene.h"
#include "ResultScene.h"

void BuildSettings::Build(GameContext& context)
{
	context.GetSceneManager().Register<TitleScene>("TitleScene");
	context.GetSceneManager().Register<BaseScene>("BaseScene");
	context.GetSceneManager().Register<ResultScene>("ResultScene");

	context.GetSceneManager().LoadScene("TitleScene");
}
