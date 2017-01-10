--Begin_Box--
--[NodeData][Name:MoveToFreeVolume]
--[InputPin][Name:In][VarType:impulse]
--[OutputPin][Name:Out][VarType:impulse]

--End_Box--

function Prepare()
end

function Run(aCaller, pinIndex)
	ExecutePin("Out", aCaller);
	MoveToFreeVolume(GetCurrentObjectID(aCaller));
end
