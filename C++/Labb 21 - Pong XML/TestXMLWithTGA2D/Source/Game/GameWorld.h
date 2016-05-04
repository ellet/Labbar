#pragma once
#include <vector>
#include "TinyXML2\tinyxml2.h"

namespace DX2D
{
	class CSprite;
	class CSpriteBatch;
	class CText;
	class CCustomShape;
}

class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta);
private:
	void ReadXMLFile(tinyxml2::XMLElement & aStartingElement);
	void SetAGameObject(tinyxml2::XMLElement & aBaseElement);

	DX2D::CSprite* myCarSprite;
	DX2D::CSprite* myCarSprite2;
	DX2D::CText* text;

	
};