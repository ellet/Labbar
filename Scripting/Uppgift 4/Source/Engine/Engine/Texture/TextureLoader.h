#pragma once

namespace SB
{
	class Texture;
	class TextureCube;

	template<>
	class ResourceLoader<Texture>
	{
	public:
		static Texture * Load(const std::string & aPath, LoadError & aError);
	};

	template<>
	class ResourceLoader<TextureCube>
	{
	public:
		static TextureCube * Load(const std::string & aPath, LoadError & aError);
	};
}
