#pragma once

enum class FileExtensionsEnum
{
	eJSON,
	eFBX,
	eDDS,
	eFolder,
	eNotUsed,
	enumlength
};



inline const std::string & EnumToString(const FileExtensionsEnum aEnumToConvert)
{
	static std::unordered_map<FileExtensionsEnum, std::string> TestEnumMapOfStrings =
	{
		{ FileExtensionsEnum::eJSON,		"JSON" },
		{ FileExtensionsEnum::eFBX,			"FBX" },
		{ FileExtensionsEnum::eDDS,			"DDS" },
		{ FileExtensionsEnum::eFolder,		"Folder" }
	};

	return TestEnumMapOfStrings[aEnumToConvert];
}

inline FileExtensionsEnum FileEndingFindEnum(const std::string & aStringToConvert)
{
	static std::unordered_map<std::string, FileExtensionsEnum> TestEnumMapOfStrings =
	{
		{ "json" , FileExtensionsEnum::eJSON },
		{ "fbx" , FileExtensionsEnum::eFBX },
		{ "dds", FileExtensionsEnum::eDDS },
		{ ""	, FileExtensionsEnum::eFolder }
	};

	if (TestEnumMapOfStrings.find(aStringToConvert) != TestEnumMapOfStrings.end())
	{
		return TestEnumMapOfStrings[aStringToConvert];
	}
	else
	{
		return FileExtensionsEnum::eNotUsed;
	}
}

inline const std::string & EnumToFileEnding(const FileExtensionsEnum aEnumToConvert)
{
	static std::unordered_map<FileExtensionsEnum, std::string> TestEnumMapOfStrings =
	{
		{ FileExtensionsEnum::eJSON,		"json" },
		{ FileExtensionsEnum::eFBX,			"fbx" },
		{ FileExtensionsEnum::eDDS,			"dds" },
		{ FileExtensionsEnum::eFolder,		"" }
	};

	if (TestEnumMapOfStrings.find(aEnumToConvert) != TestEnumMapOfStrings.end())
	{
		return TestEnumMapOfStrings[aEnumToConvert];
	}
	else
	{
		return "NotFound";
	}
}
