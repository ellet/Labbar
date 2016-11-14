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

namespace ENGINE_NAMESPACE
{
	Effect::Effect()
	{
		myVertexShader = nullptr;
		myPixelShader = nullptr;
		myGeometryShader = nullptr;
		myLayout = nullptr;

		myIsLinked = false;
	}

	Effect::~Effect()
	{
		if (myLayout != nullptr)
		{
			myLayout->Release();
			myLayout = nullptr;
		}
	}

	void Effect::AttachVertexShader(const std::string & aFileName, const char * aEntryPoint)
	{
		assert("Effect already linked" && myIsLinked == false);
		assert("Vertex shader already attached" && myVertexShader == nullptr);
		myVertexShader = Engine::GetResourceManager().Get<ShaderFile>(aFileName, nullptr, true)->GetVertexShader(aEntryPoint);
	}

	void Effect::AttachPixelShader(const std::string & aFileName, const char * aEntryPoint)
	{
		assert("Effect already linked" && myIsLinked == false);
		assert("Pixel shader already attached" && myPixelShader == nullptr);
		myPixelShader = Engine::GetResourceManager().Get<ShaderFile>(aFileName, nullptr, true)->GetPixelShader(aEntryPoint);
	}

	void Effect::AttachGeometryShader(const std::string & aFileName, const char * aEntryPoint)
	{
		assert("Effect already linked" && myIsLinked == false);
		assert("Geometry shader already attached" && myGeometryShader == nullptr);
		myGeometryShader = Engine::GetResourceManager().Get<ShaderFile>(aFileName, nullptr, true)->GetGeometryShader(aEntryPoint);
	}

	void Effect::Link(const InputLayout & aLayoutDescription)
	{
		assert("Effect already linked" && myIsLinked == false);

		if (myVertexShader != nullptr)
		{
			myLayout = myVertexShader->CreateLayout(aLayoutDescription);
		}

		myIsLinked = true;
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
			Engine::GetInstance().GetRenderer().GetContext()->IASetInputLayout(myLayout);
		}
		else
		{
			Engine::GetInstance().GetRenderer().GetContext()->IASetInputLayout(nullptr);
		}
	}
}
