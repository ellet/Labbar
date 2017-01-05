#include "stdafx.h"
#include "Engine\Effect\VertexShader.h"
#include "Engine\Rendering\DXRenderer.h"
#include <d3d11.h>
#include "Engine\Effect\InputLayout.h"

namespace SB
{
	VertexShader::VertexShader(const std::string & aFileName, const char * aEntryPoint, const InputLayout & aInputLayout)
		: Shader(aFileName)
	{
		myInputLayout = aInputLayout;
		myEntryPoint = aEntryPoint;
		myShader = nullptr;
		myBlob = nullptr;

		Prepare(true);
		
	}

	VertexShader::~VertexShader()
	{
		SAFE_RELEASE(myShader);
		SAFE_RELEASE(myBlob);
	}

	void VertexShader::Bind() const
	{
		const_cast<VertexShader*>(this)->Prepare(false);
		Engine::GetInstance().GetRenderer().GetContext()->VSSetShader(myShader, nullptr, 0);
		Engine::GetInstance().GetRenderer().GetContext()->IASetInputLayout(myD3DInputLayout);
	}

	void VertexShader::Reload()
	{
		SAFE_RELEASE(myShader);
		SAFE_RELEASE(myBlob);

		ID3D10Blob * blob = CreateShader(GetPath(), myEntryPoint.c_str(), "vs_5_0");

		CheckDXError(
			Engine::GetInstance().GetRenderer().GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &myShader);
		);

		myBlob = blob;

		myD3DInputLayout = CreateLayout(myInputLayout);
	}
	
	ID3D11InputLayout * VertexShader::CreateLayout(const InputLayout & aLayoutDescription)
	{
		ID3D11InputLayout * layout;

		CheckDXError(
			Engine::GetInstance().GetRenderer().GetDevice()->CreateInputLayout(
				aLayoutDescription.GetLayoutLocation(), aLayoutDescription.GetLayoutCount(),
				myBlob->GetBufferPointer(), myBlob->GetBufferSize(),
				&layout
			)
		);

		return layout;
	}
}
