#pragma once
//#include <../CommonUtilities/InputWrapper.h>
#include "TinyXML2/tinyxml2.h"
#include <vector>
#include "BaseGameStructure\GameObjects\TemplateGameObject.h"
#include "../CommonUtilities/GrowingArray/GrowingArray.h"
#include "BaseGameStructure\GameObjects\Dot.h"
#include "Objects\DotImageContainer.h"
#include "Objects\ShapeContainer.h"
#include <tga2d\text\text.h>
#include <random>


class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta);
	void Draw();



private:
	//InputWrapper myInput;

	float myCameraSpeed;

	std::default_random_engine myRandomGenerator;
	std::uniform_real_distribution<float> myDistribution; //(0.0f, 1.0f);

	ShapeContainer myPrettyCube;
	ShapeContainer myPrettySphere;
	ShapeContainer myPrettyTorus;

	DX2D::CText * myRenderingInfo;

	//DotImageContainer myStars;
	
	float testRotation;
};