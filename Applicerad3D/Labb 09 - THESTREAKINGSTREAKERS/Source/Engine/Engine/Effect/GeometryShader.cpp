#include "stdafx.h"
#include "GeometryShader.h"
#include "Engine\Effect\VertexShader.h"
#include "Engine\Rendering\DXRenderer.h"
#include <d3d11.h>
#include "Engine\Effect\InputLayout.h"

namespace ENGINE_NAMESPACE
{

	GeometryShader::GeometryShader(const std::string & aFileName, const char * aEntryPoint) : Shader(aFileName)
	{
		myGeometryShader = nullptr;
		myBlob = nullptr;
		myEntryPoint = aEntryPoint;

		Reload();
	}


	GeometryShader::~GeometryShader()
	{
		SAFE_RELEASE(myGeometryShader);
		SAFE_RELEASE(myBlob);
	}

	void GeometryShader::Bind() const
	{
		Engine::GetInstance().GetRenderer().GetContext()->GSSetShader(myGeometryShader, nullptr, 0);
	}

	void GeometryShader::Reload()
	{
		SAFE_RELEASE(myGeometryShader);
		SAFE_RELEASE(myBlob);

		ID3D10Blob * blob = CreateShader(GetPath(), myEntryPoint, "gs_5_0");

		CheckDXError(
			Engine::GetInstance().GetRenderer().GetDevice()->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &myGeometryShader);
		);

		myBlob = blob;
	}

	ID3D11InputLayout * GeometryShader::CreateLayout(const InputLayout & aLayoutDescription)
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
