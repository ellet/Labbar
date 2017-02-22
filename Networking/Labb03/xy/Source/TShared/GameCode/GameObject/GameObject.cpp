#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
{
	for (int i = 0; i < EComponentIds_Count; i++)
	{
		myComponents[i] = nullptr;
	}
}


CGameObject::~CGameObject()
{
	for (int i=0; i< EComponentIds_Count; i++)
	{
		delete myComponents[i];
		myComponents[i] = nullptr;
	}

}

void CGameObject::BroadCastMessage(CComponentMessageBase* aMessage)
{
	for (int i = 0; i < EComponentIds_Count; i++)
	{
		if (myComponents[i])
		{
			myComponents[i]->OnMessage(aMessage);
		}
		
	}
}

void CGameObject::Update(float aTimeDelta)
{
	for (int i = 0; i < EComponentIds_Count; i++)
	{
		if (myComponents[i])
		{
			myComponents[i]->Update(aTimeDelta);
		}
	}
}

void CGameObject::Render()
{
	for (int i = 0; i < EComponentIds_Count; i++)
	{
		if (myComponents[i])
		{
			myComponents[i]->Render();
		}
	}
}
