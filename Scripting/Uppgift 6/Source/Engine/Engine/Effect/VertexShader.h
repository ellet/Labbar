#pragma once
#include "Engine\Effect\Shader.h"

struct ID3D11VertexShader;
struct ID3D11InputLayout;

namespace SB
{
	class InputLayout;

	class VertexShader : public Shader
	{
	public:
		VertexShader(const std::string & aFileName, const char * aEntryPoint, const InputLayout & aInputLayout);
		~VertexShader();

		void Bind() const override;
		void Reload() override;

	private:
		ID3D11InputLayout * CreateLayout(const InputLayout & aLayoutDescription);

		std::string myEntryPoint;
		ID3D11VertexShader * myShader;
		ID3D10Blob * myBlob;
		InputLayout myInputLayout;
		ID3D11InputLayout * myD3DInputLayout;
	};
}
