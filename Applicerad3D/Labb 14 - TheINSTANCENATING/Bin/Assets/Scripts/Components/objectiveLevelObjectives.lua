function self:Initialize()
	self:ActivateObjective("KillObjective")
	
end
local myKillObjectiveActive = true;
local timer = 0
function self:Update(aDeltaTime)
	timer = timer + aDeltaTime
	if (timer >= 2 and myKillObjectiveActive == true) then
		--self:SpawnPrefabAtPosition("TestSpawnEnemy", 0, 0, 0)
		myKillObjectiveActive = false
		self:SaveScene()
		timer = 0
	end
end

function self:ObjectiveCompleteEvent(aEventName)

	if (aEventName == "KillObjective")then
		--self:ActivateObjective("hejsan")
		myKillObjectiveActive = false;
		self:LevelCleared()
	end
	
	if (aEventName == "hejsan") then
		self:LevelCleared()
	end
	
end

function self:OnTrigger()
	self:ActivateObjective("KILL1000NEWLYSPAWNEDENEMIES")
end