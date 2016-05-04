#include "JSONParser.h"


void JSONParser::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new JSONParser();
	}
}

void JSONParser::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}











JSONParser* JSONParser::ourInstance = nullptr;



JSONParser::JSONParser()
{
	myFileReader.open("JSON/Emitter.json");
	
	picojson::value file;
	

	picojson::parse(file, myFileReader);

	myRoot = file.get<picojson::object>();
}


JSONParser::~JSONParser()
{
}
