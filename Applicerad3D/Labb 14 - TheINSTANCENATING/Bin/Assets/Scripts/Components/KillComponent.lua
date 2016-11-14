function self:Update (aDeltaTime)

end

function self:ZeroHPEvent()
	self:ObjectiveIncrementCounter("KillObjective", 1)
end
