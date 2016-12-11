print = PrintToLog

KeyValues =
{
	KLeft = 0x25,
	KUp = 0x26,
	KRight = 0x27,
	KDown = 0x28,
	KEnter = 0x0D,
	KCTRL = 0x11,

	KA = 0x41,
	KS = 0x53,
	KD = 0x44,
	KW = 0x57
}

DirectionEnum =
{
	Up = 0,
	Right = 1,
	Down = 2,
	Left = 3
}

g_AIState = true
g_AIUpdated = false
g_AIDirection = DirectionEnum.Right
g_AIFlipUpdate = false

g_WinState = false
g_LoseState = false

g_elapsedTime = 0.016

g_AIUpdateRate = 0.00000000000000001
g_UpdateRate = 0.1
g_UpdateTimer = g_UpdateRate

g_FlipRate = 1

g_FlipTimer = g_FlipRate

g_XGridSize = 16
g_YGridSize = 16
g_GridCount = g_XGridSize * g_YGridSize


g_BackgroundSprite = "Data/Sprites/Background.png"

g_HeadUpSprite = "Data/Sprites/HeadUp.png"
g_HeadRightSprite = "Data/Sprites/HeadRight.png"
g_HeadDownSprite = "Data/Sprites/HeadDown.png"
g_HeadLeftSprite = "Data/Sprites/HeadLeft.png"
g_SnakeBodySprite = "Data/Sprites/SnakeBody.png"

g_FoodSprite = "Data/Sprites/EatyTihngy.png"
g_BoxSprite = "Data/Sprites/GridBox.png"

g_FruitData = {}
g_PlayerData = {}

g_LoseSprite = "Data/Sprites/LoseScreen.png"
g_WinSprite = "Data/Sprites/WinScreen.png"




function StartUp()

	g_PlayerData.currentX = g_XGridSize / 2
	g_PlayerData.currentY = 2
	g_PlayerData.previousX = g_XGridSize / 2
	g_PlayerData.previousY = 1
	g_PlayerData.currentPlayerHead = g_HeadDownSprite
	g_PlayerData.currentDirection = 2

	g_PlayerData.previousDirection = 2

	g_PlayerData.Score = 0
	g_PlayerData.SegmentCount = 1
	g_PlayerData.SegmentsX = { g_XGridSize / 2 }
	g_PlayerData.SegmentsY = { 1 }

	g_FruitData.xPos = 4
	g_FruitData.yPos = 3
	g_FruitData.Sprite = g_FoodSprite

	g_LoseState = false
	g_WinState = false
	g_AIUpdated = false
end
StartUp()

function InputCheck()
	if GetKeyState(KeyValues.KCTRL) and g_AIFlipUpdate == false then
		g_AIState = not g_AIState
		g_AIFlipUpdate = true
	end


		if g_AIState == true then
			if g_AIUpdated == false then
				g_AIUpdated = true

				g_PlayerData.currentDirection = g_AIDirection

				if g_PlayerData.currentX >= g_XGridSize and g_AIDirection == DirectionEnum.Right then
					g_PlayerData.currentDirection = DirectionEnum.Down
					g_AIDirection = DirectionEnum.Left

				elseif g_PlayerData.currentX <= 1 and g_AIDirection == DirectionEnum.Left then
					g_PlayerData.currentDirection = DirectionEnum.Down
					g_AIDirection = DirectionEnum.Right
				end
			end
		else
		if (((GetKeyState(KeyValues.KLeft) == true or (GetKeyState(KeyValues.KA) == true)) and g_PlayerData.previousDirection ~= DirectionEnum.Right)) then
			g_PlayerData.currentDirection = DirectionEnum.Left
			g_PlayerData.currentPlayerHead = g_HeadLeftSprite

		elseif (((GetKeyState(KeyValues.KRight) or (GetKeyState(KeyValues.KD) == true)) and g_PlayerData.previousDirection ~= DirectionEnum.Left)) then
			g_PlayerData.currentDirection = DirectionEnum.Right
			g_PlayerData.currentPlayerHead = g_HeadRightSprite

		elseif (((GetKeyState(KeyValues.KUp) or (GetKeyState(KeyValues.KW) == true)) and g_PlayerData.previousDirection ~= DirectionEnum.Down)) then
			g_PlayerData.currentDirection = DirectionEnum.Up
			g_PlayerData.currentPlayerHead = g_HeadUpSprite

		elseif (((GetKeyState(KeyValues.KDown) or (GetKeyState(KeyValues.KS)) == true) and g_PlayerData.previousDirection ~= DirectionEnum.Up)) then
			g_PlayerData.currentDirection = DirectionEnum.Down
			g_PlayerData.currentPlayerHead = g_HeadDownSprite

		end
	end
end

function AddSegemnt()
	g_PlayerData.Score = g_PlayerData.Score + 100
	g_PlayerData.SegmentCount = g_PlayerData.SegmentCount + 1
	g_PlayerData.SegmentsX[g_PlayerData.SegmentCount] = g_PlayerData.SegmentsX[g_PlayerData.SegmentCount - 1]
	g_PlayerData.SegmentsY[g_PlayerData.SegmentCount] = g_PlayerData.SegmentsY[g_PlayerData.SegmentCount - 1]
end

function SegmentsUpdate()

	for iSegment = g_PlayerData.SegmentCount, 1, -1
	do
		g_PlayerData.SegmentsX[iSegment+1] = g_PlayerData.SegmentsX[iSegment]
		g_PlayerData.SegmentsY[iSegment+1] = g_PlayerData.SegmentsY[iSegment]
	end

	g_PlayerData.SegmentsX[1] = g_PlayerData.previousX
	g_PlayerData.SegmentsY[1] = g_PlayerData.previousY
end

function SnakeUpdate()

	g_PlayerData.previousX = g_PlayerData.currentX
	g_PlayerData.previousY = g_PlayerData.currentY
	g_PlayerData.previousDirection = g_PlayerData.currentDirection
	g_AIUpdated = false

	if (DirectionEnum.Left == g_PlayerData.currentDirection) then
		g_PlayerData.currentX = g_PlayerData.currentX - 1

	elseif (DirectionEnum.Right == g_PlayerData.currentDirection) then
		g_PlayerData.currentX = g_PlayerData.currentX + 1

	elseif (DirectionEnum.Up == g_PlayerData.currentDirection) then
		g_PlayerData.currentY = g_PlayerData.currentY - 1

	else
		g_PlayerData.currentY = g_PlayerData.currentY + 1
	end

	if g_PlayerData.currentX > g_XGridSize then
		g_PlayerData.currentX = 1

	elseif g_PlayerData.currentX < 1 then
		g_PlayerData.currentX = g_XGridSize
	end

	if g_PlayerData.currentY > g_YGridSize then
		g_PlayerData.currentY = 1

	elseif g_PlayerData.currentY < 1 then
		g_PlayerData.currentY = g_YGridSize
	end

	SegmentsUpdate()
end

function CollisionTestAgainstSegments(aX, aY)
	for iSegment = 1, g_PlayerData.SegmentCount
	do
		if aX == g_PlayerData.SegmentsX[iSegment] and aY == g_PlayerData.SegmentsY[iSegment] then
			return true
		end
	end

	return false
end

function CollisionTestAgainstSnake(aX, aY)
	if aX == g_PlayerData.currentX and aY == g_PlayerData.currentY then
		return true
	end

	return CollisionTestAgainstSegments(aX, aY)
end

function SpawnFruit()

	if g_PlayerData.SegmentCount < g_GridCount then
		local freeNotFound = true
		while freeNotFound == true do
			local testPosX, testPosY = math.random(g_XGridSize), math.random(g_YGridSize)

			if CollisionTestAgainstSnake(testPosX, testPosY) == false then
				freeNotFound = false
				g_FruitData.xPos = testPosX
				g_FruitData.yPos = testPosY
			end
		end
	end
end


function FruitCollisionTest()
	if g_FruitData.xPos == g_PlayerData.currentX and g_FruitData.yPos == g_PlayerData.currentY then
		return true
	end
	return false
end

function LoseStateCheck()
	if CollisionTestAgainstSegments(g_PlayerData.currentX, g_PlayerData.currentY) == true then
		g_LoseState = true;
	end
end

function WinStateCheck()
	if g_PlayerData.SegmentCount >= g_GridCount then
		g_WinState = true
	end
end

function GameUpdate()
	InputCheck()

	if g_AIFlipUpdate == true then
		g_FlipTimer = g_FlipTimer - g_elapsedTime
		if g_FlipTimer <= 0 then
			g_FlipTimer = g_FlipRate
			g_AIFlipUpdate = false
		end
	end

	if (g_LoseState == false) and (g_WinState == false) then
		g_UpdateTimer = g_UpdateTimer - g_elapsedTime
		if g_UpdateTimer < 0 then
			if g_AIState == true then
				g_UpdateTimer = g_AIUpdateRate
			else
				g_UpdateTimer = g_UpdateRate
			end

			SnakeUpdate()




			if FruitCollisionTest() == true then
				AddSegemnt()
				SpawnFruit()
				WinStateCheck()
			end

			if g_WinState == false then
				LoseStateCheck()
			end

		end
	else
		if (GetKeyState(KeyValues.KEnter) == true) then
			StartUp()
		end
	end

	RenderText("Score: " .. g_PlayerData.Score,1150,125)

	local aistate = "on"

	if g_AIState == false then
		aistate = "off"
	end

	RenderText("AImode is: " .. aistate,1150,175)

if g_AIFlipUpdate == false then

	RenderText("Press CTRL to ", 1150, 200)
	RenderText("Flip AI mode ", 1150, 225)
end

	RenderText("Controls: ", 1150, 300)
	RenderText("Arrow keys or" , 1150, 325)
	RenderText("WASD" , 1150, 350)
end




function RenderInGrid(aX, aY, aImageToRender)
	RenderImage(aImageToRender, (aX * 64) + 32, (aY * 64) + 32)
end

function RenderPlayer()
	RenderInGrid(g_PlayerData.currentX, g_PlayerData.currentY, g_PlayerData.currentPlayerHead)

	for iSegment = 1, g_PlayerData.SegmentCount, 1
	do
		RenderInGrid(g_PlayerData.SegmentsX[iSegment], g_PlayerData.SegmentsY[iSegment], g_SnakeBodySprite)
	end
end

function Render()
RenderImage(g_BackgroundSprite,690,550)

	for iXAxis = 1, g_XGridSize, 1
	do
		for iYAxis = 1, g_YGridSize, 1
		do
			RenderInGrid(iXAxis, iYAxis, g_BoxSprite)
		end
	end

	RenderInGrid(g_FruitData.xPos, g_FruitData.yPos, g_FruitData.Sprite)

	RenderPlayer()

	if g_LoseState == true then
		RenderImage(g_LoseSprite,690,550)
	elseif g_WinState == true then
		RenderImage(g_WinSprite,690,550)
	end
end

function Init()
	math.math.randomseed(3)

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
