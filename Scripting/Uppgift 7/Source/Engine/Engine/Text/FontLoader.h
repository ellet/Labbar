#pragma once

namespace SB
{
	class Font;

	template<>
	class ResourceLoader<Font>
	{
	public:
		static Font * Load(const std::string & aPath, LoadError & aError);
	};

}
