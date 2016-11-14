#include "stdafx.h"
#include "JsonObject.h"


namespace ENGINE_NAMESPACE
{
	JsonObject::JsonObject(bool aIsConstructedThroughJson /*= false*/)
	{
		myShouldBeSaved = aIsConstructedThroughJson;
	}

	JsonObject::~JsonObject()
	{
	}

	//Write the JsonObject to the current save game scene
	void JsonObject::ToJson() const
	{
		if (myShouldBeSaved == true)
		{
			SB::Engine::GetJsonSerializer().CloseSaveFile();


			
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