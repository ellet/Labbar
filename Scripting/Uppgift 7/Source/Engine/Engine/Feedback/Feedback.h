#pragma once
#include "FeedbackStructs.h"

namespace SB
{
	class Feedback
	{
	public:
		Feedback(const std::string & aFeedbackType);
		~Feedback();

		void Update(const Time & aDeltaTime, const Matrix44f & aTransformation);

		void SetIsPaused(const bool aTrueOrFalse);

	private:
		void InternalUpdate(const Time & aDeltaTime, const Matrix44f & aTransformation);
		void LoadFeedbackTypes();

		static std::unordered_map<std::string, std::shared_ptr<FeedbackSettings>> myFeedbackTypes;
		std::shared_ptr<FeedbackSettings> mySettings;

		Time myCurrentTime;
		Time myTotalLifeTime;
		bool myIsLooping;
		bool myIsPaused;
	};
}