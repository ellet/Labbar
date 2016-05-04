#pragma once
#include <Vectors/vector3.h>
#include "../../Game/BaseGameStructure/Rendering/RenderCommands.h"

class WorldSpace;

struct Particle
{
	inline Particle();

	Vector3f myPosition;
	Vector3f myVelocity;

	Vector3f myGravity;
	bool myIsAffectedByGravity;

	DX2D::CSprite * myTexture;

	float myTimeLeft;

	float mySize;
	float mySizeDelta;

	float myAlpha;
	float myAlphaDelta;

	WorldSpace * myEmitterSpace;

	bool myIsActive;

	RenderCommands inline Draw();
};

inline Particle::Particle()
{
	myPosition = Vector3f::Zero;
	myVelocity = Vector3f::Zero;

	myGravity = Vector3f::Zero;
	myIsAffectedByGravity = false;

	myTexture = nullptr;

	myTimeLeft = 0.f;

	mySize = 1.f;
	mySizeDelta = 0.f;

	myAlpha = 1.f;
	myAlphaDelta = 0.f;

	myIsActive = false;
	myEmitterSpace = nullptr;
}

RenderCommands  Particle::Draw()
{
	RenderCommands temp;

	temp.Init(myTexture, myPosition, myEmitterSpace, Vector4f(1.f, 1.f, 1.f, myAlpha), Vector2f(mySize, mySize));

	return temp;
}