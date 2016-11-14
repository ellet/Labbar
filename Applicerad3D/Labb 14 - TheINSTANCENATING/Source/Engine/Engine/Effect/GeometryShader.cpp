#include "stdafx.h"
#include "GeometryShader.h"

namespace ENGINE_NAMESPACE
{
	GeometryShader::GeometryShader(const std::string & aFileName, const char * aEntryPoint)
		: Shader(aFileName)
	{
		myEntryPoint = aEntryPoint;
		myShader = nullptr;

		ID3D10Blob * blob = CreateShader(aFileName, aEntryPoint, "gs_5_0");

		CheckDXError(
			Engine::GetInstance().GetRenderer().GetDevice()->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &myShader);
		);

		blob->Release();
		blob = nullptr;
	}

	GeometryShader::~GeometryShader()
	{
		SAFE_RELEASE(myShader);
	}

	void GeometryShader::Bind() const
	{
		Engine::GetInstance().GetRenderer().GetContext()->GSSetShader(myShader, nullptr, 0);
	}

	void GeometryShader::Reload()
	{
		SAFE_RELEASE(myShader);

		ID3D10Blob * blob = CreateShader(GetPath(), myEntryPoint.c_str(), "gs_5_0");

		CheckDXError(
			Engine::GetInstance().GetRenderer().GetDevice()->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &myShader);
		);
	}

}