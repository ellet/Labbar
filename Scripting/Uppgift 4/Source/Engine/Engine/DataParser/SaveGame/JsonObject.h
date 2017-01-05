#pragma once


namespace SB
{
	class JsonObject
	{
	public:
		JsonObject(bool aIsConstructedThroughJson = false);
		virtual ~JsonObject();

		virtual void ToJson(JsonSerializer &aSerializer) const;

		void SetShouldBeSaved(bool aShouldBeSaved);
		bool GetShouldBeSaved()const;
	protected:
		bool myShouldBeSaved;
	};


}