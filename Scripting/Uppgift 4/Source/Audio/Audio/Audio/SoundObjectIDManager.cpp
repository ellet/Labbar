#include "SoundObjectIDManager.h"
#include "WwiseManager.h"

#define SOUND_OBJECTS_STARTSIZE 2000
#define REMOVED_SOUND_OBJECT_STARTSIZE 200

SoundObjectIDManager::SoundObjectIDManager()
{
	myObjectIDs.reserve(SOUND_OBJECTS_STARTSIZE);
	myRemovedObjectIDs.reserve(REMOVED_SOUND_OBJECT_STARTSIZE);
}


SoundObjectIDManager::~SoundObjectIDManager()
{
}


int SoundObjectIDManager::GetNewID()
{
	int ID = 0;

	if (myRemovedObjectIDs.size() > 0)
	{
		ID = myRemovedObjectIDs.back();
		myRemovedObjectIDs.erase(myRemovedObjectIDs.end() - 1);
	}
	else
	{
		ID = (int)myObjectIDs.size() + 1;
	}

	myObjectIDs.push_back(ID);
	return ID;
}

void SoundObjectIDManager::RemoveID(int anID)
{
	for (size_t i = 0; i < myObjectIDs.size(); i++)
	{
		if (myObjectIDs[i] == anID)
		{
			myObjectIDs.erase(myObjectIDs.begin() + i);
			myRemovedObjectIDs.push_back(anID);
			break;
		}
	}
}

bool SoundObjectIDManager::CheckIfIDExists(int anID)
{
	for (size_t i = 0; i < myObjectIDs.size(); i++)
	{
		if (myObjectIDs[i] == anID)
		{
			return true;
		}
	}
	return false;
}

void SoundObjectIDManager::UnregisterAllObjects(CWwiseManager* aManager)
{
	for (unsigned short i = 0; i < myRemovedObjectIDs.size(); ++i)
	{
		aManager->UnRegisterObject(myRemovedObjectIDs[i]);
	}

	for (unsigned short i = 0; i < myObjectIDs.size(); ++i)
	{
		aManager->UnRegisterObject(myObjectIDs[i]);
	}
}