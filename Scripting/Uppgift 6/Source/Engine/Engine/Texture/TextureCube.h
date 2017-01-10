#pragma once

struct ID3D11ShaderResourceView;

namespace SB
{
	class TextureCube : public AsynchronousResource
	{
	public:
		TextureCube(const std::string & aPath);
		~TextureCube();

		void BindToVS(int aSlot) const;
		void BindToPS(int aSlot) const;
		void BindToGS(int aSlot) const;
		void BindToCS(int aSlot) const;
		void BindToHS(int aSlot) const;
		void BindToDS(int aSlot) const;

		void Reload() override;
		void Load() override;

		int GetMipMapLevels() const;

	private:
		ID3D11ShaderResourceView * myTextureView;
		int myMipMapLevels;
	};
}
