print = PrintToLog

g_elapsedTime = 0.16


g_BodySprite = "Data/Sprites/GridBox.png"
g_HeadSprite = "Data/Sprites/"


function RenderInGrid(aX, aY, aImageToRender)
	RenderImage(aImageToRender, aX, aY)
end

function GameUpdate()

end

function Render()
	RenderInGrid(100, 100, g_BodySprite)
end

function Init()
end

function UpdateHost()

	GameUpdate()
	Render()

	local x,y = GetMousePos()
	if(GetKeyState(0x50)) -- Key P, All keys: data/KeyValues.h
	then
		RenderImage("Data/snake_big.png",x,y)
	end

	--RenderText("Lycka till!",100,100)
end
