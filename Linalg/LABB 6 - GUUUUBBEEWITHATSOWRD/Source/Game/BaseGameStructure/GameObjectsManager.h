#pragma once
#include "Factories\GameObjectsFactory.h"
#include "../CommonUtilities/GrowingArray/GrowingArray.h"
#include "Rendering\RenderCommands.h"
#include <string>
#include "../BaseGameStructure/Rendering/Camera.h"

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

	static void SetCameraPosition(Vector2f aPosition);

	static void IncreaseCameraPosition(Vector2f aPosition);

	static void IncreaseCameraRotation(float aRadian);

//#pragma region CreateObjects
//
//	static TemplateGameObject GetNewTemplateGameObject();
//
//
//#pragma endregion
private:
	Camera myCamera;

	void DrawAllCommands();

	static GameObjectsManager* GetInstance();

	CommonUtilities::GrowingArray<RenderCommands> myDrawQue;

	GameObjectsManager();
	~GameObjectsManager();

	static GameObjectsManager* ourInstance;

	GameObjectsFactory myFactory;
};

