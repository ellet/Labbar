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

	mySpace.SetPosition(aCreationData.myPosition);
	
	myChildrenRotationSpeed = aCreationData.myRotationSpeed;
	myLocalRotationSpeed = aCreationData.myLocalRotationSpeed;
	myOrbitSpeed = aCreationData.myOrbitSpeed;
	myCurrentRotation = 0.f;
}

void SpatialObject::Update(const CU::Time & aDeltaTime)
{
	const float newRotation = myChildrenRotationSpeed * aDeltaTime.GetSeconds();

	myCurrentRotation += myLocalRotationSpeed * aDeltaTime.GetSeconds();

	mySpace.Rotate2D(DEGRESS_TO_RADIANSF(newRotation));
	mySpace.RotateAroundAxis2D(DEGRESS_TO_RADIANSF(myOrbitSpeed * aDeltaTime.GetSeconds()));
	
	mySprite.SetRotationDegrees(myCurrentRotation);

	for (unsigned short iChild = 0; iChild < myChildren.Size(); ++iChild)
	{
		myChildren[iChild]->Update(aDeltaTime);
	}
}

void SpatialObject::Draw(const CU::Matrix33f & aParentMatrix) const
{
	CU::Matrix33f tempTransformation;// = mySpace.GetTransform();//myTransformation * aParentMatrix;

	for (unsigned short iChild = 0; iChild < myChildren.Size(); ++iChild)
	{
		myChildren[iChild]->Draw(tempTransformation);
	}

	//CU::Vector2f temppos = mySpace.GetPosition();
	mySprite.Draw(mySpace.GetPosition());
}

void SpatialObject::AddChild(SpatialObject & aSpatialObject)
{
	aSpatialObject.SetParentSpace(mySpace);
	myChildren.Add(&aSpatialObject);
}

void SpatialObject::SetParentSpace(const CU::Space& aSpace)
{
	mySpace.SetParent(aSpace);
}

const CU::Vector2f & SpatialObject::GetPosition()
{
	return mySpace.GetPosition();
}

const CU::Matrix33f & SpatialObject::GetTransformation()
{
	return mySpace.GetTransform();
}
