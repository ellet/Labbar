#pragma once

namespace ENGINE_NAMESPACE
{
	class AssimpModel;

	template<>
	class ResourceLoader<AssimpModel>
	{
	public:
		static AssimpModel * Load(const std::string & aPath, LoadError & aError);
	};
}
