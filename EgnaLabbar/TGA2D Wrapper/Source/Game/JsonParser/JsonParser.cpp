#include "stdafx.h"
#include "JsonParser.h"
#include "../Levels/Level.h"
#include "../Object/Object.h"
#include "tga2d\sprite\sprite.h"
#include <Vectors\Vector.h>
#include <sstream>
#include <fstream>
#include <DLDebug\DL_Debug.h>
#include <string>
#include "../Settings/Settings.h"
#include "../Levels/Border.h"
#include "../Player/Player.h"
#include "..\Interface\Dialog\DialogManager.h"
#include <CollisionManager\EventCollider.h>
#include <CollisionManager\CollisionShapes\BoxShape.h>
#include "../Object/ObjectManager.h"
#include <map>
#include <BaseClasses/BaseGameObject/BaseAnimatedObject/BaseAnimatedGameObject.h>
#include "../Object/BalanceLine.h"

JsonParser *JsonParser::ourInstance;

const std::string JsonParser::DefaultAnimationPath = "JSON/Animations/Default.json";

JsonParser::JsonParser()
{
}

JsonParser::~JsonParser()
{
}
#pragma warning( push )
#pragma warning( disable : 4127)

void JsonParser::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new JsonParser();
	}
}

void JsonParser::Destroy()
{
	delete ourInstance;

	ourInstance = nullptr;
}

void JsonParser::ReadJSONFile(picojson::value &aValue, const std::string &aPath)
{
	std::ifstream myReadFile;
	std::stringstream stringStream;
	myReadFile.open(aPath, std::ios::binary);

	// Read Json file
	if (!myReadFile.is_open()) return;
	stringStream << myReadFile.rdbuf();
	myReadFile.close();

	// Parse Json data
	stringStream >> aValue;
	std::string err = picojson::get_last_error();
	if (!err.empty()) {
		std::cout << err << " path " << aPath << std::endl;
		DL_ASSERT(false, (err + aPath).c_str());
		return;
	}
}
void JsonParser::InitInterfaces(CU::GrowingArray<InterfaceBase*> &aInterfaces, Inventory* aInventory)
{
	GetInstance().InitInternalInterfaces(aInterfaces, aInventory);
}

void JsonParser::InitInternalInterfaces(CU::GrowingArray<InterfaceBase*> &aInterfaces, Inventory* aInventory)
{
	picojson::value rootValue;
	std::string jsonpath = "JSON/Root.json";
	ReadJSONFile(rootValue, jsonpath);

	// check if the type of the value is "object"
	if (!rootValue.is<picojson::object>()) {
		DL_ASSERT(false, "Error in Root.json \nPath: JSON/Root.json");
	}

	picojson::object &root = rootValue.get<picojson::object>();
	std::string allInterfacesPath = root["InterfacesPath"].get<std::string>();

	picojson::value allInterfaces;
	ReadJSONFile(allInterfaces, allInterfacesPath);

	// check if the type of the value is "object"
	if (!allInterfaces.is<picojson::object>()) {
		DL_ASSERT(false, ("Error in Interfaces.json \nPath:" + allInterfacesPath).c_str());
	}

	picojson::object &interfaces = allInterfaces.get<picojson::object>();
	picojson::array &allInterfacsArray = interfaces["Interfaces"].get<picojson::array>();

	picojson::value currentInterfaceValue;
	for (size_t i = 0; i < allInterfacsArray.size(); i++)
	{
		std::string currentinterfacespath = allInterfacsArray[i].get("Path").get<std::string>();
		ReadJSONFile(currentInterfaceValue, currentinterfacespath);

		// check if the type of the value is "object"
		if (!currentInterfaceValue.is<picojson::object>()) {
			DL_ASSERT(false, ("Error in levels.json \nPath:" + currentinterfacespath).c_str());
		}

		std::cout << "JsonParser: Checking Interface: " << currentinterfacespath << std::endl;

		if (allInterfacsArray[i].get("InterfaceName").get<std::string>() == "Inventory")
		{
			std::string path = currentinterfacespath;
			ValidateJSONValue(currentInterfaceValue, "SpritePath", path);

			const char *spritePath = currentInterfaceValue.get("SpritePath").get<std::string>().c_str();

			ValidateJSONValue(currentInterfaceValue, "Position", path);

			picojson::value position = currentInterfaceValue.get("Position");

			InventoryInterface *inventory = new InventoryInterface(aInventory, 2,2, Vector2f(75,125), Vector2f(125,75));
			inventory->SetPosition(GetVector2fPosition(position));
			inventory->LoadSprite(spritePath);
			aInterfaces.Add(inventory);
		}
		else
		{
			// Validation
			const char* validationString = "Error: ";
			std::string message = validationString;
			message += " No supported interface found. Check Spelling and/or ask progg.";
			DL_ASSERT(false, message.c_str());
		}		
	}
}

void JsonParser::InitInternalSettings(Settings &aSettings)
{
	picojson::value rootValue;
	std::string jsonpath = "JSON/Settings.json";
	ReadJSONFile(rootValue, jsonpath);

	// check if the type of the value is "object"
	if (!rootValue.is<picojson::object>()) {
		DL_ASSERT(false, "Error in Settings.json \nPath: JSON/Settings.json");
	}

	// obtain a const reference to the map, and print the contents
	picojson::object &settings = rootValue.get<picojson::object>();

	ValidateJSONObject(settings, "Settings");

	picojson::array &allSettings = settings["Settings"].get<picojson::array>();

	for (size_t i = 0; i < allSettings.size(); i++)
	{
		std::string path = "JSON/Settings.json";
		ValidateJSONValue(allSettings[i], "SettingsType", path);

		std::string resolutionString = "Resolution";
		if (allSettings[i].get("SettingsType").get<std::string>() == resolutionString)
		{
			ValidateJSONValue(allSettings[i], "Width", path);
			ValidateJSONValue(allSettings[i], "Height", path);

			aSettings.myResolution.x = static_cast<float>(allSettings[i].get("Width").get<double>());
			aSettings.myResolution.y = static_cast<float>(allSettings[i].get("Height").get<double>());
		}

		std::string startStateString = "StartState";
		if (allSettings[i].get("SettingsType").get<std::string>() == startStateString)
		{
			ValidateJSONValue(allSettings[i], "Name", path);

			aSettings.myStartState = allSettings[i].get("Name").get<std::string>();
		}
	}
}

void JsonParser::InitSettings(Settings &aSettings)
{
	GetInstance().InitInternalSettings(aSettings);
}

void JsonParser::ValidateJSONValue(picojson::value &aObject, const char *aValidationString, std::string &aPath)
{
	bool validationBool = aObject.contains(aValidationString);
	if (validationBool == false)
	{
		std::string message = "Error in file: " + aPath + " does not contain " + "\"" + aValidationString + "\" check spelling";
		std::cout << message << std::endl;
		DL_ASSERT(validationBool, message.c_str());
	}
}

void JsonParser::ValidateJSONObject(picojson::object &aObject, const char *aValidationString)
{
	if (aObject.find(aValidationString) == aObject.cend())
	{
		std::string message = "Error does not contain \"" + std::string(aValidationString) + "\" check spelling";
		std::cout << message << std::endl;
		DL_ASSERT(false, message.c_str());
	}
}

bool JsonParser::DoesValueExist(picojson::value &aObject, const char *aValueName)
{
	return aObject.contains(aValueName);
}

void JsonParser::InitInternalLevels(CommonUtilities::GrowingArray<Level> &aLevels, Inventory *aInventory, Player *aPlayer)
{
	picojson::value rootValue;
	std::string jsonpath = "JSON/Root.json";
	ReadJSONFile(rootValue, jsonpath);

	// check if the type of the value is "object"
	if (!rootValue.is<picojson::object>()) {
		DL_ASSERT(false, "Error in Root.json \nPath: JSON/Root.json");
	}

	picojson::object &root = rootValue.get<picojson::object>();
	std::string allLevelsPath = root["LevelsPath"].get<std::string>();

	picojson::value allLevels;
	ReadJSONFile(allLevels, allLevelsPath);

	// check if the type of the value is "object"
	if (!allLevels.is<picojson::object>()) {
		DL_ASSERT(false, ("Error in Levels.json \nPath:" + allLevelsPath).c_str());
	}

	picojson::object &levels = allLevels.get<picojson::object>();
	picojson::array &allLevelsArray = levels["Levels"].get<picojson::array>();

	aLevels.Init(static_cast<unsigned short>(allLevelsArray.size()));

	picojson::value currentLevelValue;
	for (size_t i = 0; i < allLevelsArray.size(); i++)
	{
		std::string currentLevelpath = allLevelsArray[i].get("Path").get<std::string>();
		bool isStartLevel = (currentLevelpath == levels["StartLevel"].get("Path").get<std::string>());
		ReadJSONFile(currentLevelValue, currentLevelpath);

		// check if the type of the value is "object"
		if (!currentLevelValue.is<picojson::object>()) {
			DL_ASSERT(false, ("Error in levels.json \nPath:" + currentLevelpath).c_str());
		}

		std::cout << "JsonParser: Checking Level: " << currentLevelpath << std::endl;

		picojson::object &levelObject = currentLevelValue.get<picojson::object>();

		//Objects
		picojson::array &objects = levelObject["Objects"].get<picojson::array>();

		CommonUtilities::GrowingArray<Object*> allObjects;
		allObjects.Init(static_cast<unsigned short>(objects.size()));

		for (size_t i = 0; i < objects.size(); i++)
		{
			ValidateJSONValue(objects[i], "Name", currentLevelpath);
			ValidateJSONValue(objects[i], "SpritePath", currentLevelpath);
			ValidateJSONValue(objects[i], "Active", currentLevelpath);


			Object *object = new Object;
			object->Init(objects[i].get("Name").get<std::string>());
			
			if (objects[i].contains("Animation") == true)
			{
				InitAnimation(*object, objects[i].get("Animation").get<std::string>());
			}
			else
			{
				object->LoadSprite(objects[i].get("SpritePath").get<std::string>());
				InitAnimation(*object);
			}
			
			bool value = objects[i].get("Active").get<bool>();
			object->SetIsActive(value);
			

			Vector2f rawPosition = GetVector2fPosition(objects[i]);
			object->SetPosition(Vector2f(rawPosition.x, rawPosition.y));
			object->SetRenderPriority(rawPosition.y);
			object->SetColor(Vector4f(1.f, 1.f, 1.f, 1.f));
			object->SetSize(Vector2f(1.f, 1.f));
			object->SetRotation(0);
			CU::GrowingArray<Event*> eventList = InitEvents(objects[i].get<picojson::object>(), *object, aInventory, aPlayer);
			for (int i = 0; i < static_cast<int>(eventList.Size()); i++)
			{
				EventManager::AddEvent(eventList[static_cast<unsigned short>(i)]);
			}
			allObjects.Add(object);
		}

		// Level
		const char *backgroundPath = levelObject["BackgroundImagePath"].get<std::string>().c_str();
		std::string levelName = levelObject["Name"].get<std::string>();

		// Borders
		CommonUtilities::GrowingArray<Border> borderList;

		if (levelObject.find("BorderPath") != levelObject.cend())
		{
			std::string levelBorderPath = levelObject["BorderPath"].get<std::string>();
			picojson::value borderValue;
			ReadJSONFile(borderValue, levelBorderPath);

			picojson::object &bordersObject = borderValue.get<picojson::object>();
			picojson::array &borderArray = bordersObject["BorderObjects"].get<picojson::array>();


			borderList.Init(static_cast<unsigned short>(borderArray.size()));

			for (size_t i = 0; i < borderArray.size(); i++)
			{
				float xValue1 = static_cast<float>(borderArray[i].get("XPosition1").get<double>());
				float yValue1 = static_cast<float>(borderArray[i].get("YPosition1").get<double>());
				float xValue2 = static_cast<float>(borderArray[i].get("XPosition2").get<double>());
				float yValue2 = static_cast<float>(borderArray[i].get("YPosition2").get<double>());
				borderList.Add(Border(Vector2f(xValue1, yValue1), Vector2f(xValue2, yValue2)));
			}
		}

		Level level;

		if (levelObject.find("PlayerScaling") != levelObject.end())
		{
			picojson::object &playerScaling = levelObject["PlayerScaling"].get<picojson::object>();
			const float topY = static_cast<float>(playerScaling["TopY"].get<double>());
			const float topScale = static_cast<float>(playerScaling["TopScale"].get<double>());
			const float bottomY = static_cast<float>(playerScaling["BottomY"].get<double>());
			const float bottomScale = static_cast<float>(playerScaling["BottomScale"].get<double>());
			level.SetScaleValues(topY, topScale, bottomY, bottomScale);
		}

		picojson::object &player = levelObject["Player"].get<picojson::object>();
		Vector2f playerPos = GetVector2fPosition(player["PlayerPosition"]);

		std::map<std::string, Object*> objectMap;
		for (unsigned short i = 0; i < allObjects.Size(); i++)
		{
			objectMap.insert(std::pair<std::string, Object*>(allObjects[i]->GetName(), allObjects[i]));
		}

		ValidateJSONObject(levelObject, "BackgroundSound");
		std::string backgroundSoundName = levelObject["BackgroundSound"].get<std::string>();
		ObjectManager::Add(objectMap);
		if (currentLevelValue.contains("HasBeamPuzzle"))
		{
			if (currentLevelValue.get("HasBeamPuzzle").get<bool>() == true)
			{
				CreateBeamPuzzle(allObjects, aInventory, aPlayer);
			}
		}		

		level.Init(allObjects, borderList, backgroundPath, levelName, isStartLevel, playerPos, backgroundSoundName);

		aLevels.Add(level);
	}
}

void JsonParser::InitDialog(DialogManager &aDialogManager)
{
	GetInstance().InitInternalDialog(aDialogManager);
}
void JsonParser::InitInternalDialog(DialogManager &aDialogManager)
{

	picojson::value rootValue;
	std::string jsonpath = "JSON/Root.json";
	ReadJSONFile(rootValue, jsonpath);

	// check if the type of the value is "object"
	if (!rootValue.is<picojson::object>()) {
		DL_ASSERT(false, "Error in Root.json \nPath: JSON/Root.json");
	}

	picojson::object &root = rootValue.get<picojson::object>();
	std::string dialogPath = root["DialogPath"].get<std::string>();

	picojson::value dialogValue;
	ReadJSONFile(dialogValue, dialogPath);

	// check if the type of the value is "object"
	if (!dialogValue.is<picojson::object>()) {
		DL_ASSERT(false, ("Error in Dialog.json \nPath:" + dialogPath).c_str());
	}

	Point2f position;
	position.x = static_cast<float>(dialogValue.get("Dialog").get("PositionX").get<double>());
	position.y = static_cast<float>(dialogValue.get("Dialog").get("PositionY").get<double>());
	
	Vector2f size;
	size.x = static_cast<float>(dialogValue.get("Dialog").get("Width").get<double>());
	size.y = static_cast<float>(dialogValue.get("Dialog").get("Height").get<double>());
	
	std::string backgroundSpritePath = dialogValue.get("Dialog").get("BackgroundSpritePath").get<std::string>();
	std::string fontPath = dialogValue.get("Dialog").get("FontPath").get<std::string>();
	float fontSize = static_cast<float>(dialogValue.get("Dialog").get("FontSize").get<double>());

	Point2f positionText;
	positionText.x = position.x + static_cast<float>(dialogValue.get("Dialog").get("TextPositionX").get<double>());
	positionText.y = position.y + static_cast<float>(dialogValue.get("Dialog").get("TextPositionY").get<double>());

	Vector2f sizeText;
	sizeText.x = static_cast<float>(dialogValue.get("Dialog").get("TextWidth").get<double>());
	sizeText.y = static_cast<float>(dialogValue.get("Dialog").get("TextHeight").get<double>());

	Point2f avatarPosition;
	avatarPosition.x = position.x + static_cast<float>(dialogValue.get("Dialog").get("AvatarPositionX").get<double>());
	avatarPosition.y = position.y + static_cast<float>(dialogValue.get("Dialog").get("AvatarPositionY").get<double>());

	aDialogManager.SetPosition(position);
	aDialogManager.SetSize(size);

	aDialogManager.SetFontSize(fontSize);
	aDialogManager.LoadBackground(backgroundSpritePath);

	aDialogManager.SetTextPosition(positionText);
	aDialogManager.SetTextSize(sizeText);

	aDialogManager.LoadFont(fontPath);

	aDialogManager.SetAvatarPosition(avatarPosition);

	picojson::value &avatarSprites = dialogValue.get("Dialog").get("AvatarSprites");
	picojson::array &avatarImageList = avatarSprites.get<picojson::array>();
	for (unsigned short i = 0; i < avatarImageList.size(); ++i)
	{
		aDialogManager.LoadSpeakerSprite(
			avatarImageList[i].get("path").get<std::string>(),
			avatarImageList[i].get("id").get<std::string>()
		);
	}

}

void JsonParser::InitPlayer(Player *aPlayer)
{
	GetInstance().InitInternalPlayer(aPlayer);
}

void JsonParser::InitInternalPlayer(Player *aPlayer)
{
	picojson::value rootValue;
	std::string jsonpath = "JSON/Root.json";
	ReadJSONFile(rootValue, jsonpath);

	// check if the type of the value is "object"
	if (!rootValue.is<picojson::object>()) {
		DL_ASSERT(false, "Error in Root.json \nPath: JSON/Root.json");
	}

	picojson::object &root = rootValue.get<picojson::object>();
	std::string playerPath = root["PlayerPath"].get<std::string>();

	picojson::value playerValue;
	ReadJSONFile(playerValue, playerPath);

	// check if the type of the value is "object"
	if (!playerValue.is<picojson::object>()) {
		DL_ASSERT(false, ("Error in Player.json \nPath:" + playerPath).c_str());
	}

	//std::string spritePath = playerValue.get("Player").get("SpritePath").get<std::string>();
	float speed = static_cast<float>(playerValue.get("Player").get("PlayerSpeed").get<double>());

	std::string animationPath = playerValue.get("Player").get("AnimationPath").get<std::string>();
	InitAnimation(*aPlayer, animationPath);

	//aPlayer->LoadSprite(spritePath);
	aPlayer->SetSpeed(speed);
	aPlayer->SetPosition(Vector2f::Zero);


}

void JsonParser::InitAnimation(BaseAnimatedGameObject &aGameObject, const std::string &anAnimationFile)
{
	GetInstance().InitInternalAnimation(aGameObject, anAnimationFile);
}

void JsonParser::InitSounds(std::map<std::string, std::string> &aSoundsMap)
{
	GetInstance().InitInternalSounds(aSoundsMap);
}

void JsonParser::InitActionWheel(ActionWheel *aActionWheel)
{
	GetInstance().InitInternalActionWheel(aActionWheel);
}

void JsonParser::InitInternalAnimation(BaseAnimatedGameObject &aGameObject, const std::string &anAnimationFile)
{

	picojson::value rootValue;
	ReadJSONFile(rootValue, anAnimationFile);

	// check if the type of the value is "object"
	if (!rootValue.is<picojson::object>()) {
		DL_ASSERT(false, ("Error in Animation.json \nPath: " + anAnimationFile).c_str());
	}

	std::map<std::string, unsigned short> spriteData;

	picojson::value &animation = rootValue.get("Animation");
	if (animation.contains("SpriteSheet"))
	{

		std::string spriteSheet = animation.get("SpriteSheet").get<std::string>();
		const unsigned short columns = static_cast<unsigned short>(rootValue.get("Animation").get("Columns").get<double>());
		const unsigned short rows = static_cast<unsigned short>(rootValue.get("Animation").get("Rows").get<double>());

		std::shared_ptr<DX2D::CSprite> sprite = std::shared_ptr<DX2D::CSprite>(aGameObject.GetSprite());
		if (sprite == nullptr)
		{
			sprite = std::make_shared<DX2D::CSprite>(DX2D::CSprite(spriteSheet.c_str()));
		}

		spriteData["default"] = aGameObject.AddSpriteData(sprite, columns, rows);

	}
	else if (animation.contains("SpriteSheets"))
	{

		picojson::array &spriteDataList = animation.get("SpriteSheets").get<picojson::array>();
		for (unsigned short i = 0; i < spriteDataList.size(); ++i)
		{
			
			const std::string dataID = spriteDataList[i].get("ID").get<std::string>();
			const std::string spritePath = spriteDataList[i].get("Path").get<std::string>();

			const unsigned short columns = static_cast<unsigned short>(spriteDataList[i].get("Columns").get<double>());
			const unsigned short rows = static_cast<unsigned short>(spriteDataList[i].get("Rows").get<double>());

			spriteData[dataID] = aGameObject.AddSpriteData(std::make_shared<DX2D::CSprite>(DX2D::CSprite(spritePath.c_str())), columns, rows);

		}

	}
	else
	{
		bool crash = false;
		DL_ASSERT(crash, ("No spritesheet, specify \"SpriteSheet\" or \"SpriteSheets\" in " + anAnimationFile).c_str());
	}

	picojson::value &animationvalue = rootValue.get("Animation").get("AnimationList");
	picojson::array &animationList = animationvalue.get<picojson::array>();
	for (unsigned short i = 0; i < animationList.size(); ++i)
	{

		std::string spriteID;
		if (animationList[i].contains("SpriteID") == true)
		{
			spriteID = animationList[i].get("SpriteID").get<std::string>();
		}
		else
		{
			spriteID = "default";
		}

		std::string animationID = animationList[i].get("ID").get<std::string>();
		float displayTime = static_cast<float>(animationList[i].get("DisplayTime").get<double>());
		unsigned short firstFrame = static_cast<unsigned short>(animationList[i].get("FirstFrame").get<double>());
		unsigned short lastFrame = static_cast<unsigned short>(animationList[i].get("LastFrame").get<double>());
		bool loop = animationList[i].get("Loop").get<bool>();
		
		aGameObject.AddAnimation(animationID, displayTime, firstFrame, lastFrame, loop, spriteData.at(spriteID));

	}

	std::string defaultAnimation = rootValue.get("Animation").get("DefaultAnimation").get<std::string>();
	aGameObject.SetDefaultAnimation(defaultAnimation);
	aGameObject.PlayAnimtaion(defaultAnimation);

}

void JsonParser::InitInternalSounds(std::map<std::string, std::string> &aSoundsMap)
{
	picojson::value rootValue;
	std::string jsonpath = "JSON/Root.json";
	ReadJSONFile(rootValue, jsonpath);

	// check if the type of the value is "object"
	if (!rootValue.is<picojson::object>()) {
		DL_ASSERT(false, ("Error in Root.json \nPath: " + jsonpath).c_str());
	}

	picojson::value sounds;
	std::string soundsPath = rootValue.get("SoundsPath").get<std::string>();

	ReadJSONFile(sounds, soundsPath);

	// check if the type of the value is "object"
	if (!rootValue.is<picojson::object>()) {
		DL_ASSERT(false, ("Error in Sounds.json \nPath: " + soundsPath).c_str());
	}

	picojson::array soundsArray = sounds.get("Sounds").get<picojson::array>();

	for (unsigned short i = 0; i < soundsArray.size(); i++)
	{
		ValidateJSONValue(soundsArray[i], "Name", soundsPath);
		ValidateJSONValue(soundsArray[i], "Path", soundsPath);

		std::string name = soundsArray[i].get("Name").get<std::string>();
		std::string path = soundsArray[i].get("Path").get<std::string>();

		std::pair<std::string, std::string> pair;
		pair.first = name;
		pair.second = path;

		aSoundsMap.insert(pair);
	}
}

void JsonParser::InitInternalActionWheel(ActionWheel *aActionWheel)
{

	picojson::value rootValue;
	std::string jsonpath = "JSON/Root.json";
	ReadJSONFile(rootValue, jsonpath);

	// check if the type of the value is "object"
	if (!rootValue.is<picojson::object>()) {
		DL_ASSERT(false, ("Error in Root.json \nPath: " + jsonpath).c_str());
	}

	picojson::value sounds;
	std::string soundsPath = rootValue.get("ActionWheelPath").get<std::string>();

	ReadJSONFile(sounds, soundsPath);

	// check if the type of the value is "object"
	if (!rootValue.is<picojson::object>()) {
		DL_ASSERT(false, ("Error in ActionWheel.json \nPath: " + soundsPath).c_str());
	}

	picojson::array soundsArray = sounds.get("ActionWheel").get<picojson::array>();

	for (unsigned short i = 0; i < soundsArray.size(); i++)
	{
		ValidateJSONValue(soundsArray[i], "Name", soundsPath);
		ValidateJSONValue(soundsArray[i], "SpritePath", soundsPath);

		std::string name = soundsArray[i].get("Name").get<std::string>();
		std::string path = soundsArray[i].get("SpritePath").get<std::string>();

		if (name == std::string("Fire"))
		{
			aActionWheel->MyFirePath(path);
		}
		else if (name == std::string("Water"))
		{
			aActionWheel->MyWaterPath(path);
		}
		else if (name == std::string("Wind"))
		{
			aActionWheel->MyWindPath(path);
		}
		else if (name == std::string("Earth"))
		{
			aActionWheel->MyEarthPath(path);
		}
		else if (name == std::string("Click"))
		{
			aActionWheel->MyClickPath(path);
		}
		else
		{
			// Validation
			const char* validationString = "Error: ";
			std::string message = validationString;
			message += name;
			message += ": This action wheel name is not supported.";
			DL_ASSERT(false, message.c_str());
		}
	}
}


void JsonParser::InitLevels(CommonUtilities::GrowingArray<Level> &aLevels, Inventory *aInventory, Player *aPlayer)
{
	GetInstance().InitInternalLevels(aLevels, aInventory, aPlayer);
}

CU::GrowingArray<Event*> JsonParser::InitEvents(picojson::object &aJSONObject,
	Object &aObject, Inventory *aInventory, Player *aPlayer)
{
	CommonUtilities::GrowingArray<Event*> eventList;
	if (eventList.IsInitialized() == false)
	{
		eventList.Init(20);
	}

	if (aJSONObject.find("Events") != aJSONObject.cend())
	{
		picojson::array &events = aJSONObject["Events"].get<picojson::array>();

		for (size_t i = 0; i < events.size(); i++)
		{
			// Validation
			const char *validationString = "EventType";
			std::string path = "";
			ValidateJSONValue(events[i], validationString, path);
			std::string test = events[i].get(validationString).get<std::string>();

			if (events[i].get(validationString).get<std::string>() == std::string("PickUpEvent"))
			{
				CreatePickupEvent(events, i, path, eventList, aInventory, aObject);

			}
			else if (events[i].get(validationString).get<std::string>() == std::string("ChangeLevelEvent"))
			{
				CreateChangeLevelEvent(events, i, path, eventList, aPlayer);
			}
			else if (events[i].get(validationString).get<std::string>() == std::string("PlaySoundEvent"))
			{
				CreatePlaySoundEvent(events, i, path, eventList);

			}
			else if (events[i].get(validationString).get<std::string>() == std::string("OnClickEvent"))
			{
				CreateOnclickEvent(aObject, aInventory, events, i, aPlayer);

			}
			else if (events[i].get(validationString).get<std::string>() == std::string("OnCombineEvent"))
			{
				CreateOnCombineEvent(events, i, path, aObject, aInventory, aPlayer, eventList);

			}
			else if (events[i].get(validationString).get<std::string>() == std::string("AddAsInventory"))
			{
				CreateAddAsInventoryEvent(eventList, aInventory, aObject);

			}
			else if (events[i].get(validationString).get<std::string>() == std::string("OnUseEvent"))
			{
				CreateOnuseEvent(events, aObject, aInventory, aPlayer,i);

			}
			else if (events[i].get(validationString).get<std::string>() == std::string("DialogueEvent"))
			{
				CreateDialogEvent(events, i, path, eventList);
			}
			else if (events[i].get(validationString).get<std::string>() == std::string("OnElement"))
			{
				CreateOnElementEvent(events, i, aObject, aInventory, aPlayer);

			}
			else if (events[i].get(validationString).get<std::string>() == std::string("SetActiveEvent"))
			{
				CreateSetActiveEvent(events, i, path, eventList);
			}
			else if (events[i].get(validationString).get<std::string>() == std::string("CheckInventoryEvent"))
			{
				CreateCheckInventoryEvent(events, i, path, aInventory, aObject, aPlayer, eventList);
			}
			else if (events[i].get(validationString).get<std::string>() == std::string("SetActiveInterface"))
			{
				CreateSetActiveInterfaceEvent(events, i, path, eventList);
			}
			else if (events[i].get(validationString).get<std::string>() == std::string("ExamineEvent"))
			{
				CreateExamineEvent(events, i, path, aObject);
			}
			else if (events[i].get(validationString).get<std::string>() == std::string("UnlockMagicEvent"))
			{
				CreateActivateMagicEvent(events, i, path, eventList);

			}
			else
			{
				PrintEventsNotFoundError(events, i);
			}
		}
	}	
	return eventList;
}

void JsonParser::CreateActivateMagicEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList)
{
	// Validation
	ValidateJSONValue(events[i], "Data", path);

	picojson::value &dataObject = events[i].get<picojson::object>()["Data"];
	ValidateJSONValue(dataObject, "Type", path);
	std::string type = dataObject.get("Type").get<std::string>();

	if (type == "Fire")
	{
		eventList.Add(new ActivateMagicElementEvent(eElementType::eFire));
	}
	else if (type == "Water")
	{
		eventList.Add(new ActivateMagicElementEvent(eElementType::eWater));
	}
	else if (type == "Earth")
	{
		eventList.Add(new ActivateMagicElementEvent(eElementType::eEarth));
	}
	else if (type == "Wind")
	{
		eventList.Add(new ActivateMagicElementEvent(eElementType::eWind));
	}
	else
	{
		// Validation
		const char* validationString = "Error: ";
		std::string message = validationString;
		message += type;
		message += ": Not supported. Supported elements are: Fire Water Earth Wind";
		DL_ASSERT(false, message.c_str());
	}
}

void JsonParser::CreateExamineEvent(picojson::array & events, size_t i, std::string path, Object &aObject)
{
	CommonUtilities::GrowingArray<Event*> list;
	list.Init(2);
	CreateDialogEvent(events, i, path, list);
	aObject.SetExamineEvent(dynamic_cast<PlayDialogEvent*>(list[0]));
}

void JsonParser::CreateSetActiveInterfaceEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList)
{
	// Validation
	ValidateJSONValue(events[i], "Data", path);

	picojson::value &dataObject = events[i].get<picojson::object>()["Data"];
	ValidateJSONValue(dataObject, "InterfaceName", path);
	std::string inerfaceName = dataObject.get("InterfaceName").get<std::string>();
	ValidateJSONValue(dataObject, "Value", path);
	bool value = dataObject.get("Value").get<bool>();

	eventList.Add(new SetActiveInterface(inerfaceName, value));
}

void JsonParser::PrintEventsNotFoundError(picojson::array &events, size_t i)
{
	// Validation
	const char* validationString = "Error: ";
	std::string message = validationString;
	message += events[i].get("EventType").get<std::string>();
	message += ": Not supported event found. Check Spelling and/or ask progg. Release version outdated?";
	DL_ASSERT(false, message.c_str());
}

void JsonParser::CreateOnElementEvent(picojson::array &events, size_t i, Object &aObject, Inventory * aInventory, Player * aPlayer)
{
	if (DoesValueExist(events[i], "FireEvents") == true)
	{
		CommonUtilities::GrowingArray<Event*> event = InitEvents(events[i].get("FireEvents").get<picojson::object>(), aObject, aInventory, aPlayer);
		for (unsigned short i = 0; i < static_cast<int>(event.Size()); i++)
		{
			aObject.AddElementEvent(eElementType::eFire, event[i]);
		}
	}
	if (DoesValueExist(events[i], "WaterEvents") == true)
	{
		CommonUtilities::GrowingArray<Event*> event = InitEvents(events[i].get("WaterEvents").get<picojson::object>(), aObject, aInventory, aPlayer);
		for (unsigned short i = 0; i < static_cast<int>(event.Size()); i++)
		{
			aObject.AddElementEvent(eElementType::eWater, event[i]);
		}
	}
	if (DoesValueExist(events[i], "WindEvents") == true)
	{
		CommonUtilities::GrowingArray<Event*> event = InitEvents(events[i].get("WindEvents").get<picojson::object>(), aObject, aInventory, aPlayer);
		for (unsigned short i = 0; i < static_cast<int>(event.Size()); i++)
		{
			aObject.AddElementEvent(eElementType::eWind, event[i]);
		}
	}
	if (DoesValueExist(events[i], "EarthEvents") == true)
	{
		CommonUtilities::GrowingArray<Event*> event = InitEvents(events[i].get("EarthEvents").get<picojson::object>(), aObject, aInventory, aPlayer);
		for (unsigned short i = 0; i < static_cast<int>(event.Size()); i++)
		{
			aObject.AddElementEvent(eElementType::eEarth, event[i]);
		}
	}
}

void JsonParser::CreateDialogEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList)
{
	ValidateJSONValue(events[i], "Data", path);
	picojson::value &dataObject = events[i].get<picojson::object>()["Data"];

	ValidateJSONValue(dataObject, "SpriteID", path);
	std::string avatarID = dataObject.get("SpriteID").get<std::string>();

	ValidateJSONValue(dataObject, "Text", path);
	std::string text = dataObject.get("Text").get<std::string>();

	eventList.Add(new PlayDialogEvent(avatarID, text));
}

void JsonParser::CreateAddAsInventoryEvent(CommonUtilities::GrowingArray<Event*> &eventList, Inventory * aInventory, Object & aObject)
{
	eventList.Add(new AddAsSelectedObjectEvent(aInventory, &aObject));
}

void JsonParser::CreateOnuseEvent(picojson::array &events, Object & aObject, Inventory * aInventory, Player * aPlayer, size_t aI)
{
	OnUseEvents *useEvent = new OnUseEvents();
	CommonUtilities::GrowingArray<Event*> event = InitEvents(events[aI].get<picojson::object>(), aObject, aInventory, aPlayer);
	for (int i = 0; i < static_cast<int>(event.Size()); i++)
	{
		useEvent->AddEvent(event[static_cast<unsigned short>(i)]);
	}
	EventManager::AddEvent(useEvent);
}

void JsonParser::CreateOnCombineEvent(picojson::array &events, size_t i, std::string path, Object & aObject, Inventory * aInventory, Player * aPlayer, CommonUtilities::GrowingArray<Event*> &eventList)
{
	ValidateJSONValue(events[i], "Data", path);
	picojson::value &dataObject = events[i].get<picojson::object>()["Data"];

	ValidateJSONValue(dataObject, "ObjectToCombineWith", path);
	std::string objectToCombineWith = dataObject.get("ObjectToCombineWith").get<std::string>();

	OnCombineEvent *combineEvent = new OnCombineEvent(objectToCombineWith);
	CommonUtilities::GrowingArray<Event*> event = InitEvents(events[i].get<picojson::object>(), aObject, aInventory, aPlayer);
	for (int j = 0; j < static_cast<int>(event.Size()); j++)
	{
		combineEvent->AddEvent(event[static_cast<unsigned short>(j)]);
	}

	picojson::object boxObject = events[i].get("BoxSize").get<picojson::object>();



	//aObject.SetEventCollider(new EventCollider(box, combineEvent));
	eventList.Add(combineEvent);
	EventManager::AddEvent(combineEvent);
}

void JsonParser::CreateOnclickEvent(Object &aObject, Inventory * aInventory, picojson::array &events, size_t i, Player * aPlayer)
{
	OnClickEvent *clickEvent = new OnClickEvent(&aObject, aInventory);
	CommonUtilities::GrowingArray<Event*> event = InitEvents(events[i].get<picojson::object>(), aObject, aInventory, aPlayer);
	for (int j = 0; j < static_cast<int>(event.Size()); j++)
	{
		clickEvent->AddEvent(event[static_cast<unsigned short>(j)]);
	}

	picojson::object boxObject = events[i].get("BoxSize").get<picojson::object>();

	BoxShape *box = new BoxShape(aObject.GetPosition(),
		Vector2f(static_cast<float>(boxObject["X"].get<double>()),
		static_cast<float>(boxObject["X"].get<double>())));

	aObject.SetEventCollider(new EventCollider(box, clickEvent, &aObject));
	EventManager::AddEvent(clickEvent);
}


void JsonParser::CreateCheckInventoryEvent(picojson::array &events, size_t i, std::string path, Inventory * aInventory, Object &aObject, Player * aPlayer, CommonUtilities::GrowingArray<Event*> &eventList)
{
	// Validation
	ValidateJSONValue(events[i], "Data", path);

	picojson::value &dataObject = events[i].get<picojson::object>()["Data"];
	ValidateJSONValue(dataObject, "ObjectName", path);
	std::string objectName = dataObject.get("ObjectName").get<std::string>();
	CheckInventoryEvent *checkEvent = new CheckInventoryEvent(objectName, aInventory);
	CommonUtilities::GrowingArray<Event*> event = InitEvents(events[i].get<picojson::object>(), aObject, aInventory, aPlayer);
	for (int j = 0; j < static_cast<int>(event.Size()); j++)
	{
		checkEvent->AddEvent(event[static_cast<unsigned short>(j)]);
	}
	eventList.Add(checkEvent);
	EventManager::AddEvent(checkEvent);
}

void JsonParser::CreatePlaySoundEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList)
{
	// Validation
	ValidateJSONValue(events[i], "Data", path);

	picojson::value &dataObject = events[i].get<picojson::object>()["Data"];
	ValidateJSONValue(dataObject, "SoundName", path);
	std::string soundName = dataObject.get("SoundName").get<std::string>();
	ValidateJSONValue(dataObject, "Repeat", path);
	bool repeat = dataObject.get("Repeat").get<bool>();

	eventList.Add(new PlaySoundEvent(soundName, repeat));
}

Vector2f JsonParser::GetVector2fPosition(picojson::value &aObject)
{
	// Validation
	std::string path = "";
	ValidateJSONValue(aObject, "YPosition", path);
	ValidateJSONValue(aObject, "XPosition", path);
	return Vector2f(static_cast<float>(aObject.get("XPosition").get<double>()), static_cast<float>(aObject.get("YPosition").get<double>()));
}

void JsonParser::CreatePickupEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList, Inventory * aInventory, Object &aObject)
{
	picojson::value &dataObject = events[i].get<picojson::object>()["Data"];
	ValidateJSONValue(dataObject, "ObjectNametoPickUp", path);
	ValidateJSONValue(dataObject, "RemoveObjectAfterPickup", path);

	std::string targetObject = dataObject.get("ObjectNametoPickUp").get<std::string>();
	bool removeAfterPickup = dataObject.get("RemoveObjectAfterPickup").get<bool>();

	eventList.Add(new PickUpEvent(aInventory, aObject.GetName(), targetObject, removeAfterPickup));
}

void JsonParser::CreateChangeLevelEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList, Player * aPlayer)
{
	// Validation
	ValidateJSONValue(events[i], "Data", path);

	picojson::value &dataObject = events[i].get<picojson::object>()["Data"];
	ValidateJSONValue(dataObject, "TargetLevelName", path);
	std::string targetName = dataObject.get("TargetLevelName").get<std::string>();
	ValidateJSONValue(dataObject, "PlayerPosition", path);
	Vector2f playerPos = GetVector2fPosition(dataObject.get("PlayerPosition"));

	eventList.Add(new ChangeLevelEvent(targetName, (*aPlayer), playerPos));// targetPosition));
}

void JsonParser::CreateSetActiveEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList)
{
	// Validation
	ValidateJSONValue(events[i], "Data", path);

	picojson::value &dataObject = events[i].get<picojson::object>()["Data"];
	ValidateJSONValue(dataObject, "ObjectName", path);
	std::string objectName = dataObject.get("ObjectName").get<std::string>();
	ValidateJSONValue(dataObject, "Value", path);
	bool value = dataObject.get("Value").get<bool>();

	eventList.Add(new SetActiveEvent(objectName, value));
}


void JsonParser::CreateBeamPuzzle(CommonUtilities::GrowingArray<Object*> &aObjects,
		Inventory *aInventory, Player *aPlayer)
{
	picojson::value rootValue;
	std::string jsonpath = "JSON/Root.json";
	ReadJSONFile(rootValue, jsonpath);

	// check if the type of the value is "object"
	if (!rootValue.is<picojson::object>()) {
		DL_ASSERT(false, "Error in Root.json \nPath: JSON/Root.json");
	}

	std::string path = "BalanceBeamPuzzle.json";
	ValidateJSONValue(rootValue, "BalanceBeamPuzzle", path);

	picojson::object &root = rootValue.get<picojson::object>();
	std::string beamPuzzle = root["BalanceBeamPuzzle"].get<std::string>();

	picojson::value beamPuzzleValue;
	ReadJSONFile(beamPuzzleValue, beamPuzzle);
	// check if the type of the value is "object"
	if (!beamPuzzleValue.is<picojson::object>()) {
		DL_ASSERT(false, "Error in BeamPuzzlePuzzle.json");
	}

	ValidateJSONValue(beamPuzzleValue, "LeftSideWeights", path);
	ValidateJSONValue(beamPuzzleValue, "RightSideWeights", path);
	ValidateJSONValue(beamPuzzleValue, "VictoryAngles", path);
	ValidateJSONValue(beamPuzzleValue, "VictoryAnglesSprite", path);
	ValidateJSONValue(beamPuzzleValue, "DistanceFromBeam", path);
	
	CommonUtilities::GrowingArray<WeightData*> leftWeights;
	leftWeights.Init(10);
	CommonUtilities::GrowingArray<WeightData*> rightWeights;
	rightWeights.Init(10);
	CommonUtilities::GrowingArray<VictoryAngleData*> angleList;
	angleList.Init(10);
	picojson::array &leftSideWeights = beamPuzzleValue.get("LeftSideWeights").get<picojson::array>();
	picojson::array &rightSideWeights = beamPuzzleValue.get("RightSideWeights").get<picojson::array>();
	picojson::array &victoryAngles = beamPuzzleValue.get("VictoryAngles").get<picojson::array>();

	picojson::value beam = beamPuzzleValue.get("Beam");
	Vector2f leftCenterPos = GetVector2fPosition(beam.get("LeftSideOffset"));
	Vector2f rightCenterPos = GetVector2fPosition(beam.get("RightSideOffset"));

	ReadSideWeightData(leftSideWeights, leftWeights);
	ReadSideWeightData(rightSideWeights, rightWeights);
	ReadVictoryAngleData(victoryAngles, angleList, aInventory, aPlayer, beamPuzzleValue.get("VictoryAnglesSprite").get<std::string>());

	ValidateJSONValue(beam, "SpritePath", path);
	ValidateJSONValue(beam, "BasePosition", path);
	ValidateJSONValue(beam, "LeftSideOffset", path);
	ValidateJSONValue(beam, "RightSideOffset", path);

	std::string beamSpritePath = beam.get("SpritePath").get<std::string>();
	Vector2f basePos = GetVector2fPosition(beam.get("BasePosition"));
	Vector2f rightPos = GetVector2fPosition(beam.get("RightSideOffset"));
	Vector2f leftPos = GetVector2fPosition(beam.get("LeftSideOffset"));

	BeamData beamData;
	beamData.myLeftSideOffset = leftPos;
	beamData.myLeftSideWeights = leftWeights;
	beamData.myMainPoint = basePos;
	beamData.myRightSideOffset = rightPos;
	beamData.myRightSideWeights = rightWeights;
	beamData.mySpritePath = beamSpritePath;
	beamData.VictoryPointDistanceFromLine = static_cast<float>( beamPuzzleValue.get("DistanceFromBeam").get<double>());
	beamData.myVictoryAngles = angleList;

	BalanceLine *b = new BalanceLine(beamData);
	aObjects.Add(b);
}

void JsonParser::ReadSideWeightData(picojson::array &aValues,
	CommonUtilities::GrowingArray<WeightData*> &aWeightData)
{
	std::string path = "BalanceBeamPuzzle.json";
	for (unsigned short i = 0; i < aValues.size(); i++)
	{
		ValidateJSONValue(aValues[i], "SpritePath", path);
		ValidateJSONValue(aValues[i], "OffestPosition", path);
		ValidateJSONValue(aValues[i], "Weight", path);
		ValidateJSONValue(aValues[i], "BoxSize", path);

		std::string spritePath = aValues[i].get("SpritePath").get<std::string>();
		Vector2f offsetPos = GetVector2fPosition(aValues[i].get("OffestPosition"));
		float weight = static_cast<float>(aValues[i].get("Weight").get<double>());

		picojson::object boxObject = aValues[i].get("BoxSize").get<picojson::object>();

		

		WeightData *data = new WeightData;
		data->myAngleWeight = weight;
		data->myBoxShapeSize = Vector2f(static_cast<float>(boxObject["X"].get<double>()),
			static_cast<float>(boxObject["X"].get<double>()));
		data->myOffset = offsetPos;
		data->mySpritePath = spritePath;

		aWeightData.Add(data);
	}
}

void JsonParser::ReadVictoryAngleData(picojson::array &aValue, CommonUtilities::GrowingArray<VictoryAngleData*> &aVictoryDataList,
	Inventory *aInventory, Player *aPlayer, std::string &aSpritePath)
{
	std::string path = "BalanceBeamPuzzle.json";
	for (unsigned short i = 0; i < aValue.size(); i++)
	{
		ValidateJSONValue(aValue[i], "Angle", path);
		float angle = static_cast<float>(aValue[i].get("Angle").get<double>());
		CommonUtilities::GrowingArray<Event*> list;
		list.Init(20);
		Object *o = new Object;
		VictoryAngleData *data = new VictoryAngleData;
		list = InitEvents(aValue[i].get<picojson::object>(), *o, aInventory, aPlayer);
		data->myEvents = list;
		data->mySpritePath = aSpritePath;
		data->myAngle = angle;
		aVictoryDataList.Add(data);
	}
}

#pragma warning( pop ) 