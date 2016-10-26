#pragma once

namespace
ENGINE_NAMESPACE
{
	class ShaderFile;

	template<>
	class ResourceLoader<ShaderFile>
	{
	public:
		static ShaderFile * Load(const std::string & aPath, LoadError & aError);
	};
}
