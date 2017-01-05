#pragma once

enum class TextureFormat
{
	eUnorm8,
	eFloat16
};

namespace SB
{
	class EngineSettings
	{
	public:
		EngineSettings(DataNode aSettingsData);
		~EngineSettings();

		inline const Vector2us& GetResolution() const
		{
			return myResolution;
		}
		inline bool GetStartInFullscreen() const
		{
			return myStartInFullscreen;
		}
		inline bool GetUsePostProcessing() const
		{
			return myUsePostProcessing;
		}
		inline bool GetUseHDR() const
		{
			return myUseHDR;
		}
		inline bool GetUseBloom() const
		{
			return myUseBloom;
		}
		inline bool GetUseMotionBlur() const
		{
			return myUseMotionBlur;
		}

		inline void SetHasHDR(bool aValue)
		{
			myUseHDR = aValue;
		}
		inline void SetHasBloom(bool aValue)
		{
			myUseBloom = aValue;
		}
		inline void SetHasMotionBlur(bool aValue)
		{
			myUseMotionBlur = aValue;
		}

		inline void ToggleHDR()
		{
			myUseHDR = !myUseHDR;
		}
		inline void ToggleBloom()
		{
			myUseBloom = !myUseBloom;
		}
		inline void ToggleMotionBlur()
		{
			myUseMotionBlur = !myUseMotionBlur;
		}
		TextureFormat GetRenderingFormat() const;

	private:
		Vector2us myResolution;
		bool myStartInFullscreen;
		bool myUsePostProcessing;
		bool myUseHDR;
		bool myUseBloom;
		bool myUseMotionBlur;
	};
}
