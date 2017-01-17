#include "stdafx.h"
#include "Engine\Model\Surface.h"

namespace SB
{

	Surface::Surface()
	{
		SetSlot(SurfaceTextureIndex::eDiffuse, Engine::GetResourceManager().Get<Texture>("Assets/DefaultMaterials/default_al.dds", nullptr, true));
		SetSlot(SurfaceTextureIndex::eAmbientOcclusion, Engine::GetResourceManager().Get<Texture>("Assets/DefaultMaterials/default_ao.dds", nullptr, true));
		SetSlot(SurfaceTextureIndex::eEmissive, Engine::GetResourceManager().Get<Texture>("Assets/DefaultMaterials/default_em.dds", nullptr, true));
		SetSlot(SurfaceTextureIndex::eMetalness, Engine::GetResourceManager().Get<Texture>("Assets/DefaultMaterials/default_me.dds", nullptr, true));
		SetSlot(SurfaceTextureIndex::eNormal, Engine::GetResourceManager().Get<Texture>("Assets/DefaultMaterials/default_no.dds", nullptr, true));
		SetSlot(SurfaceTextureIndex::eRoughness, Engine::GetResourceManager().Get<Texture>("Assets/DefaultMaterials/default_ro.dds", nullptr, true));
	}

	void Surface::BindToPS() const
	{
		for (int i = 0; i < static_cast<int>(SurfaceTextureIndex::eCount); i++)
		{
			BindSlotToPS(i);
		}
	}

	void Surface::BindSlotToPS(int aIndex) const
	{
		if (myTextures[aIndex] != nullptr)
		{
			myTextures[aIndex]->BindToPS(aIndex);
		}
	}

	void Surface::SetSlot(const SurfaceTextureIndex aSlot, const std::shared_ptr<Texture> & aTexture)
	{
		if (aTexture == nullptr)
		{
			myTextureName[static_cast<int>(aSlot)] = "";
		}
		else
		{
			myTextureName[static_cast<int>(aSlot)] = aTexture->GetPath();
		}
		myTextures[static_cast<int>(aSlot)] = aTexture;
	}

	const std::shared_ptr<Texture>& Surface::GetSlot(const SurfaceTextureIndex aSlot) const
	{
		return myTextures[static_cast<int>(aSlot)];
	}

	bool Surface::Prepare(bool aLoadAsynchronously)
	{
		bool isReady = true;
		for (int i=0; i<static_cast<int>(SurfaceTextureIndex::eCount); i++)
		{
			if (myTextures[i] != nullptr && myTextures[i]->Prepare(aLoadAsynchronously) == false)
			{
				isReady = false;
			}
		}
		return isReady;
	}

	ResourceStatus Surface::GetLoadStatus() const
	{
		bool somethingIsPreparing = false,
			somethingIsReady = false,
			somethingIsRemoved = false,
			somethingHasNotStartedLoading = false;

		for (int i = 0; i<static_cast<int>(SurfaceTextureIndex::eCount); i++)
		{
			if (myTextures[i] != nullptr)
			{
				ResourceStatus status = myTextures[i]->GetStatus();

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
}
