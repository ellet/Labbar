#pragma once
#include <vector>

class CWwiseManager;

class SoundObjectIDManager
{
public:
	SoundObjectIDManager();
	~SoundObjectIDManager();

	int GetNewID();

	void RemoveID(int anID);

	bool CheckIfIDExists(int anID);

	void UnregisterAllObjects(CWwiseManager* aManager);

private:
	std::vector<int> myObjectIDs;
	std::vector<int> myRemovedObjectIDs;
};
