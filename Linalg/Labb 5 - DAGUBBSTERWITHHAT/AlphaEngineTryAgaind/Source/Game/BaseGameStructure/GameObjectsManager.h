#pragma once
#include "Factories\GameObjectsFactory.h"
#include "../CommonUtilities/GrowingArray/GrowingArray.h"
#include "Rendering\RenderCommands.h"
#include <string>

class BaseGameObject;
class TemplateGameObject;

class GameObjectsManager
{
public:
	static void CreateGameObjectsManager();

	static BaseGameObject & GetBaseGameObject(size_t aIndex);

	static void Update(float aDeltaTime);
	static void Draw();

	static size_t GetNewBaseGameObjectIndex();

	static void AddRenderToQue(const RenderCommands aRenderCommand);

//#pragma region CreateObjects
//
//	static TemplateGameObject GetNewTemplateGameObject();
//
//
//#pragma endregion
private:
	void DrawAllCommands();

	static GameObjectsManager* GetInstance();

	CommonUtilities::GrowingArray<RenderCommands> myDrawQue;

	GameObjectsManager();
	~GameObjectsManager();

	static GameObjectsManager* ourInstance;

	GameObjectsFactory myFactory;
};

