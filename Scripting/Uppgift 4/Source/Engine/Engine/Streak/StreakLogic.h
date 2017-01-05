#pragma once

namespace SB
{
	class StreakLogic
	{
	public:
		virtual ~StreakLogic();
		virtual void SaveToJson(JsonSerializer &aSerializer)const {}
		virtual float CalculateSize(float aProgress) = 0;
		virtual Vector4f CalculateColor(float aProgress) = 0;
	};

	class UnityStreakLogic : public StreakLogic
	{
	public:
		UnityStreakLogic(DataNode aNode);
		UnityStreakLogic(const GrowingArray<Vector4f> & aColors, const GrowingArray<float> & aSizes);
		float CalculateSize(float progress) override;
		Vector4f CalculateColor(float progress) override;

		void SaveToJson(JsonSerializer &aSerializer)const override;
	private:
		GrowingArray<Vector4f> myColors;
		GrowingArray<float> mySizes;
	};
	
	class ConstantStreakProperties : public StreakLogic
	{
	public:
		ConstantStreakProperties(const Vector3f & aColor, float aSize);
		float CalculateSize(float aProgress) override;
		Vector4f CalculateColor(float aProgress) override;
		
	private:
		Vector3f myColor;
		float mySize;
	};
}
