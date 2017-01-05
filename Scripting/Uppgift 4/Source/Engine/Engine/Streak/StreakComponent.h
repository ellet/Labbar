#pragma once
#include "Engine/Component/BaseComponent.h"
#include <Utilities/Randomizer/Randomizer.h>

namespace SB
{
	class Effect;
	template <typename T>
	class VertexBuffer;
	struct StreakData;
	class StreakLogic;
	class Text;

	class StreakComponent : public BaseComponent
	{
	public:
		void Initialize() override;
		void Reset();

		StreakComponent();
		~StreakComponent();

		virtual void EndUpdate(const Time & aDeltaTime) override;

		virtual void Render(const Camera & aCamera) const override;

		void LoadData(DataNode aProperties) override;
		void Setup(StreakLogic * aStreakLogic, const Time & aTimeBetweenStreakSegments, int aNumberOfStreakSegments);

		void EnableEmmision();
		void DisableEmmision();

		virtual void ToJson(JsonSerializer &aSerializer) const override;
	private:
		void SpawnStreak();
		StreakData & GetHeadingPoint();
		StreakData& GetBackwardPoint();
		StreakData & GetCurrentPoint();
		StreakData & GetTrailingPoint();
		StreakData & GetSegment(int aRelativeIndexToCurrent);
		unsigned short GetSegmentIndex(int aRelativeIndexToCurrent) const;
		GrowingArray<StreakData> myStreakVertices;
		GrowingArray<Time> myStreakAge;
		std::unique_ptr<StreakLogic> myStreakLogic;

		Randomizer myRandomizer;
		Time travelledTime;
		Vector3f myTrailingForwardPos;
		Vector3f myTrailingForwardVector;

		std::shared_ptr<Effect> myEffect;
		std::shared_ptr<VertexBuffer<StreakData>> myVertexBuffer;

		Vector3f myStartPosition;

		unsigned short myCurrentIndex;
		bool myIsFilled;
		bool myIsSetup;
		Time myTimeBetweenStreakSegments;
		int myNumberOfSegments;

		bool myIsEmitting;
	};
}
