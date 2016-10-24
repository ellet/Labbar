#pragma once

namespace ENGINE_NAMESPACE
{
	class Texture;

	template<>
	class ResourceLoader<Texture>
	{
	public:
		static Texture * Load(const std::string & aPath, LoadError & aError);
	};
}
