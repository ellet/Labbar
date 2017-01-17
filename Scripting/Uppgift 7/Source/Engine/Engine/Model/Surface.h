#pragma once

namespace SB
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

		bool Prepare(bool aLoadAsynchronously);
		ResourceStatus GetLoadStatus() const;

	private:
		void BindSlotToPS(int aIndex) const;

		std::array<std::shared_ptr<Texture>, static_cast<int>(SurfaceTextureIndex::eCount)> myTextures;
		std::array<std::string, static_cast<int>(SurfaceTextureIndex::eCount)> myTextureName;
	};
}
