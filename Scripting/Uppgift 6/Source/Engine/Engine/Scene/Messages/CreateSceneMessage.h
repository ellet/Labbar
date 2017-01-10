#pragma once

namespace SB
{
	enum class eSceneClass
	{
		eJSON,
		eCredits,
		eSplashscreen,
		eMainMenu,
		eLevelSelect,
		eOptions,
		eParticleEditor,
		eYlfTest,
		enumlength
	};

	enum class eSceneType
	{
		eMajor,
		eSub
	};

	struct CreateSceneMessage
	{
		CreateSceneMessage(eSceneClass aSceneClassEnum, eSceneType aSceneTypeEnum, std::function<void(std::shared_ptr<SB::Scene>)> aFunctionToCall, const std::string & aFilePath = "", const std::string & aSkyBoxPath = "", const unsigned short aLevelNumber = 0)
		{
			mySceneClass = aSceneClassEnum;
			mySceneType = aSceneTypeEnum;
			myFilePath = aFilePath;
			mySkyBoxPath = aSkyBoxPath;
			myFunctionCall = aFunctionToCall;
			myLevelNumber = aLevelNumber;
		}

		std::string myFilePath;
		std::string mySkyBoxPath;
		eSceneClass mySceneClass;
		eSceneType mySceneType;
		std::function<void(std::shared_ptr<SB::Scene>)> myFunctionCall;
		unsigned short myLevelNumber;
	};

}