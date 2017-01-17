#include "stdafx.h"
#include <d3d11.h>
#include "Engine\Effect\Effect.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Effect\VertexShader.h"
#include "Engine\Effect\PixelShader.h"
#include "Engine\Engine.h"
#include "Engine\Effect\InputLayout.h"
#include "Engine\Effect\GeometryShader.h"
#include "ShaderFile.h"

namespace SB
{
	Effect::Effect()
	{
		myVertexShader = nullptr;
		myPixelShader = nullptr;
		myGeometryShader = nullptr;
		myLayout = nullptr;
	}

	Effect::~Effect()
	{
		if (myLayout != nullptr)
		{
			myLayout->Release();
			myLayout = nullptr;
		}
	}

	void Effect::AttachVertexShader(const std::string & aFileName, const char * aEntryPoint, const InputLayout & aInputLayout)
	{
		assert("Vertex shader already attached" && myVertexShader == nullptr);
		myVertexShader = Engine::GetResourceManager().Get<ShaderFile>(aFileName, nullptr, true)->GetVertexShader(aEntryPoint, aInputLayout);
	}

	void Effect::AttachPixelShader(const std::string & aFileName, const char * aEntryPoint)
	{
		assert("Pixel shader already attached" && myPixelShader == nullptr);
		myPixelShader = Engine::GetResourceManager().Get<ShaderFile>(aFileName, nullptr, true)->GetPixelShader(aEntryPoint);
	}

	void Effect::AttachGeometryShader(const std::string & aFileName, const char * aEntryPoint)
	{
		assert("Geometry shader already attached" && myGeometryShader == nullptr);
		myGeometryShader = Engine::GetResourceManager().Get<ShaderFile>(aFileName, nullptr, true)->GetGeometryShader(aEntryPoint);
	}

	bool Effect::Prepare(bool aLoadAsynchronously)
	{
		bool isReady = true;
		
		if (myGeometryShader != nullptr)
		{
			if (myGeometryShader->Prepare(aLoadAsynchronously) == false)
			{
				isReady = false;
			}
		}
		if (myPixelShader != nullptr)
		{
			if (myPixelShader->Prepare(aLoadAsynchronously) == false)
			{
				isReady = false;
			}
		}
		if (myVertexShader != nullptr)
		{
			if (myVertexShader->Prepare(aLoadAsynchronously) == false)
			{
				isReady = false;
			}
		}

		return isReady;
	}

	void Effect::Bind() const
	{
		if (myVertexShader != nullptr)
		{
			myVertexShader->Bind();
		}
		else
		{
			Engine::GetInstance().GetRenderer().GetContext()->VSSetShader(nullptr, nullptr, 0);
			Engine::GetInstance().GetRenderer().GetContext()->IASetInputLayout(nullptr);
		}

		if (myPixelShader != nullptr)
		{
			myPixelShader->Bind();
		}
		else
		{
			Engine::GetInstance().GetRenderer().GetContext()->PSSetShader(nullptr, nullptr, 0);
		}

		if (myGeometryShader != nullptr)
		{
			myGeometryShader->Bind();
		}
		else
		{
			Engine::GetInstance().GetRenderer().GetContext()->GSSetShader(nullptr, nullptr, 0);
		}

		if (myLayout != nullptr)
		{
		}
		else
		{
		}
	}
}
