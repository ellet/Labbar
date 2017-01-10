#pragma once

namespace SB
{
	enum class DebugWindowEnum
	{
		eDebugToggle,
		eSceneWindow,
		enumlength
	};


	inline const std::string & EnumToString(const DebugWindowEnum aEnumToConvert)
	{
		static std::unordered_map<DebugWindowEnum, std::string> TestEnumMapOfStrings =
		{
			{ DebugWindowEnum::eDebugToggle,			"Toggle Functions" },
			{ DebugWindowEnum::eSceneWindow,			"Scene Selector" }
		};

		return TestEnumMapOfStrings[aEnumToConvert];
	}

	typedef StaticList<bool, static_cast<int>(DebugWindowEnum::enumlength)> WindowFlagsList;
}

