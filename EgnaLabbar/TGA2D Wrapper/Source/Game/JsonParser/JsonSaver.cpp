#include "stdafx.h"
#include "JsonSaver.h"
#include <fstream>


JsonSaver::JsonSaver()
{
}

void JsonSaver::SaveToFile(CommonUtilities::GrowingArray<Border> aBorderList, std::string aLevelName)
{
	std::string saveString = "JSON/Levels/" + aLevelName + "/borders.json";
	std::ofstream output(saveString);

	output << "{"
		<< "\n\t\"BorderObjects\" :"
		<< "\n\t\t[";
	for (unsigned short i = 0; i < aBorderList.Size(); ++i)
	{
		if (i < aBorderList.Size()-1)
		{
			output << "\n\t\t\t{"
				<< "\n\t\t\t\t\"XPosition1\" : " << aBorderList[i].GetNode1().x
				<< ",\n\t\t\t\t\"YPosition1\" : " << aBorderList[i].GetNode1().y
				<< ",\n\t\t\t\t\"XPosition2\" : " << aBorderList[i].GetNode2().x
				<< ",\n\t\t\t\t\"YPosition2\" : " << aBorderList[i].GetNode2().y
				<< "\n\t\t\t},";
		}
		else
		{
			output << "\n\t\t\t{"
				<< "\n\t\t\t\t\"XPosition1\" : " << aBorderList[i].GetNode1().x
				<< ",\n\t\t\t\t\"YPosition1\" : " << aBorderList[i].GetNode1().y
				<< ",\n\t\t\t\t\"XPosition2\" : " << aBorderList[i].GetNode2().x
				<< ",\n\t\t\t\t\"YPosition2\" : " << aBorderList[i].GetNode2().y
				<< "\n\t\t\t}";
		}
	}
	output << "\n\t\t]"
		<< "\n}";
	output.flush();
}

JsonSaver::~JsonSaver()
{
}
