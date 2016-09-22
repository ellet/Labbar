#include "stdafx.h"
#include "ModelInstance.h"
#include "Model.h"
#include "ConstantBuffer.h"
#include "DXRenderer.h"
#include "ModelRenderer.h"
#include "StandardEffect.h"
#include "AssimpModel.h"

ModelInstance::ModelInstance(const std::shared_ptr<Model> & aModel)
{
	myModel = aModel;
	myIsLoaded = true;
}

ModelInstance::ModelInstance()
{
	myModel = nullptr;
	myIsLoaded = false;
}

ModelInstance::~ModelInstance()
{
}

void ModelInstance::Render() const
{
	if (myIsLoaded == true)
	{
		myModel->Render(myWorldMatrix);
	}
}

void ModelInstance::InstantRender() const
{
	if (myIsLoaded == true)
	{
		myModel->InstantRender(myWorldMatrix);
	}
}

void ModelInstance::SetMatrix(const Matrix44f & aMatrix)
{
	myWorldMatrix = aMatrix;
}

BoundingBoxf ModelInstance::GetBoundingBox() const
{
	BoundingBoxf boundingBox = myModel->GetBoundingBox();
	boundingBox.min = Vector4f(boundingBox.min, 1.f) * myWorldMatrix;
	boundingBox.max = Vector4f(boundingBox.max, 1.f) * myWorldMatrix;
	return boundingBox;
}

void ModelInstance::SetPosition(const Vector3f & aPosition)
{
	myWorldMatrix.SetPosition(aPosition);
}

void ModelInstance::Load(std::shared_ptr<StandardEffect> & anEffect, const std::string & aFilePath)
{
	myModel = std::make_shared<AssimpModel>(anEffect, aFilePath);
	myIsLoaded = true;
}


