#include "stdafx.h"
#include "Engine\Model\Surface.h"
#include "Engine/Texture\TextureCube.h"

std::unique_ptr<TextureCube> Surface::ourCube = nullptr;

Surface::Surface()
{
	if (ourCube == nullptr)
	{
		ourCube = std::make_unique<TextureCube>("Textures/cubeMap.dds");
	}
}

void Surface::BindToPS() const
{
	BindSlotToPS(static_cast<int>(SurfaceTextureIndex::eDiffuse));
	BindSlotToPS(static_cast<int>(SurfaceTextureIndex::eSpecular));
	BindSlotToPS(static_cast<int>(SurfaceTextureIndex::eAmbientOcclusion));
	BindSlotToPS(static_cast<int>(SurfaceTextureIndex::eEmissive));
	BindSlotToPS(static_cast<int>(SurfaceTextureIndex::eNormal));
	BindSlotToPS(static_cast<int>(SurfaceTextureIndex::eMetalness));
	if (ourCube != nullptr)
	{
		ourCube->BindToPS(6);
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
	myTextures[static_cast<int>(aSlot)] = aTexture;
}
