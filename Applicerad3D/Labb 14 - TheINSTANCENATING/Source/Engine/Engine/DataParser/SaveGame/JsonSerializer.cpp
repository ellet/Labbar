#include "stdafx.h"
#include "JsonSerializer.h"

namespace ENGINE_NAMESPACE
{
	JsonSerializer::JsonSerializer(const char* aSaveDataPath)
	{
		mySaveDataPath = aSaveDataPath;
		myShouldWriteComma = false;

	}

	JsonSerializer::~JsonSerializer()
	{
	}

	void JsonSerializer::OpenSaveFile()
	{
		mySaveFile.open(mySaveDataPath, std::fstream::out);
		mySaveFile << "{";
		myHierarchy.Push('}');
	}

	/*void JsonSerializer::WriteStringToSaveFile(const char* aWriteData)
	{
		mySaveFile << aWriteData;
	}*/

	void JsonSerializer::CloseSaveFile()
	{
		myShouldWriteComma = false;

		while (myHierarchy.Size() > 0)
		{
			mySaveFile << myHierarchy.Pop();
		}

		mySaveFile.close();
	}

	//Start writing an object of aName
	void JsonSerializer::WriteObject(const char* aName)
	{
		TryWriteComma();
		mySaveFile << "\"";
		mySaveFile << aName;
		mySaveFile << "\":{";
		myHierarchy.Push('}');
	}

	void JsonSerializer::WriteObject()
	{
		TryWriteComma();
		mySaveFile << "{";
		myHierarchy.Push('}');
	}

	//Start writing an array of aName
	void JsonSerializer::WriteArray(const char* aName)
	{
		TryWriteComma();
		mySaveFile << "\"";
		mySaveFile << aName;
		mySaveFile << "\":[";

		myHierarchy.Push(']');
	}

	void JsonSerializer::WriteArray()
	{
		mySaveFile << "[";

		myHierarchy.Push(']');
	}

	//Step out of current scope
	void JsonSerializer::StepOut()
	{
		myShouldWriteComma = true;
		mySaveFile << myHierarchy.Pop();
	}


	//PRIVATE FUNCTIONS:

	void JsonSerializer::WriteValue(const bool aBool)
	{
		mySaveFile << (aBool ? "true" : "false");
	}

	void JsonSerializer::WriteValue(const char* aString)
	{
		mySaveFile << "\"";
		int stringIndex = 0;
		while (aString[stringIndex] != '\0')
		{
			char curChar = aString[stringIndex];

			if (curChar == '\"' || curChar == '\\')
				mySaveFile << '\\';


			mySaveFile << aString[stringIndex];
			stringIndex++;
		}
		mySaveFile << "\"";
	}

	void JsonSerializer::WriteValue(const std::string &aString)
	{
		WriteValue(aString.c_str());
	}

	void JsonSerializer::WriteValue(const Vector3f &aVector3)
	{
		mySaveFile << "[";
		WriteValue(aVector3.x);
		mySaveFile << ",";
		WriteValue(aVector3.y);
		mySaveFile << ",";
		WriteValue(aVector3.z);
		mySaveFile << "]";
	}

	void JsonSerializer::WriteValue(const Vector4f &aVector4)
	{
		mySaveFile << "[";
		WriteValue(aVector4.x);
		mySaveFile << ",";
		WriteValue(aVector4.y);
		mySaveFile << ",";
		WriteValue(aVector4.z);
		mySaveFile << ",";
		WriteValue(aVector4.w);
		mySaveFile << "]";
	}

	void JsonSerializer::TryWriteComma()
	{
		if (myShouldWriteComma == true)
		{
			mySaveFile << ",";
		}
		myShouldWriteComma = false;
	}

}
