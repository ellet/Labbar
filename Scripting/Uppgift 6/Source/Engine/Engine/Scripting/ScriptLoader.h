#pragma once

namespace SB
{
	class ScriptFile;

	template <>
	class ResourceLoader<ScriptFile>
	{
	public:
		static ScriptFile * Load(const std::string & aPath, LoadError & aError);
	};

}
