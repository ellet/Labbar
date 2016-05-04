#pragma once
#include <../CommonUtilities/InputWrapper.h>
#include "TinyXML2/tinyxml2.h"
#include <vector>
#include "BaseGameStructure\GameObjects\TemplateGameObject.h"
#include "../CommonUtilities/GrowingArray/GrowingArray.h"
#include "BaseGameStructure\GameObjects\Dot.h"
#include "Objects\DotImageContainer.h"


class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta);
	void Draw();


private:
	DotImageContainer myGubbeWithHat;
	float testRotation;
};