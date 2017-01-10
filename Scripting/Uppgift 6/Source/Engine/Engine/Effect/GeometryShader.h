#pragma once
#include "Engine\Effect\Shader.h"

namespace SB
{
	class GeometryShader : public Shader
	{
	public:
		GeometryShader(const std::string & aFileName, const char * aEntryPoint);
		~GeometryShader();

		virtual void Bind() const override;

		virtual void Reload() override;

	private:
		std::string myEntryPoint;
		ID3D11GeometryShader * myShader;
	};

}