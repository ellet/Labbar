#include "stdafx.h"
#include "Engine\Model\Model.h"
#include "Engine\Effect\Effect.h"
#include "Engine\Model\Mesh.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Rendering\ModelRenderer.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Texture/RenderTexture.h"
#include "Engine/Texture/WorldRenderTexture.h"

namespace
SB
{
	Model::Model()
	{
		myShouldRender = true;
	}

	Model::Model(const std::shared_ptr<GenericMesh>& aMesh)
	{
		myShouldRender = true;

		AddMesh(aMesh);
	}

	Model::~Model()
	{
	}

	void Model::Render(const Camera & aCamera, const std::shared_ptr<Effect>& aEffect, const Matrix44f& aMatrix, const Matrix44f& aLastFrameMatrix, const Color& aColor, const AnimationPlaybackData * aPlaybackData, uint8_t* aCullingCache, size_t* aLodCache) const
	{
		if (myShouldRender == false)
		{
			return;
		}

		bool hasRenderedMinMax = false;

		size_t lodCache = SIZE_MAX;

		if (aLodCache != nullptr)
		{
			lodCache = *aLodCache;

			if (lodCache != SIZE_MAX)
			{
				if (TryRenderMeshIndex(aCamera, lodCache, aEffect, aMatrix, aLastFrameMatrix, aColor, aCullingCache))
				{
					return;
				}
			}
		}

		const std::shared_ptr<GenericMesh> * lowestLod = nullptr;

		for (size_t i = 0; i < myMeshes.size(); i++)
		{
			if (i == lodCache)
			{
				continue;
			}

			if (myMeshes[i]->HasMinMaxRenderDistance())
			{
				if (hasRenderedMinMax == false)
				{
					if (TryRenderMeshIndex(aCamera, i, aEffect, aMatrix, aLastFrameMatrix, aColor, aCullingCache))
					{
						hasRenderedMinMax = true;
						if (aLodCache != nullptr)
						{
							*aLodCache = i;
						}
					}
					else
					{
						if (lowestLod == nullptr || myMeshes[i]->GetMaximumRenderDistance() > (*lowestLod)->GetMaximumRenderDistance())
						{
							lowestLod = &myMeshes[i];
						}
					}
				}
			}
			else
			{
				TryRenderMeshIndex(aCamera, i, aEffect, aMatrix, aLastFrameMatrix, aColor, aCullingCache);
			}
		}

		if (hasRenderedMinMax == false && lowestLod != nullptr)
		{
			InstanceData tempInstanceData;
			tempInstanceData.myMatrix = aMatrix;
			tempInstanceData.myColor = aColor;
			tempInstanceData.myLastFrameMatrix = aLastFrameMatrix;
			aCamera.GetRenderTexture()->GetModelRenderer().Render(aEffect, *lowestLod, tempInstanceData, aCullingCache);
		}
	}

	bool Model::TryRenderMeshIndex(const Camera & aCamera, size_t i, const std::shared_ptr<Effect>& aEffect, const Matrix44f& aMatrix, const Matrix44f& aLastFrameMatrix, const Color& aColor, uint8_t* aCullingCache) const
	{
		if (myMeshes[i]->HasMinMaxRenderDistance())
		{
			float min = myMeshes[i]->GetMinimumRenderDistance();
			float max = myMeshes[i]->GetMaximumRenderDistance();
			Vector3f origo = Vector4f(0.f, 0.f, 0.f, 1.f) * aMatrix;
			Vector3f maxPoint = Vector4f(max, 0.f, 0.f, 1.f) * aMatrix;
			float adjustedMax = (maxPoint - origo).Length();
			float adjustedMin = adjustedMax * (min / max);
			float distanceToCamera = (aCamera.GetPosition() - origo).Length();

			if (distanceToCamera < adjustedMin || distanceToCamera >= adjustedMax)
			{
				return false;
			}
		}

		InstanceData tempInstanceData;
		tempInstanceData.myMatrix = aMatrix;
		tempInstanceData.myColor = aColor;
		tempInstanceData.myLastFrameMatrix = aLastFrameMatrix;
		aCamera.GetRenderTexture()->GetModelRenderer().Render(aEffect, myMeshes[i], tempInstanceData, aCullingCache);

		return true;
	}

	void Model::InstantRender(const Camera & aCamera, const std::shared_ptr<Effect>& aEffect, const Matrix44f& aWorldMatrix, const Matrix44f& aOldMatrix, const Color& aColor, const AnimationPlaybackData * aPlaybackData) const
	{
		if (myShouldRender == false)
		{
			return;
		}

		InstanceData tempInstanceData;
		tempInstanceData.myMatrix = aWorldMatrix;
		tempInstanceData.myColor = aColor;
		tempInstanceData.myLastFrameMatrix = aOldMatrix;

		aCamera.GetRenderTexture()->GetModelRenderer().PrepareInstantRender(tempInstanceData);

		for (size_t i = 0; i < myMeshes.size(); i++)
		{
			aCamera.GetRenderTexture()->GetModelRenderer().InstantRender(aEffect, myMeshes[i]);
		}
	}

	ResourceStatus Model::GetLoadStatus() const
	{
		bool somethingIsPreparing = false,
			somethingIsReady = false,
			somethingIsRemoved = false,
			somethingHasNotStartedLoading = false;

		for (size_t i = 0; i < myMeshes.size(); i++)
		{
			ResourceStatus status = myMeshes[i]->GetLoadStatus();

			if (status == ResourceStatus::ePreparing)
			{
				somethingIsPreparing = true;
			}
			if (status == ResourceStatus::eReady)
			{
				somethingIsReady = true;
			}
			if (status == ResourceStatus::eNotStartedLoading)
			{
				somethingHasNotStartedLoading = true;
			}
			if (status == ResourceStatus::eRemoved)
			{
				somethingIsRemoved = true;
			}
		}

		if (somethingIsPreparing)
		{
			return ResourceStatus::ePreparing;
		}
		if (somethingIsRemoved)
		{
			return ResourceStatus::eRemoved;
		}
		if (somethingIsReady)
		{
			return ResourceStatus::eReady;
		}
		if (somethingHasNotStartedLoading)
		{
			return ResourceStatus::eNotStartedLoading;
		}
		Error("Unknown resource status");
	}

	bool Model::MakeReady(bool aLoadAsynchronously)
	{
		bool isReady = true;
		for (size_t i = 0; i < myMeshes.size(); i++)
		{
			if (myMeshes[i]->Prepare(aLoadAsynchronously) == false)
			{
				isReady = false;
			}
		}
		return isReady;
	}

	void Model::AddMesh(const std::shared_ptr<GenericMesh>& aMesh)
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

	const std::vector<std::shared_ptr<GenericMesh>>& Model::GetMeshes() const
	{
		return myMeshes;
	}

	const BoundingBoxf& Model::GetBoundingBox() const
	{
		return myBoundingBox;
	}
}
