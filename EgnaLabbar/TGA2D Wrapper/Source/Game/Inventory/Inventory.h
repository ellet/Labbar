#pragma once
#include <GrowingArray\GrowingArray.h>
#include <map>
class Object;
class InventoryInterface;

class Inventory
{
public:
	Inventory();
	~Inventory();
	bool AddObjectToInventory(Object* aObject);
	void RemoveObjectFromInventory(Object* aObjectToRemove);
	const CommonUtilities::GrowingArray<Object*>& GetAllInventoryObjects() const;
	Object* GetAObject(Object *aObject);
	void Update(const float aDeltaTime);
	void SetInventoryInterface(InventoryInterface* aInterface);
	void SetSelectedObject(Object *aObject);
	void RemoveSelectedObject();
	bool HasSelectedObject();
	Object *GetSelectedObject();
	Object *GetSelectedObjectSprite();
	bool HasObject(std::string &aName);
private:
	int myMaxNumberOfObjects;
	int myObjectCount;
	CommonUtilities::GrowingArray<Object*> myObjects;
	InventoryInterface *myInventoryInterface;
	Object *mySelectedObjectSprite;
	Object *mySelectedObjectData;
};

