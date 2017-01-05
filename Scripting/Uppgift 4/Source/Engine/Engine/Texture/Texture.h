#pragma once
#include <dxgiformat.h>

struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;

namespace SB
{
	class Texture : public AsynchronousResource
	{
	public:
		Texture(unsigned int aWidth, unsigned int aHeight, DXGI_FORMAT aFormat = DXGI_FORMAT_R8G8B8A8_UNORM, bool aIsRenderTarget = false);
		Texture(const std::string & aPath);
		Texture(ID3D11Texture2D * aTexture, ID3D11ShaderResourceView * aResourceView, int aWidth, int aHeight);
		~Texture();

		void BindToVS(int aSlot) const;
		void BindToPS(int aSlot) const;
		void BindToGS(int aSlot) const;
		void BindToCS(int aSlot) const;
		void BindToHS(int aSlot) const;
		void BindToDS(int aSlot) const;

		void UnbindFromVS(int aSlot) const;
		void UnbindFromPS(int aSlot) const;
		void UnbindFromGS(int aSlot) const;
		void UnbindFromCS(int aSlot) const;
		void UnbindFromHS(int aSlot) const;
		void UnbindFromDS(int aSlot) const;

		ID3D11Texture2D * GetTexture();
		ID3D11ShaderResourceView * GetView() const;

		void Reload() override;
		void Load() override;
		Vector2f GetSize() const;

	private:
		ID3D11Texture2D * myTexture;
		ID3D11ShaderResourceView * myTextureView;
		int myWidth;
		int myHeight;
	};

	inline Vector2f Texture::GetSize() const
	{
		const_cast<Texture*>(this)->Prepare(false);
		return Vector2f(static_cast<float>(myWidth), static_cast<float>(myHeight));
	}
}
