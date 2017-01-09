//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "DataParser.h"
#include "rapidjson/error/en.h"
#include <mutex>
#include <unordered_map>
#include <string>

namespace SB
{
	namespace DataParser
	{
		std::mutex loadMutex;
		std::unordered_map<std::string, rapidjson::Document*> loadedDocuments;

		void Open(const std::string &aFileName, rapidjson::Document& aDocument, const bool aPrintLogMessage)
		{
			Open(aFileName.c_str(), aDocument, aPrintLogMessage);
		}
		void Open(const char* aFileName, rapidjson::Document& aDocument, const bool aPrintLogMessage)
		{
			{
				std::lock_guard<std::mutex> lg(loadMutex);
				auto && it = loadedDocuments.find(aFileName);
				if (it != loadedDocuments.end())
				{
					aDocument.CopyFrom(*it->second, aDocument.GetAllocator());
					return;
				}
			}

			std::ifstream file(aFileName);//Open file
			if (file.fail() == true)
			{
				std::string message = "Json file: ";
				message += aFileName;
				message += " doesn't exist! Please reconsider your life choices!";
				//Error(message);
				std::cout << message.c_str() << std::endl;
			}
			std::string str((std::istreambuf_iterator<char>(file)), //Begin of file
				std::istreambuf_iterator<char>()); //End of file

			//size_t stringLength = str.length() + 2;
			//char* data = new char[stringLength]; //Set data to the amount of characters in str
			//
			//unsigned int dataIndex = 0;
			//for (unsigned int i = 0; i < str.length(); ++i)
			//{
			//	if (str[i] != 0)
			//	{
			//		data[dataIndex] = str[i];
			//		++dataIndex;
			//	}
			//}
			//
			//data[dataIndex] = '\0'; //Set last character to null
			file.close();//Close file

			rapidjson::ParseResult parseResult = aDocument.Parse(str.c_str());


			if (aDocument.HasParseError() == true)
			{
				unsigned short errorLine = 0;
				for (size_t i = 0; i < parseResult.Offset(); ++i)
				{
					if (str[i] == '\n')
					{
						++errorLine;
					}
				}

				std::string fileName = aFileName;
				std::string errorText = "Error parsing JSON file " + fileName + " at line #" + std::to_string(errorLine) + ": ";


				rapidjson::ParseErrorCode error = aDocument.GetParseError();
				switch (error)
				{
				case rapidjson::kParseErrorDocumentEmpty:
					errorText += "Document is empty";
					break;
				case rapidjson::kParseErrorDocumentRootNotSingular:
					errorText += "Document root not singular";
					break;
				case rapidjson::kParseErrorValueInvalid:
					errorText += "Value invalid";
					break;
				case rapidjson::kParseErrorObjectMissName:
					errorText += "Object missing name";
					break;
				case rapidjson::kParseErrorObjectMissColon:
					errorText += "Object missing colon";
					break;
				case rapidjson::kParseErrorObjectMissCommaOrCurlyBracket:
					errorText += "Object missing comma or curly bracket";
					break;
				case rapidjson::kParseErrorArrayMissCommaOrSquareBracket:
					errorText += "Array missing comma or square bracket";
					break;
				case rapidjson::kParseErrorStringUnicodeEscapeInvalidHex:
					errorText += "String unicode escape invalid hex";
					break;
				case rapidjson::kParseErrorStringUnicodeSurrogateInvalid:
					errorText += "String unicode surrogate invalid";
					break;
				case rapidjson::kParseErrorStringEscapeInvalid:
					errorText += "String escape invalid";
					break;
				case rapidjson::kParseErrorStringMissQuotationMark:
					errorText += "String missing quotation mark";
					break;
				case rapidjson::kParseErrorStringInvalidEncoding:
					errorText += "String invalid encoding";
					break;
				case rapidjson::kParseErrorNumberTooBig:
					errorText += "Number too big";
					break;
				case rapidjson::kParseErrorNumberMissFraction:
					errorText += "Number missing fraction";
					break;
				case rapidjson::kParseErrorNumberMissExponent:
					errorText += "Number missing exponent";
					break;
				case rapidjson::kParseErrorTermination:
					errorText += "Termination";
					break;
				case rapidjson::kParseErrorUnspecificSyntaxError:
					errorText += "Unspecified syntax error";
					break;
				default:
					errorText += "Unspecified error";
					break;
				}

				//Error(errorText.c_str());
				std::cout << errorText << std::endl;
			}

			//delete[] data;
			//data = nullptr;

			if (aPrintLogMessage == true)
			{
				std::cout << "Loaded " << aFileName << std::endl;
			}

			rapidjson::Document *newDoc = new rapidjson::Document();
			newDoc->CopyFrom(aDocument, newDoc->GetAllocator());
			std::lock_guard<std::mutex> lg(loadMutex);
			if (loadedDocuments.find(aFileName) == loadedDocuments.end())
			{
				loadedDocuments.emplace(aFileName, newDoc);
			}
			else
			{
				delete newDoc;
			}
		}

		void ClearDocumentFromCache(const std::string& aFileName)
		{
			std::lock_guard<std::mutex> lg(loadMutex);
			auto && it = loadedDocuments.find(aFileName);
			if (it == loadedDocuments.end())
			{
				return;
			}
			delete it->second;
			loadedDocuments.erase(it);
		}

	} namespace Data = DataParser; namespace JsonParser = DataParser; namespace Json = DataParser;
}
