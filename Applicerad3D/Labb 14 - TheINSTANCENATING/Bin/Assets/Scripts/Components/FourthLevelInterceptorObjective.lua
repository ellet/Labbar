function self:Update (aDeltaTime)

end

function self:ZeroHPEvent()
	self:ObjectiveIncrementCounter("FourthLevelInterceptorObjective", 1)
end
