#pragma once

namespace CommonUtilities
{
	namespace CommandLine
	{
		void ParseCommandLines(const CU::GrowingArray<std::string> & aInputToParse);

		void ParseLine(const std::string & aCommand);
	}
}

//class CommandLineManager
//{
//public:
//	CommandLineManager();
//	~CommandLineManager();
//
//	//Init(const std::string & aInputString);
//
//	/*bool HasParameter(const std::string aParameter);
//
//	bool HasArgument(const std::string aParameter, const std::string & aArgument);*/
//
//private:
//	CU::GrowingArray<std::string> myParameters;
//};