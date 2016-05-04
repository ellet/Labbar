#pragma once
//#include <CommonUtilities/InputWrapper.h>
#include "TinyXML2/tinyxml2.h"
#include <vector>
#include "BaseGameStructure\GameObjects\TemplateGameObject.h"
#include "../CommonUtilities/GrowingArray/GrowingArray.h"
#include "BaseGameStructure\GameObjects\Dot.h"
#include "Objects\DotImageContainer.h"
#include "Objects\ShapeContainer.h"
#include <InputWrapper\InputWrapper.h>
#include <random>

#include <Particles/Particle.h>
//#include "../ParticleSystem/Particles/Particle.h"


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
	
	float testRotation;
};