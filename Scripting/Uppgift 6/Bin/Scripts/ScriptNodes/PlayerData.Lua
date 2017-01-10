--Begin_Box--
--[NodeData][Name:PlayerData]
--[InputPin][Name:In][VarType:impulse]
--[InputPin][Name:PlayerPointer][VarType:string]
--[OutputPin][Name:Out][VarType:impulse]
--[OutputPin][Name:Health][VarType:int]
--[OutputPin][Name:Name][VarType:string]
--[OutputPin][Name:ID][VarType:string]
--[OutputPin][Name:EquippedWeapon][VarType:string]
--End_Box--

function Prepare()
end

function Run(aCaller, pinIndex)
	ExecutePin("Out", aCaller);
end
