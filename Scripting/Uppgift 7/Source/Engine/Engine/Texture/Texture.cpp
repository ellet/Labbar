#include "stdafx.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\DXHelpers\DDSTextureLoader.h"
#include "Engine\DXHelpers\dds.h"

namespace SB
{
	Texture::Texture(unsigned int aWidth, unsigned int aHeight, DXGI_FORMAT aFormat, bool aIsRenderTarget)
		: AsynchronousResource("[Dynamic Render Target]")
	{
		myWidth = aWidth;
		myHeight = aHeight;

		D3D11_TEXTURE2D_DESC textureDesc;

		textureDesc.Width = aWidth;
		textureDesc.Height = aHeight;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = aFormat;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.MiscFlags = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | (aIsRenderTarget ? D3D11_BIND_RENDER_TARGET : 0);
		textureDesc.CPUAccessFlags = 0;
		
		CheckDXError(
			Engine::GetInstance().GetRenderer().GetDevice()->CreateTexture2D(&textureDesc, nullptr, &myTexture)
		);

		CheckDXError(
			Engine::GetInstance().GetRenderer().GetDevice()->CreateShaderResourceView(myTexture, nullptr, &myTextureView);
		);

		SetStatus(ResourceStatus::eReady);

	}

	Texture::Texture(const std::string & aPath)
		: AsynchronousResource(aPath)
	{
		myTexture = nullptr;
		myTextureView = nullptr;
	}

	Texture::Texture(ID3D11Texture2D* aTexture, ID3D11ShaderResourceView* aResourceView, int aWidth, int aHeight)
		: AsynchronousResource("[Back Buffer]")
	{
		myTexture = aTexture;
		myTexture->AddRef();
		myTextureView = aResourceView;
		myTextureView->AddRef();
		myWidth = aWidth;
		myHeight = aHeight;
		SetStatus(ResourceStatus::eReady);
	}

	Texture::~Texture()
	{
		SAFE_RELEASE(myTextureView);
		SAFE_RELEASE(myTexture);
	}

	void Texture::BindToVS(int aSlot) const
	{
		const_cast<Texture*>(this)->Prepare(false);
		Engine::GetInstance().GetRenderer().GetContext()->VSSetShaderResources(aSlot, 1, &myTextureView);
	}

	void Texture::BindToPS(int aSlot) const
	{
		const_cast<Texture*>(this)->Prepare(false);
		Engine::GetInstance().GetRenderer().GetContext()->PSSetShaderResources(aSlot, 1, &myTextureView);
	}

	void Texture::BindToGS(int aSlot) const
	{
		const_cast<Texture*>(this)->Prepare(false);
		Engine::GetInstance().GetRenderer().GetContext()->GSSetShaderResources(aSlot, 1, &myTextureView);
	}

	void Texture::BindToCS(int aSlot) const
	{
		const_cast<Texture*>(this)->Prepare(false);
		Engine::GetInstance().GetRenderer().GetContext()->CSSetShaderResources(aSlot, 1, &myTextureView);
	}

	void Texture::BindToHS(int aSlot) const
	{
		const_cast<Texture*>(this)->Prepare(false);
		Engine::GetInstance().GetRenderer().GetContext()->HSSetShaderResources(aSlot, 1, &myTextureView);
	}

	void Texture::BindToDS(int aSlot) const
	{
		const_cast<Texture*>(this)->Prepare(false);
		Engine::GetInstance().GetRenderer().GetContext()->DSSetShaderResources(aSlot, 1, &myTextureView);
	}

	

	ID3D11Texture2D* Texture::GetTexture()
	{
		return myTexture;
	}

	ID3D11ShaderResourceView* Texture::GetView() const
	{
		return myTextureView;
	}

	void Texture::Reload()
	{
		SAFE_RELEASE(myTextureView);
		SAFE_RELEASE(myTexture);

		DirectX::DDS_HEADER header;

		const std::string & path = GetPath();

		ID3D11Resource * texture;

		HRESULT res = DirectX::CreateDDSTextureFromFile(Engine::GetInstance().GetRenderer().GetDevice(), std::wstring(path.begin(), path.end()).c_str(), &texture, &myTextureView, &header);

		if (res != S_OK)
		{
			Error(FormatString("Failed to load DDS texture \"{0}\".", path).c_str());
		}
		
		CheckDXError(
			texture->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&myTexture))
		);

		// QueryInterface calls AddRef, get rid of our old reference
		SAFE_RELEASE(texture);

		myWidth = header.width;
		myHeight = header.height;

		if (myTexture == nullptr)
		{
			Error("Only 2D-textures are supported!");
			return;
		}
	}

	void Texture::Load()
	{
		Reload();
	}

	void Texture::UnbindFromVS(int aSlot) const
	{
		ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
		Engine::GetInstance().GetRenderer().GetContext()->VSSetShaderResources(aSlot, 1, nullSRV);
	}

	void Texture::UnbindFromPS(int aSlot) const
	{
		ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
		Engine::GetInstance().GetRenderer().GetContext()->PSSetShaderResources(aSlot, 1, nullSRV);
	}

	void Texture::UnbindFromGS(int aSlot) const
	{
		ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
		Engine::GetInstance().GetRenderer().GetContext()->GSSetShaderResources(aSlot, 1, nullSRV);
	}

	void Texture::UnbindFromCS(int aSlot) const
	{
		ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
		Engine::GetInstance().GetRenderer().GetContext()->CSSetShaderResources(aSlot, 1, nullSRV);
	}

	void Texture::UnbindFromHS(int aSlot) const
	{
		ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
		Engine::GetInstance().GetRenderer().GetContext()->HSSetShaderResources(aSlot, 1, nullSRV);
	}

	void Texture::UnbindFromDS(int aSlot) const
	{
		ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
		Engine::GetInstance().GetRenderer().GetContext()->DSSetShaderResources(aSlot, 1, nullSRV);
	}

}
