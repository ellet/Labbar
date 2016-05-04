#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/math/vector2.h>
#include <tga2d/Engine.h>
#include <tga2d/text/text.h>
#include "../CommonUtilities/Macros.h"
#include <sstream>
#include "TinyXML2/tinyxml2.h"
#include <iostream>
#include "BaseGameStructure\GameObjectsManager.h"
#include "../CommonUtilities/Vectors/Vector.h"
#include "CreatePlane.h"


const size_t StarAmount = 100000;

//using namespace DX2D;
CGameWorld::CGameWorld()
{
	testRotation = 0.f;

	myCameraSpeed = 4.f;

	myDistribution = std::uniform_real_distribution<float>(0.f, 1.f);
}


CGameWorld::~CGameWorld()
{
}

void CGameWorld::Init()
{
	myInput.Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), (*DX2D::CEngine::GetInstance()->GetHWND()));

	/*float randomY = myDistribution(myRandomGenerator);
	float randomX = myDistribution(myRandomGenerator);
	float randomZ = myDistribution(myRandomGenerator);

	myStars.Init(Vector3f(randomX, randomY, randomZ), nullptr);

	float tempRandomNumber = myDistribution(myRandomGenerator);

	for (size_t iStar = 0; iStar < StarAmount; ++iStar)
	{
		randomY = myDistribution(myRandomGenerator);
		randomX = myDistribution(myRandomGenerator);
		randomZ = myDistribution(myRandomGenerator);

		myStars.AddChild(Vector3f(randomX, randomY, randomZ), nullptr);
	}
	*/

	/*myPrettyShape.Init(Vector3f(0.2f, 0.2f, 0.2f), nullptr);


	float randomY = myDistribution(myRandomGenerator);
	float randomX = myDistribution(myRandomGenerator);
	float randomZ = myDistribution(myRandomGenerator);

	CommonUtilities::GrowingArray<Voxel> temp;
	temp.Init(20);

	for (size_t iVoxel = 0; iVoxel < 10; ++iVoxel)
	{
		randomY = myDistribution(myRandomGenerator);
		randomX = myDistribution(myRandomGenerator);
		randomZ = myDistribution(myRandomGenerator);

		Voxel tempVoxel;
		tempVoxel.Init(Vector3f(randomX, randomY, randomZ), 2.f , myPrettyShape.GetMySpace());

		temp.Add(tempVoxel);
	}


	myPrettyShape.AddVoxels(temp);*/

	myPrettyCube.Init(Vector3f(-3.f, 0.f, 5.f), nullptr); 
	myPrettySphere.Init(Vector3f(0.f, 0.f, 5.f), nullptr);
	myPrettyTorus.Init(Vector3f(3.f, 0.f, 5.f), nullptr);

	myPrettyCube.AddVoxels(CreateCube(Vector2ui(10, 10)));
	myPrettySphere.AddVoxels(CreateSphere(10, 30));
	myPrettyTorus.AddVoxels(CreateTorus(40, 20));

	



	GameObjectsManager::SetCameraPosition(Vector3f( 0.0f, 0.0f, 0.0f));
}

void CGameWorld::Update(float aTimeDelta)
{
	GameObjectsManager::Update(aTimeDelta);

	myInput.Update();

	if (myInput.GetKeyDown(DIK_W))
	{
		//GameObjectsManager::IncreaseCameraPosition(Vector3f::UnitZ * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraForward(myCameraSpeed * aTimeDelta);
	}

	if (myInput.GetKeyDown(DIK_S))
	{
		//GameObjectsManager::IncreaseCameraPosition(-Vector3f::UnitZ * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraForward(-myCameraSpeed * aTimeDelta);
	}

	if (myInput.GetKeyDown(DIK_A))
	{
		//GameObjectsManager::IncreaseCameraPosition(-Vector3f::UnitX * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraRight(-myCameraSpeed * aTimeDelta);
	}

	if (myInput.GetKeyDown(DIK_D))
	{
		//GameObjectsManager::IncreaseCameraPosition(Vector3f::UnitX * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraRight(myCameraSpeed * aTimeDelta);
	}



	if (myInput.GetKeyDown(DIK_UPARROW))
	{
		GameObjectsManager::IncreaseCameraPitch(-0.5f * aTimeDelta);
	}

	if (myInput.GetKeyDown(DIK_DOWNARROW))
	{
		GameObjectsManager::IncreaseCameraPitch(0.5f * aTimeDelta);
	}

	if (myInput.GetKeyDown(DIK_RIGHTARROW))
	{
		GameObjectsManager::IncreaseCameraYaw(0.5f * aTimeDelta);
	}

	if (myInput.GetKeyDown(DIK_LEFTARROW))
	{
		GameObjectsManager::IncreaseCameraYaw(-0.5f * aTimeDelta);
	}

	if (myInput.GetKeyDown(DIK_T))
	{
		myPrettyCube.RotateY(0.5f * aTimeDelta);
	}
	if (myInput.GetKeyDown(DIK_G))
	{
		myPrettyCube.RotateX(0.5f * aTimeDelta);
	}
	if (myInput.GetKeyDown(DIK_B))
	{
		myPrettyCube.RotateZ(0.5f * aTimeDelta);
	}


	if (myInput.GetKeyDown(DIK_Y))
	{
		myPrettySphere.RotateY(0.5f * aTimeDelta);
	}
	if (myInput.GetKeyDown(DIK_H))
	{
		myPrettySphere.RotateX(0.5f * aTimeDelta);
	}
	if (myInput.GetKeyDown(DIK_N))
	{
		myPrettySphere.RotateZ(0.5f * aTimeDelta);
	}


	if (myInput.GetKeyDown(DIK_U))
	{
		myPrettyTorus.RotateY(0.5f * aTimeDelta);
	}
	if (myInput.GetKeyDown(DIK_J))
	{
		myPrettyTorus.RotateX(0.5f * aTimeDelta);
	}
	if (myInput.GetKeyDown(DIK_M))
	{
		myPrettyTorus.RotateZ(0.5f * aTimeDelta);
	}

}

void CGameWorld::Draw()
{
	GameObjectsManager::Draw();
}