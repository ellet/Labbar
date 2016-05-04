#include "stdafx.h"
#include "TemplateGameObject.h"
#include "../GameObjectsManager.h"


TemplateGameObject::TemplateGameObject()
{
	
}


TemplateGameObject::~TemplateGameObject()
{
}


void TemplateGameObject::Init()
{
	myBaseGameObjectIndex = GameObjectsManager::GetNewBaseGameObjectIndex();
	
	GetMyBaseGameObject().Init("sprites/templatesprite.png");
}

BaseGameObject & TemplateGameObject::GetMyBaseGameObject()
{
	return GameObjectsManager::GetBaseGameObject(myBaseGameObjectIndex);
}