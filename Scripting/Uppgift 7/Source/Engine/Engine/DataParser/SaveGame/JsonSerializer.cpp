#include "stdafx.h"
#include "JsonSerializer.h"

namespace SB
{
	JsonSerializer::JsonSerializer(const char* aWriteToDataPath)
	{
		myWriteToDataPath = aWriteToDataPath;
		myShouldWriteComma = false;
		OpenSaveFile();
	}

	JsonSerializer::~JsonSerializer()
	{
		CloseSaveFile();
	}

	void JsonSerializer::OpenSaveFile()
	{
		myWriteToFile.open(myWriteToDataPath, std::ifstream::out);
		myWriteToFile << "{";
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
			myWriteToFile << myHierarchy.Pop();
		}

		myWriteToFile.close();
	}

	//Start writing an object of aName
	void JsonSerializer::WriteObject(const char* aName)
	{
		TryWriteComma();
		myWriteToFile << "\"";
		myWriteToFile << aName;
		myWriteToFile << "\":{";
		myHierarchy.Push('}');
	}

	void JsonSerializer::WriteObject()
	{
		TryWriteComma();
		myWriteToFile << "{";
		myHierarchy.Push('}');
	}

	//Start writing an array of aName
	void JsonSerializer::WriteArray(const char* aName)
	{
		TryWriteComma();
		myWriteToFile << "\"";
		myWriteToFile << aName;
		myWriteToFile << "\":[";

		myHierarchy.Push(']');
	}

	void JsonSerializer::WriteArray()
	{
		myWriteToFile << "[";

		myHierarchy.Push(']');
	}

	//Step out of current scope
	void JsonSerializer::StepOut()
	{
		myShouldWriteComma = true;
		myWriteToFile << myHierarchy.Pop();
	}


	//PRIVATE FUNCTIONS:

	void JsonSerializer::WriteValue(const bool aBool)
	{
		myWriteToFile << (aBool ? "true" : "false");
	}

	void JsonSerializer::WriteValue(const char* aString)
	{
		myWriteToFile << "\"";
		int stringIndex = 0;
		while (aString[stringIndex] != '\0')
		{
			char curChar = aString[stringIndex];

			if (curChar == '\"' || curChar == '\\')
				myWriteToFile << '\\';


			myWriteToFile << aString[stringIndex];
			stringIndex++;
		}
		myWriteToFile << "\"";
	}

	void JsonSerializer::WriteValue(const std::string &aString)
	{
		WriteValue(aString.c_str());
	}

	void JsonSerializer::WriteValue(const Vector3f &aVector3)
	{
		myWriteToFile << "[";
		WriteValue(aVector3.x);
		myWriteToFile << ",";
		WriteValue(aVector3.y);
		myWriteToFile << ",";
		WriteValue(aVector3.z);
		myWriteToFile << "]";
	}

	void JsonSerializer::WriteValue(const Vector4f &aVector4)
	{
		myWriteToFile << "[";
		WriteValue(aVector4.x);
		myWriteToFile << ",";
		WriteValue(aVector4.y);
		myWriteToFile << ",";
		WriteValue(aVector4.z);
		myWriteToFile << ",";
		WriteValue(aVector4.w);
		myWriteToFile << "]";
	}

	void JsonSerializer::TryWriteComma()
	{
		if (myShouldWriteComma == true)
		{
			myWriteToFile << ",";
		}
		myShouldWriteComma = false;
	}

}
