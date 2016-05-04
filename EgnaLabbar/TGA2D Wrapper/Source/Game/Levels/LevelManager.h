#pragma once
#include <GrowingArray\GrowingArray.h>
#include "..\JsonParser\JsonParser.h"


class Player;
class Editor;

class LevelManager
{
public:
	static void Init(Player *aPlayer, Inventory *aInventory);
	static void Update(const float aDeltaTime);
	static void Draw();
	static void CheckForInput();
	static void ChangeLevel(const std::string &aLevelName);
	inline static void Create();
	inline static void Destroy();
	inline static LevelManager &GetInstance();
	static LevelManager *ourInstance;

	static void SetPlayerGotoPosition(Vector2f aPosition);
private:
	void InitInternal(Player *aPlayer, Inventory *aInventory);
	void UpdateInternal(const float aDeltaTime);
	void DrawInternal();
	void CheckForInputInternal();
	void ChangeLevelInternal(const std::string &aLevelName);


	static CommonUtilities::GrowingArray<Level> myLevels;
	static Level *ourCurrentLevel;
	static Player *ourPlayer;
	static Editor *ourEditor;

};

inline LevelManager& LevelManager::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "EventManager is nullptr");
	return (*ourInstance);
}

void LevelManager::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new LevelManager();
	}
}

void LevelManager::Destroy()
{
	delete ourInstance;

	ourInstance = nullptr;
}

