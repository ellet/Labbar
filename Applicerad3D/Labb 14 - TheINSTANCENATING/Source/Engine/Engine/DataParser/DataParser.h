#pragma once
#include "rapidjson\document.h"

namespace ENGINE_NAMESPACE
{
	typedef rapidjson::Document DataDocument;
	typedef rapidjson::Value& DataNode;
	typedef rapidjson::Value DataNodeCopy;

	namespace DataParser
	{
		void Open(const std::string &aFileName, rapidjson::Document& aDocument, const bool aPrintLogMessage = true);
		void Open(const char* aFileName, rapidjson::Document& aDocument, const bool aPrintLogMessage = true);
		
		void ClearDocumentFromCache(const std::string& aFileName);

	} namespace Data = DataParser; namespace JsonParser = DataParser; namespace Json = DataParser;
}
