--Begin_Box--
--[NodeData][Name:Print]
--[InputPin][Name:In][VarType:impulse]
--[InputPin][Name:In2][VarType:string]
--[OutputPin][Name:Out][VarType:impulse]
--End_Box--

function Prepare()
end

function Run(aCaller, pinIndex)
	Print(GetPinData(aCaller, "In2"))
	--PrintLog(aCaller, GetPinData(aCaller, "In2"));
	ExecutePin("Out", aCaller);
end
