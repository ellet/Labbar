#pragma once


namespace ENGINE_NAMESPACE
{
	class JsonObject
	{
	public:
		JsonObject(bool aIsConstructedThroughJson = false);
		virtual ~JsonObject();

		virtual void ToJson()const;

		void SetShouldBeSaved(bool aShouldBeSaved);
		bool GetShouldBeSaved()const;
	protected:
		bool myShouldBeSaved;
	};


}