#pragma once
#include <DLDEBUG\DL_Debug.h>
#include <GrowingArray\GrowingArray.h>
#include "..\Levels\Level.h"
#include "../../picojson-master/picojson.h"
#include "../EventManager/Events/AllEvents.h"
#include "../Interface/InterfaceBase.h"
#include "../Interface/Inventory/InventoryInterface.h"
#include <map>
#include <Input\MouseActions\ActionWheel.h>

struct Settings;
class Inventory;
class Player;
class DialogManager;
class BaseAnimatedGameObject;
class Object;
class BalanceLine;
struct WeightData;
struct VictoryAngleData;

class JsonParser
{
public:

	static void Create();
	static void Destroy();
	static void InitLevels(CommonUtilities::GrowingArray<Level> &aLevels, Inventory *aInventory, Player *aPlayer);
	static void InitSettings(Settings &aSettings);
	static void InitDialog(DialogManager &aDialogManager);
	static void InitInterfaces(CU::GrowingArray<InterfaceBase*> &aInterfaces, Inventory* aInventory);
	static void InitPlayer(Player *aPlayer);
	static void InitAnimation(BaseAnimatedGameObject &aGameObject, const std::string &anAnimationFile = DefaultAnimationPath);
	static void InitSounds(std::map<std::string, std::string> &aSoundsMap);
	static void InitActionWheel(ActionWheel *aActionWheel);

private:

	static const std::string DefaultAnimationPath;

	JsonParser();
	~JsonParser();
	static void ReadJSONFile(picojson::value &aValue, const  std::string &aPath);
	CU::GrowingArray<Event*> InitEvents(picojson::object &aJSONObject,
		Object &aObject, Inventory *aInventory, Player *aPlayer);

	void CreateActivateMagicEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList);
	void CreateExamineEvent(picojson::array & events, size_t i, std::string path, Object &aObject);
	void CreateSetActiveInterfaceEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList);
	void PrintEventsNotFoundError(picojson::array &events, size_t i);
	void CreateOnElementEvent(picojson::array &events, size_t i, Object &aObject, Inventory * aInventory, Player * aPlayer);
	void CreateDialogEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList);
	void CreateAddAsInventoryEvent(CommonUtilities::GrowingArray<Event*> &eventList, Inventory * aInventory, Object & aObject);
	void CreateOnuseEvent(picojson::array &events, Object & aObject, Inventory * aInventory, Player * aPlayer, size_t aI);
	void CreateOnCombineEvent(picojson::array &events, size_t i, std::string path, Object & aObject, Inventory * aInventory, Player * aPlayer, CommonUtilities::GrowingArray<Event*> &eventList);
	void CreateOnclickEvent(Object &aObject, Inventory * aInventory, picojson::array &events, size_t i, Player * aPlayer);
	void CreateCheckInventoryEvent(picojson::array &events, size_t i, std::string path, Inventory * aInventory, Object &aObject, Player * aPlayer, CommonUtilities::GrowingArray<Event*> &eventList);
	void CreatePlaySoundEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList);
	void CreatePickupEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList, Inventory * aInventory, Object &aObject);
	void CreateChangeLevelEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList, Player * aPlayer);
	void CreateSetActiveEvent(picojson::array &events, size_t i, std::string path, CommonUtilities::GrowingArray<Event*> &eventList);

	static JsonParser *ourInstance;
	inline static JsonParser &GetInstance();

	void InitInternalLevels(CommonUtilities::GrowingArray<Level> &aLevels, Inventory *aInventory, Player *aPlayer);
	void InitInternalSettings(Settings &aSettings);
	void InitInternalInterfaces(CU::GrowingArray<InterfaceBase*> &aInterfaces, Inventory* aInventory);
	void InitInternalDialog(DialogManager &aDialogManager);
	void InitInternalPlayer(Player *aPlayer);
	void InitInternalAnimation(BaseAnimatedGameObject &aGameObject, const std::string &anAnimationFile = DefaultAnimationPath);
	void InitInternalSounds(std::map<std::string, std::string> &aSoundsMap);
	void InitInternalActionWheel(ActionWheel *aActionWheel);
	void CreateBeamPuzzle(CommonUtilities::GrowingArray<Object*> &aObjects, Inventory *aInventory, Player *aPlayer);
	void ReadSideWeightData(picojson::array &aValue,
		CommonUtilities::GrowingArray<WeightData*> &aWeightData);
	void ReadVictoryAngleData(picojson::array &aValue, CommonUtilities::GrowingArray<VictoryAngleData*> &aVictoryDataList,
		Inventory *aInventory, Player *aPlayer, std::string &aSpritePath);

	void ValidateJSONValue(picojson::value &aObject, const char *aValidationString, std::string &aPath);
	void ValidateJSONObject(picojson::object &aObject, const char *aValidationString);
	bool DoesValueExist(picojson::value &aObject, const char *aValueName);
	Vector2f JsonParser::GetVector2fPosition(picojson::value &aObject);
};

inline JsonParser& JsonParser::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "JSONParser is nullptr");
	return (*ourInstance);
}
