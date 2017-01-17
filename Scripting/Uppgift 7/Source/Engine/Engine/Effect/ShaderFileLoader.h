#pragma once

namespace
SB
{
	class ShaderFile;

	template<>
	class ResourceLoader<ShaderFile>
	{
	public:
		static ShaderFile * Load(const std::string & aPath, LoadError & aError);
	};
}
