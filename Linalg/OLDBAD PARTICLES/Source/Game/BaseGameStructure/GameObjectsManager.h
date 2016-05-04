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

	static void AddRenderToQue(const RenderCommands & aRenderCommand);

	static void SetCameraPosition(Vector3f aPosition);

	//static void IncreaseCameraPosition(Vector3f aPosition);

	static void IncreaseCameraForward(float aDelta);

	static void IncreaseCameraRight(float aDelta);

	static void IncreaseCameraYaw(float aRadian);

	static void IncreaseCameraPitch(float aRadian);

	static void IncreaseCameraRoll(float aRadian);



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

	CommonUtilities::GrowingArray<RenderCommands, unsigned int> myDrawQue;

	GameObjectsManager();
	~GameObjectsManager();

	static GameObjectsManager* ourInstance;

	GameObjectsFactory myFactory;
};

