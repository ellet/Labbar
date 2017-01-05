#include "stdafx.h"
#include "Engine\Model\ModelInstance.h"
#include "Engine\Model\Model.h"
#include "Engine\Buffer\ConstantBuffer.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Rendering\ModelRenderer.h"

namespace SB
{

	ModelInstance::ModelInstance(const std::shared_ptr<Model> & aModel)
	{
		myModel = aModel;
		myEffect = nullptr;
		myColor = Vector4f::One;
		myCullingCache = 0;
	}

	ModelInstance::~ModelInstance()
	{
	}

	void ModelInstance::SetEffect(const std::shared_ptr<Effect> & aEffect)
	{
		myEffect = aEffect;
	}

	const std::shared_ptr<Effect> & ModelInstance::GetEffect() const
	{
		return myEffect;
	}

	void ModelInstance::Render(const Camera & aCamera) const
	{
		myModel->Render(aCamera, myEffect, myWorldMatrix, myPreviousWorldMatrix, myColor, nullptr, const_cast<uint8_t*>(&myCullingCache));
	}

	void ModelInstance::InstantRender(const Camera & aCamera) const
	{
		myModel->InstantRender(aCamera, myEffect, myWorldMatrix, myPreviousWorldMatrix, myColor);
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

	bool ModelInstance::Prepare(bool aLoadAsynchronously)
	{
		if (myModel != nullptr)
		{
			return myModel->MakeReady(aLoadAsynchronously);
		}
		return true;
	}

	ReceiveResult ModelInstance::Receive(const EndOfFrameMessage & aMessage)
	{
		myPreviousWorldMatrix = myWorldMatrix;
		return ReceiveResult::eContinue;
	}

}
