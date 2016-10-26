#pragma once
#include "Engine/Component/BaseComponent.h"
#include <Utilities/Randomizer/Randomizer.h>

namespace ENGINE_NAMESPACE
{
	class Effect;
	template <typename T>
	class VertexBuffer;
	struct StreakData;
	struct StreakLogic;
	class Text;

	class StreakComponent : public BaseComponent
	{
	public:
		void Initialize() override;
		StreakComponent();
		~StreakComponent();

		virtual void Update(const Time & aDeltaTime) override;

		virtual void Render() const override;

		void LoadData(DataNode aProperties) override;
		void Setup(const Vector4f & aColor, float aStreakSize, float aDistanceBetweenStreakSegments, int aNumberOfStreakSegments);

	private:
		void SpawnStreak();
		StreakData & GetHeadingPoint();
		StreakData& GetBackwardPoint();
		StreakData & GetCurrentPoint();
		StreakData & GetTrailingPoint();
		StreakData & GetSegment(int aRelativeIndexToCurrent);
		unsigned short GetSegmentIndex(int aRelativeIndexToCurrent) const;
		GrowingArray<StreakData> myStreakVertices;

		Randomizer myRandomizer;

		std::shared_ptr<Effect> myEffect;
		std::shared_ptr<VertexBuffer<StreakData>> myVertexBuffer;
		Vector4f myColor;

		Vector3f myStartPosition;

		unsigned short myCurrentIndex;
		bool myIsFilled;
		bool myIsSetup;
		float myStreakSize;
		float myDistanceBetweenSegments;
		int myNumberOfSegments;
		std::shared_ptr<Text> myText;
	};
}
