function self:Update (aDeltaTime)

end

function self:ZeroHPEvent()
	self:ObjectiveIncrementCounter("SecondLevelInterceptorObjective", 1)
end
