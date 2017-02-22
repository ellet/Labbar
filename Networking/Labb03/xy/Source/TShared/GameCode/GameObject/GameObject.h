#pragma once
#include <map>

#include <GameCode/Components/ComponentMessages.h>
#include <unordered_map>
#include <..\DX2DEngine\tga2d\math\vector2.h>

#include "GameCode\Components\BaseComponent.h"
#include "GameCode\Components\ComponentIds.h"

class CGameObject
{
public:
	CGameObject();
	~CGameObject();

	template<class T>
	T* CreateComponent();
	template<class T>
	T* GetComponent();

	void BroadCastMessage(CComponentMessageBase* aMessage);

	void Update(float aTimeDelta);
	void Render();

	DX2D::Vector2f myPosition;
	unsigned short myID;
	unsigned short myUserID;
private:
	
	CBaseComponent* myComponents[EComponentIds_Count];
};

template<class T>
T* CGameObject::CreateComponent()
{
	T* newComp = new T();
	newComp->myOwner = this;
	myComponents[T::myID] = newComp;
	return newComp;
}

template<class T>
T* CGameObject::GetComponent()
{
	return static_cast<T*>(myComponents[T::myID]);
}

