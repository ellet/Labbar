#include "stdafx.h"
#include "EngineSettings.h"

namespace SB
{
	EngineSettings::EngineSettings(DataNode aSettingsData)
	{
		myResolution = Vector2us(aSettingsData["resolution"][0].GetUnsignedShort(), aSettingsData["resolution"][1].GetUnsignedShort());
		myStartInFullscreen = aSettingsData["startInFullscreen"].GetBool();
		myUsePostProcessing = aSettingsData["enablePostProcessing"].GetBool();
		myUseBloom = aSettingsData["enableBloom"].GetBool();
		myUseHDR = aSettingsData["enableHDR"].GetBool();
		myUseMotionBlur = aSettingsData["enableMotionBlur"].GetBool();
	}

	EngineSettings::~EngineSettings()
	{
	}

	TextureFormat EngineSettings::GetRenderingFormat() const
	{
		if (myUseHDR == true)
		{
			return TextureFormat::eFloat16;
		}

		return TextureFormat::eUnorm8;
	}

}
