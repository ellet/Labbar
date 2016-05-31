#pragma once
#include <vector>
#include <CU/NameSpaceAliases.h>
//class PartionGrid;

namespace CommonUtilities
{
	class Time;
}

class OctoTree;

class StaticSprite;

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(const CU::Time & aTime); 
	void Draw() const;
private:

	OctoTree * myPrettyTree;
	
	int testInt;
	
};