#include "stdafx.h"
#include "Engine\Effect\PixelShader.h"
#include "Engine\Rendering\DXRenderer.h"
#include <d3d11.h>

namespace SB
{
	PixelShader::PixelShader(const std::string & aFileName, const char * aEntryPoint)
		: Shader(aFileName)
	{
		myEntryPoint = aEntryPoint;
		myShader = nullptr;

		Prepare(true);
	}

	PixelShader::~PixelShader()
	{
		SAFE_RELEASE(myShader);
	}

	void PixelShader::Bind() const
	{
		const_cast<PixelShader*>(this)->Prepare(false);

		Engine::GetInstance().GetRenderer().GetContext()->PSSetShader(myShader, nullptr, 0);
	}

	void PixelShader::Reload()
	{
		SAFE_RELEASE(myShader);

		ID3D10Blob * blob = CreateShader(GetPath(), myEntryPoint.c_str(), "ps_5_0", myShader != nullptr);

		if (blob != nullptr)
		{
			CheckDXError(
				Engine::GetInstance().GetRenderer().GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &myShader)
			);

			SAFE_RELEASE(blob);
		}
		else
		{
			Engine::GetLogger().LogError("Failed to reload pixel shader {0}", GetPath());
		}
	}
}
