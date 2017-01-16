print = PrintToLog

g_elapsedTime = 0.16
function Init()
end 

function UpdateHost()
	local x,y = GetMousePos()
	if(GetKeyState(0x50)) -- Key P, All keys: data/KeyValues.h
	then
		RenderImage("Data/snake_big.png",x,y)
	end
	RenderText("Lycka till!",100,100)
end

