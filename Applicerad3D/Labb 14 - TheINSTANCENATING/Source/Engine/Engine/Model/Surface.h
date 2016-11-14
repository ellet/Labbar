#pragma once

namespace ENGINE_NAMESPACE
{
	enum class SurfaceTextureIndex
	{
		eDiffuse,
		eNormal,
		eRoughness,
		eAmbientOcclusion,
		eEmissive,
		eMetalness,

		eCount
	};

	class Texture;

	class Surface
	{
	public:
		Surface();
		void BindToPS() const;

		void SetSlot(const SurfaceTextureIndex aSlot, const std::shared_ptr<Texture> & aTexture);
		const std::shared_ptr<Texture> & GetSlot(const SurfaceTextureIndex aSlot) const;

	private:
		void BindSlotToPS(int aIndex) const;

		std::array<std::shared_ptr<Texture>, static_cast<int>(SurfaceTextureIndex::eCount)> myTextures;
	};
}
