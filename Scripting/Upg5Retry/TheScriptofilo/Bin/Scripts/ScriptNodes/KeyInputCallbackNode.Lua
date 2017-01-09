--Begin_Box--
--[NodeData][Name:KeyInputCallback]
--[InputPin][Name:In][VarType:impulse]
--[OutputPin][Name:Out][VarType:impulse]
--[OutputPin][Name:OnKeyPress][VarType:impulse]
--End_Box--

function Prepare()
end

function Run(aCaller, pinIndex)
	ExecutePin("Out", aCaller);
	RegisterCallback(aCaller, "KeyPress", "OnKeyPress");
end

function OnKeyPress(aCaller)
	ExecutePin("OnKeyPress", aCaller);
end