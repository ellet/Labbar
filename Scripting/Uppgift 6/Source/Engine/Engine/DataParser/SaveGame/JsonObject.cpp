#include "stdafx.h"
#include "JsonObject.h"


namespace SB
{
	JsonObject::JsonObject(bool aIsConstructedThroughJson /*= false*/)
	{
		myShouldBeSaved = aIsConstructedThroughJson;
	}

	JsonObject::~JsonObject()
	{
	}

	//Write the JsonObject to the current save game scene
	void JsonObject::ToJson(JsonSerializer &aSerializer) const
{
		if (myShouldBeSaved == true)
		{			
			Error("Json Object wants to be saved but doesn't save anything. Fix that plz");
		}
	}


	void JsonObject::SetShouldBeSaved(bool aShouldBeSaved)
	{
		myShouldBeSaved = aShouldBeSaved;
	}

	bool JsonObject::GetShouldBeSaved() const
	{
		return myShouldBeSaved;
	}

}