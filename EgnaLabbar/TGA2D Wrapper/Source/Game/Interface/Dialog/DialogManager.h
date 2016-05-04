#pragma once

#include <string>
#include <map>

#include <DLDebug\DL_Debug.h>
#include <Queue\ObjectQueue.h>

#include "DialogRenderer.h"
#include "Dialog.h"

//#include "..\InterfaceClickable.h"
#include "../InterfaceBase.h"

namespace DX2D
{
	class CSprite;
}

class DialogManager : public InterfaceBase
{
public:

	static void Create();
	static void Destroy();

	//Initialization methods.
	void LoadSpeakerSprite(const std::string &aSpritePath, const std::string &aSpriteID);
	void LoadFont(const std::string &aFontPath);

	inline void LoadBackground(const std::string &aSpritePath);

	inline void SetPosition(const Point2f &aPosition);
	inline void SetSize(const Vector2f &aSize);
	inline void SetTextPosition(const Point2f &aPosition);
	inline void SetTextSize(const Vector2f &aSize);

	inline void SetFontSize(const float aSize);
	inline void SetAvatarPosition(const Point2f &aPosition);

	virtual void Draw() const override final;

	//Dialog methods.
	void AddDialog(const std::string &aText, const std::string &aSpriteID = "");
	void ClearDialogs();

	void NextDialog();

	inline static DialogManager* GetInstance();

private:

	static DialogManager *ourInstance;

	std::map<std::string, DX2D::CSprite*> mySpriteMap;

	DialogRenderer myDialogRenderer;
	CommonUtilities::ObjectQueue<Dialog> myDialogQueue;
	CommonUtilities::GrowingArray<Dialog*> myDialogList;

	size_t myDialogTextIndex;

	DialogManager();
	~DialogManager();

};

inline void DialogManager::LoadBackground(const std::string &aSpritePath)
{
	myDialogRenderer.LoadBackground(aSpritePath);
}

inline void DialogManager::SetPosition(const Point2f &aPosition)
{
	myDialogRenderer.SetPosition(aPosition);
}
inline void DialogManager::SetSize(const Vector2f &aSize)
{
	myDialogRenderer.SetSize(aSize);
}
inline void DialogManager::SetTextPosition(const Point2f &aPosition)
{
	myDialogRenderer.SetTextPosition(aPosition);
}
inline void DialogManager::SetTextSize(const Vector2f &aSize)
{
	myDialogRenderer.SetTextSize(aSize);
}

inline void DialogManager::SetFontSize(const float aSize)
{
	myDialogRenderer.SetFontSize(aSize);
}
inline void DialogManager::SetAvatarPosition(const Point2f &aPosition)
{
	myDialogRenderer.SetAvatarPosition(aPosition);
}

inline DialogManager* DialogManager::GetInstance()
{
	return ourInstance;
}
