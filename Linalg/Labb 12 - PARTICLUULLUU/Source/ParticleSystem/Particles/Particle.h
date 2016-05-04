#pragma once
#include <Vectors/vector3.h>
#include "../../Game/BaseGameStructure/Rendering/RenderCommands.h"
#include <tga2d/sprite/sprite.h>
#include <GrowingArray/GrowingArray.h>
#include "ForceField/ForceField.h"

class WorldSpace;

namespace DX2D
{
	class CSpriteBatch;
}

struct Particle
{
	inline Particle();

	Vector3f myPosition;
	Vector3f myVelocity;

	Vector3f myGravity;
	bool myIsAffectedByGravity;

	DX2D::CSpriteBatch * mySpriteBatch;
	CU::GrowingArray<ForceField> * myLocalForceFields;

	float myTimeLeft;

	float mySize;
	float mySizeDelta;

	float myAlpha;
	float myAlphaDelta;

	Vector3f myColor;

	WorldSpace * myEmitterSpace;

	bool myIsActive;

	RenderCommands inline Draw();

	inline void ResetParticle();

private:
	DX2D::CSprite * myTexture;
};

inline Particle::Particle()
{
	ResetParticle();
}

RenderCommands  Particle::Draw()
{
	RenderCommands temp;

	temp.Init(myTexture, mySpriteBatch,myPosition, myEmitterSpace, Vector4f(myColor.r, myColor.g, myColor.b, myAlpha), Vector2f(mySize, mySize));

	return temp;
}

inline void Particle::ResetParticle()
{
	myPosition = Vector3f::Zero;
	myVelocity = Vector3f::Zero;

	myGravity = Vector3f::Zero;
	myIsAffectedByGravity = false;

	myColor = Vector3f::One;

	if (myTexture == nullptr)
	{
		myTexture = new DX2D::CSprite(nullptr);
	}

	myLocalForceFields = nullptr;

	mySpriteBatch = nullptr;
	myTimeLeft = 0.f;

	mySize = 1.f;
	mySizeDelta = 0.f;

	myAlpha = 1.f;
	myAlphaDelta = 0.f;

	myIsActive = false;
	myEmitterSpace = nullptr;
}

