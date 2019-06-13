#include "pch.h"
#include "BuildSettings.h"
#include <Framework/SceneManager.h>
#include "BaseScene.h"

void BuildSettings::Build(GameContext& context)
{
	context.GetSceneManager().Register<BaseScene>("BaseScene");

	context.GetSceneManager().LoadScene("BaseScene");
}
