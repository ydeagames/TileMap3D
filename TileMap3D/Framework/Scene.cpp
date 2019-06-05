#include "pch.h"
#include "Scene.h"

void Scene::Initialize(GameContext& context)
{
	for (auto& object : gameObjects)
		object->Initialize(context);
}

void Scene::Update(GameContext& context)
{
	for (auto& object : gameObjects)
		object->Update(context);
}

void Scene::Render(GameContext& context)
{
	for (auto& object : gameObjects)
		object->Render(context);
}

void Scene::Finalize(GameContext& context)
{
	for (auto& object : gameObjects)
		object->Finalize(context);
}

