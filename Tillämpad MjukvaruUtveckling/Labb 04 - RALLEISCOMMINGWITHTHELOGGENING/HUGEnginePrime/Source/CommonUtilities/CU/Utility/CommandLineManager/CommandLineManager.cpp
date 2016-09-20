#include "stdafx.h"
#include "CommandLineManager.h"

namespace CommonUtilities
{
	namespace CommandLine
	{
		void ParseCommandLines(const CU::GrowingArray<std::string> & aInputToParse)
		{
			for (unsigned short iCommand = 0; iCommand < aInputToParse.Size(); ++iCommand)
			{
				ParseLine(aInputToParse[iCommand]);
			}
		}

		void ParseLine(const std::string & aCommand)
		{
			if (aCommand == "ActivateLog: Input")
			{
				DL_Debug::Debug::GetInstance()->ActivateFilterlog("Input");
			}
		}

	}
}
