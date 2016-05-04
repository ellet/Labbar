#pragma once
#include <../CommonUtilities/InputWrapper.h>
#include "TinyXML2/tinyxml2.h"
#include <vector>
#include "BaseGameStructure\GameObjects\TemplateGameObject.h"
#include "../CommonUtilities/GrowingArray/GrowingArray.h"
#include "BaseGameStructure\GameObjects\Dot.h"
#include "Objects\DotImageContainer.h"
#include "../CommonUtilities/InputWrapper.h"


class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta);
	void Draw();



private:
	InputWrapper myInput;

	DotImageContainer myGubbeWithHat;
	DotImageContainer myGubbeArm;
	DotImageContainer myGubbeSword;
	DotImageContainer myTHING;
	float testRotation;
};