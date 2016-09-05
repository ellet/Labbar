#include "stdafx.h"
#include "SpatialObject.h"


SpatialObject::SpatialObject()
{
	myChildren.Init(4);
}


SpatialObject::~SpatialObject()
{
}

void SpatialObject::Init(const ConstructData & aCreationData)
{
	mySprite.Init(aCreationData.myFilePath);
	mySprite.SetPivot({ 0.5f, 0.5f });
	mySprite.SetSize(aCreationData.mySize);

	myTransformation.SetPosition(aCreationData.myPosition);
	
	myRotationSpeed = aCreationData.myRotationSpeed;
	myLocalRotationSpeed = aCreationData.myLocalRotationSpeed;
	myCurrentRotation = 0.f;
}

void SpatialObject::Update(const CU::Time & aDeltaTime)
{
	const float newRotation = myRotationSpeed * aDeltaTime.GetSeconds();

	myCurrentRotation += myLocalRotationSpeed * aDeltaTime.GetSeconds();

	myTransformation.Rotate2D(DEGRESS_TO_RADIANSF(newRotation));
	
	mySprite.SetRotationDegrees(myCurrentRotation);

	for (unsigned short iChild = 0; iChild < myChildren.Size(); ++iChild)
	{
		myChildren[iChild]->Update(aDeltaTime);
	}
}

void SpatialObject::Draw(const CU::Matrix33f & aParentMatrix) const
{
	CU::Matrix33f tempTransformation = myTransformation * aParentMatrix;

	for (unsigned short iChild = 0; iChild < myChildren.Size(); ++iChild)
	{
		myChildren[iChild]->Draw(tempTransformation);
	}

	mySprite.Draw(tempTransformation.GetPosition());
}

void SpatialObject::AddChild(SpatialObject & aSpatialObject)
{
	myChildren.Add(&aSpatialObject);
}

const CU::Vector2f & SpatialObject::GetPosition()
{
	return myTransformation.GetPosition();
}

const CU::Matrix33f & SpatialObject::GetTransformation()
{
	return myTransformation;
}
