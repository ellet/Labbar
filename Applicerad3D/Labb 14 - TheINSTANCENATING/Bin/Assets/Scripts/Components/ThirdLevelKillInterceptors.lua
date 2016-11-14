function self:Update (aDeltaTime)

end

function self:ZeroHPEvent()
	self:ObjectiveIncrementCounter("ThirdLevelKillInterceptors", 1)
end
