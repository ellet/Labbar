function self:Initialize()

	self:ActivateObjective("FirstLevelMinesObjective")
	
end
local timer = 0
function self:Update(aDeltaTime)
	timer = timer + aDeltaTime
	if (timer >= 2 and myKillObjectiveActive == true) then
		--self:SpawnPrefabAtPosition("Interceptor", 0, 0, 0)
		timer = 0
	end
end

function self:ObjectiveCompleteEvent(aEventName)
	if (aEventName == "FirstLevelMinesObjective")then
        self:SpawnPrefabAtPosition("Interceptor",43,-154,120)
		self:LevelCleared()
	end
	
end

function self:OnTrigger()
	self:ActivateObjective("derp")
end