#pragma once

enum class SurfaceTextureIndex
{
	eDiffuse,
	eSpecular,
	eAmbientOcclusion,
	eEmissive,
	eNormal,
	eMetalness,

	eCount
};

class Texture;
class TextureCube;

class Surface
{
public:
	Surface();
	void BindToPS() const;

	void SetSlot(const SurfaceTextureIndex aSlot, const std::shared_ptr<Texture> & aTexture);

private:
	void BindSlotToPS(int aIndex) const;

	static std::unique_ptr<TextureCube> ourCube;
	std::array<std::shared_ptr<const Texture>, static_cast<int>(SurfaceTextureIndex::eCount)> myTextures;
};
