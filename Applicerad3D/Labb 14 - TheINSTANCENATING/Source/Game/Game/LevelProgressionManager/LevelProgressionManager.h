#pragma once
#include "Game/Player/PlayerDataStruct.h"
#include <Engine/GenericEngineMessages.h>

struct LevelClearedMessage;
struct ProgressToNextLevelMessage;
struct SelectedLevelMessage;
struct ReloadToLastSaveMessage;

class LevelProgressionManager : public SB::Subscriber<ProgressToNextLevelMessage>, public SB::Subscriber<SelectedLevelMessage>, public SB::Subscriber<SB::EndOfFrameMessage>
	,public SB::Subscriber<ReloadToLastSaveMessage>, public SB::Subscriber <SaveLevelMessage>
{
public:
	LevelProgressionManager();
	~LevelProgressionManager();

	virtual SB::ReceiveResult Receive(const ProgressToNextLevelMessage & aMessage) override; //Maybe remove and add CreateLevelClearedScene where this message is created
	virtual SB::ReceiveResult Receive(const SelectedLevelMessage & aMessage) override;
	virtual SB::ReceiveResult Receive(const SB::EndOfFrameMessage & aMessage) override;
	virtual SB::ReceiveResult Receive(const ReloadToLastSaveMessage &aMessage)override;
	virtual SB::ReceiveResult Receive(const SaveLevelMessage &aMessage)override;
private:
	void LoadData();
	void LoadLevelPaths(SB::DataNode aLevelPathsNode);
	void LoadPlayerData(SB::DataNode aPlayerDataNode);

		
	std::string myCurrentSavedFile;
	SB::GrowingArray<std::string> myLevelFilePaths;
	std::unordered_map<std::string, SavedPlayerData> mySavedPlayerData;
	unsigned short myCurrentLevel;
	bool myProgressToNextLevel;
	bool myLoadLastSave;
};
