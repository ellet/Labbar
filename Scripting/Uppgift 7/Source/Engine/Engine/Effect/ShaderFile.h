#pragma once
#include "Shader.h"
#include <memory>

namespace SB
{
	class ShaderFile : public Resource
	{
	public:
		ShaderFile(const std::string & aPath);
		void Reload() override;

		std::shared_ptr<VertexShader> GetVertexShader(const std::string &aEntryPoint, const InputLayout & aInputLayout);
		std::shared_ptr<PixelShader> GetPixelShader(const std::string& aEntryPoint);
		std::shared_ptr<GeometryShader> GetGeometryShader(const std::string& aEntryPoint);

	private:
		std::shared_ptr<Shader> GetLoadedShader(const std::string& aEntryPoint);

		std::unordered_map<std::string, std::shared_ptr<Shader>> myLoadedShaders;
	};
}
