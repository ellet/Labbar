--Begin_Box--
--[NodeData][Name:TargetReachedCallback]
--[InputPin][Name:In][VarType:impulse]
--[OutputPin][Name:Out][VarType:impulse]
--[OutputPin][Name:OnTargetReached][VarType:impulse]
--End_Box--

function Prepare()
end

function Run(aCaller, pinIndex)
	ExecutePin("Out", aCaller);
	RegisterCallback(aCaller, "TargetReached", "OnTargetReached");
end

function OnTargetReached(aCaller)
	ExecutePin("OnTargetReached", aCaller);
end
