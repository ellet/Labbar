function self:Update (aDeltaTime)

end

function self:ZeroHPEvent()
	self:ObjectiveIncrementCounter("FirstLevelMinesObjective", 1)
end
