#pragma once
#include <vector>
#include <CU/NameSpaceAliases.h>
#include <CU/Vectors/vector2.h>
//class PartionGrid;

namespace CommonUtilities
{
	class Time;
}

class KDTree;

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
	int myHashtagDeep;

	CU::Vector2f myMouseStartPosition;

	KDTree * myPrettyTree;
	
	int testInt;
	
};