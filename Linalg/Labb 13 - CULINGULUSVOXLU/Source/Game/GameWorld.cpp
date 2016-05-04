#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/math/vector2.h>
#include <tga2d/Engine.h>
#include <tga2d/text/text.h>
#include <Macros/Macros.h>
#include <sstream>
#include "TinyXML2/tinyxml2.h"
#include <iostream>
#include "BaseGameStructure\GameObjectsManager.h"
#include "../CommonUtilities/Vectors/Vector.h"
#include "CreatePlane.h"


#include <InputWrapper/InputWrapper.h>

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
	if (myRenderingInfo != nullptr)
	{
		delete myRenderingInfo;
		myRenderingInfo = nullptr;
	}
}

void CGameWorld::Init()
{
	

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
	myPrettySphere.Init(Vector3f(3.f, 0.f, 0.f), nullptr);
	myPrettyTorus.Init(Vector3f(6.f, 0.f, 0.f), nullptr);

	myPrettyCube.AddVoxels(CreateCube(Vector2ui(10, 10)));
	myPrettySphere.AddVoxels(CreateSphere(10, 30));
	myPrettyTorus.AddVoxels(CreateTorus(40, 20));

	myPrettySphere.SetParent(myPrettyCube.GetWorldSpace());
	myPrettyTorus.SetParent(myPrettyCube.GetWorldSpace());
	
	myRenderingInfo = new DX2D::CText("Text/calibril.ttf_sdf");
	myRenderingInfo->myPosition = DX2D::Vector2f(0.3f, 0.3f);

	GameObjectsManager::SetCameraPosition(Vector3f( 0.0f, 0.0f, 0.0f));
}

void CGameWorld::Update(float aTimeDelta)
{
	ShapeContainer::ourNumberOfObjectsThatShouldRender = 0;

	GameObjectsManager::Update(aTimeDelta);

	myPrettyCube.Update();
	myPrettySphere.Update();
	myPrettyTorus.Update(); 


	std::stringstream mahText;

	mahText << "Objects Rendered: " << ShapeContainer::ourNumberOfObjectsThatShouldRender << " / 3";
	myRenderingInfo->myText = mahText.str().c_str();
	
	myRenderingInfo->Render();

	if (CU::InputWrapper::GetKeyDown(DIK_W))
	{
		//GameObjectsManager::IncreaseCameraPosition(Vector3f::UnitZ * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraForward(myCameraSpeed * aTimeDelta);
	}

	if (CU::InputWrapper::GetKeyDown(DIK_S))
	{
		//GameObjectsManager::IncreaseCameraPosition(-Vector3f::UnitZ * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraForward(-myCameraSpeed * aTimeDelta);
	}

	if (CU::InputWrapper::GetKeyDown(DIK_A))
	{
		//GameObjectsManager::IncreaseCameraPosition(-Vector3f::UnitX * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraRight(-myCameraSpeed * aTimeDelta);
	}

	if (CU::InputWrapper::GetKeyDown(DIK_D))
	{
		//GameObjectsManager::IncreaseCameraPosition(Vector3f::UnitX * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraRight(myCameraSpeed * aTimeDelta);
	}



	if (CU::InputWrapper::GetKeyDown(DIK_UPARROW))
	{
		GameObjectsManager::IncreaseCameraPitch(-0.5f * aTimeDelta);
	}

	if (CU::InputWrapper::GetKeyDown(DIK_DOWNARROW))
	{
		GameObjectsManager::IncreaseCameraPitch(0.5f * aTimeDelta);
	}

	if (CU::InputWrapper::GetKeyDown(DIK_RIGHTARROW))
	{
		GameObjectsManager::IncreaseCameraYaw(0.5f * aTimeDelta);
	}

	if (CU::InputWrapper::GetKeyDown(DIK_LEFTARROW))
	{
		GameObjectsManager::IncreaseCameraYaw(-0.5f * aTimeDelta);
	}

	if (CU::InputWrapper::GetKeyDown(DIK_T))
	{
		myPrettyCube.RotateY(0.5f * aTimeDelta);
	}
	if (CU::InputWrapper::GetKeyDown(DIK_G))
	{
		myPrettyCube.RotateX(0.5f * aTimeDelta);
	}
	if (CU::InputWrapper::GetKeyDown(DIK_B))
	{
		myPrettyCube.RotateZ(0.5f * aTimeDelta);
	}


	if (CU::InputWrapper::GetKeyDown(DIK_Y))
	{
		myPrettySphere.RotateY(0.5f * aTimeDelta);
	}
	if (CU::InputWrapper::GetKeyDown(DIK_H))
	{
		myPrettySphere.RotateX(0.5f * aTimeDelta);
	}
	if (CU::InputWrapper::GetKeyDown(DIK_N))
	{
		myPrettySphere.RotateZ(0.5f * aTimeDelta);
	}


	if (CU::InputWrapper::GetKeyDown(DIK_U))
	{
		myPrettyTorus.RotateY(0.5f * aTimeDelta);
	}
	if (CU::InputWrapper::GetKeyDown(DIK_J))
	{
		myPrettyTorus.RotateX(0.5f * aTimeDelta);
	}
	if (CU::InputWrapper::GetKeyDown(DIK_M))
	{
		myPrettyTorus.RotateZ(0.5f * aTimeDelta);
	}

}

void CGameWorld::Draw()
{
	GameObjectsManager::Draw();
}