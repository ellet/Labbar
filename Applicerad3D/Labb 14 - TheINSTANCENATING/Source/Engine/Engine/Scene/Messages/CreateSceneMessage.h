#pragma once

namespace ENGINE_NAMESPACE
{
	enum class eSceneClass
	{
		eJSON,
		ePauseMenu,
		eMainMenu,
		eLevelSelect,
		eCredit,
		eOptions,
		eParticleEditor
	};

	enum class eSceneType
	{
		eMajor,
		eSub
	};

	struct CreateSceneMessage
	{
		CreateSceneMessage(eSceneClass aSceneClassEnum, eSceneType aSceneTypeEnum, std::function<void(std::shared_ptr<SB::Scene>)> aFunctionToCall, const std::string & aFilePath = "")
		{
			mySceneClass = aSceneClassEnum;
			mySceneType = aSceneTypeEnum;
			myFilePath = aFilePath;
			myFunctionCall = aFunctionToCall;
		}

		std::string myFilePath;
		eSceneClass mySceneClass;
		eSceneType mySceneType;
		std::function<void(std::shared_ptr<SB::Scene>)> myFunctionCall;
	};

}