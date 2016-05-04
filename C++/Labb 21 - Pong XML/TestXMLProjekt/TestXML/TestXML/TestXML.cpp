// TestXML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tinyxml2.h"
#include <string>



int _tmain(int argc, _TCHAR* argv[])
{
	
	tinyxml2::XMLDocument xmlDoc;

	tinyxml2::XMLError checkError = xmlDoc.LoadFile("XMLFiles/derp.xml");

	tinyxml2::XMLElement * daRoot = xmlDoc.FirstChildElement();

	tinyxml2::XMLElement * test = daRoot->FirstChildElement();

	tinyxml2::XMLElement * elementsinTest = test->FirstChildElement();

	std::string derpererererp = test->Name();

	std::string testString = elementsinTest->GetText();

	float derp = 0.3f;
	float testFloat;
	//elementsinTest->NextSiblingElement()->QueryFloatText(&testFloat);
	testFloat = elementsinTest->NextSiblingElement()->FloatAttribute("test");
	
	std::string path;
	float x;
	float y;



	tinyxml2::XMLElement * elementWithNumbers = daRoot->FirstChildElement("NUMBERS");

	tinyxml2::XMLElement * firstNumber = elementWithNumbers->FirstChildElement();
	
	int allInts = 0;
	float allFloats = 0.f;

	while (firstNumber != nullptr)
	{
		std::string testString = firstNumber->Name();

		if (testString == "AFLOAT")
		//if (firstNumber->Name() == "AFLOAT")
		{
			float temp = 0;
			firstNumber->QueryFloatText(&temp);
			allFloats += temp;
		}
		//else if (firstNumber->Name() == "AINT")
		else if (testString == "AINT")
		{
			int temp = 0;
			firstNumber->QueryIntText(&temp);
			allInts += temp;
		}

		firstNumber = firstNumber->NextSiblingElement();
	}

	return 0;
}