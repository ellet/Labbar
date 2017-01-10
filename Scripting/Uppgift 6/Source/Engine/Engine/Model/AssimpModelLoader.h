#pragma once

namespace SB
{
	class AssimpModel;

	template<>
	class ResourceLoader<AssimpModel>
	{
	public:
		static AssimpModel * Load(const std::string & aPath, LoadError & aError);
	};
}
