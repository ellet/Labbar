#include "stdafx.h"
#include "ObjectManager.h"

ObjectManager *ObjectManager::ourInstance;
std::map<std::string, Object*> ObjectManager::myObjectsMap;

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}
