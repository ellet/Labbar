#pragma once
#include <fstream>


namespace ENGINE_NAMESPACE
{
	class JsonSerializer
	{
	public:
		JsonSerializer(const char* aSaveDataPath);
		~JsonSerializer();

		void OpenSaveFile();
		//void WriteStringToSaveFile(const char* aWriteData);
		void CloseSaveFile();


		//Json Write functions
		void WriteObject(const char* aName);
		void WriteObject();
		void WriteArray(const char* aName);
		void WriteArray();
		void StepOut();
		template <typename TValueType>
		void WriteNode(const char* aName, const TValueType &aValue);
		template <typename TValueType>
		void WriteArrayValue(const TValueType &aValue);


		inline const std::string &GetSaveDataPath() const
		{
			return mySaveDataPath;
		}

	private:

		void WriteValue(const bool aBool);

		template <typename TValueType>
		void WriteValue(const TValueType &aValue);

		void WriteValue(const char* aString);
		void WriteValue(const std::string &aString);
		void WriteValue(const Vector3f &aVector3);
		void WriteValue(const Vector4f &aVector4);

		std::fstream mySaveFile;
		std::string mySaveDataPath;
		bool myHasWrittenTrailingObject;
		Stack<char> myHierarchy;

		bool myShouldWriteComma;
		void TryWriteComma();
	};

	template <typename TValueType>
	void JsonSerializer::WriteNode(const char* aName, const TValueType &aValue)
	{
		TryWriteComma();

		mySaveFile << "\"";
		mySaveFile << aName;
		mySaveFile << "\":";
		myShouldWriteComma = true;
		WriteValue(aValue);
	}

	template <typename TValueType>
	void JsonSerializer::WriteArrayValue(const TValueType &aValue)
	{
		TryWriteComma();
		WriteValue(aValue);
		myShouldWriteComma = true;
	}

	template <typename TValueType>
	void JsonSerializer::WriteValue(const TValueType &aValue)
	{
		mySaveFile << std::to_string(aValue).c_str();
	}

}

