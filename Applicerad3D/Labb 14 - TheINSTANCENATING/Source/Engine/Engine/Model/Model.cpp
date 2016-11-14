#include "stdafx.h"
#include "Engine\Model\Model.h"
#include "Engine\Effect\Effect.h"
#include "Engine\Model\Mesh.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Rendering\ModelRenderer.h"

namespace ENGINE_NAMESPACE
{
	Model::Model()
	{
	}

	Model::Model(const std::shared_ptr<GenericMesh> & aMesh)
	{
		AddMesh(aMesh);
	}

	Model::~Model()
	{
	}

	void Model::Render(const std::shared_ptr<Effect>& aEffect, const Matrix44f& aMatrix, const Matrix44f & aLastFrameMatrix, const Vector4f& aColor) const
{
		ModelRenderer & modelRenderer = Engine::GetInstance().GetRenderer().GetModelRenderer();
		for (size_t i = 0; i < myMeshes.size(); i++)
		{
			InstanceData tempInstanceData;
			tempInstanceData.myMatrix = aMatrix;
			tempInstanceData.myColor = aColor;
			tempInstanceData.myLastFrameMatrix = aLastFrameMatrix;
			modelRenderer.Render(aEffect, myMeshes[i], tempInstanceData);
		}
	}


	void Model::InstantRender(const std::shared_ptr<Effect>& aEffect, const Matrix44f & aWorldMatrix, const Matrix44f & aOldMatrix, const Vector4f & aColor) const
	{
		ModelRenderer & modelRenderer = Engine::GetInstance().GetRenderer().GetModelRenderer();
		InstanceData tempInstanceData;
		tempInstanceData.myMatrix = aWorldMatrix;
		tempInstanceData.myColor = aColor;
		tempInstanceData.myLastFrameMatrix = aOldMatrix;

		modelRenderer.PrepareInstantRender(tempInstanceData);

		for (size_t i = 0; i < myMeshes.size(); i++)
		{

			modelRenderer.InstantRender(aEffect, myMeshes[i]);
		}
	}

	ResourceStatus Model::GetLoadStatus() const
	{
		return ResourceStatus::eReady;
	}

	bool Model::MakeReady(bool aLoadAsynchronously)
	{
		return true;
	}

	void Model::AddMesh(const std::shared_ptr<GenericMesh> & aMesh)
	{
		myMeshes.push_back(aMesh);

		BoundingBoxf bb = aMesh->GetBoundingBox();
		if (myMeshes.size() == 0)
		{
			myBoundingBox.SetToPosition(bb.GetCenter());
		}
		myBoundingBox.ExpandToContain(bb);
	}

	void Model::Reset()
	{
		myMeshes.clear();
		myBoundingBox = BoundingBoxf();
	}

	const std::vector<std::shared_ptr<GenericMesh>> & Model::GetMeshes() const
	{
		return myMeshes;
	}

	const BoundingBoxf & Model::GetBoundingBox() const
	{
		return myBoundingBox;
	}
}
