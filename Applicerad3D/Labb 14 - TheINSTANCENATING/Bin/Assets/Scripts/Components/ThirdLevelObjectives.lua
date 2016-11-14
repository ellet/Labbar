function self:Initialize()
	self:ActivateObjective("ThirdLevelKillInterceptors")
	
end
local timer = 0
function self:Update(aDeltaTime)
	timer = timer + aDeltaTime
	if (timer >= 2) then
		--self:SpawnPrefabAtPosition("TestSpawnEnemy", 0, 0, 0)
		timer = 0
	end
end

function self:ObjectiveCompleteEvent(aEventName)

	if (aEventName == "ThirdLevelKillInterceptors")then
		self:LevelCleared()
	end
	
end

function self:OnTrigger()
	--self:ActivateObjective("derp")
end