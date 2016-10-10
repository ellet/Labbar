#pragma once
#include "Engine\Effect\Shader.h"

struct ID3D11GeometryShader;
struct ID3D11InputLayout;
struct ID3D10Blob;

namespace ENGINE_NAMESPACE
{
	class GeometryShader : public Shader
	{
	public:
		GeometryShader(const std::string & aFileName, const char * aEntryPoint);
		~GeometryShader();

		void Bind() const override;
		void Reload() override;

		ID3D11InputLayout * CreateLayout(const InputLayout & aLayoutDescription);

	private:
		const char* myEntryPoint;
		ID3D11GeometryShader* myGeometryShader;
		ID3D10Blob * myBlob;
	};
}

