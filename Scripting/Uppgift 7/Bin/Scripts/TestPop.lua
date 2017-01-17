PlayterID = 0
enemyID = 0


function Init(aCaller)
  ClearUnits();
  TestPop(10, 13.13, 7.143, "arararaarar", 10034.45093845098)
  PlayterID = SpawnUnit(aCaller, "Sprites/Player.dds", 345.0, 300.0);
  enemyID = SpawnUnit(aCaller, "Sprites/Enemies.dds", 125.0, 300.0);
  RegisterCallback(aCaller, "KeyPress", "OnKeyPress");


end

function OnKeyPress(aCaller, aKeyIndex)
  if (aKeyIndex == 1) then
    --print ("Right Key Pressed")
    AddToObjectPosition(PlayterID, 1, 0);
  elseif aKeyIndex == 2 then
    --print ("Down Key Pressed")
    AddToObjectPosition(PlayterID, 0, 1);
  elseif aKeyIndex == 3 then
    --print ("Left Key Pressed")
    AddToObjectPosition(PlayterID, -1, 0);
  else
    --print ("Up Key Pressed")
    AddToObjectPosition(PlayterID, 0, -1);
  end
end

function Update(aCaller)
  if (CheckCollision(PlayterID, enemyID)) then
    Print("IT COLLIDDEDEDED")
    local x,y = GetObjectPosition(aCaller, enemyID);
    x = x + 10
    SetObjectPosition(enemyID, x, y)
  end
end
