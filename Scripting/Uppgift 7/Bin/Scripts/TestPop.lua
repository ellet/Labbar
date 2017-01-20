g_Player = {}

g_Input = {}

g_Enemies = {}

function InitPlayer()
  g_Player.ID = SpawnUnit(aCaller, "Sprites/Player.dds", 345.0, 300.0);
  g_Player.MovementSpeed = 150.0
  g_Player.Projectiles = {}
  g_Player.ProjectileSpeed = 350.0
end

function SpawnEnemies()
  SpawnEnemy(300.0, 300.0)
  SpawnEnemy(450.0, 300.0)
  SpawnEnemy(750.0, 300.0)
end

function GameInit()
  InitPlayer()
  SpawnEnemies()

  g_Input.Right = false;
  g_Input.Down = false;
  g_Input.Left = false;
  g_Input.Up = false;

  g_Input.Shoot = false
end

function SpawnEnemy(x, y)
  local enemy = {}

  enemy.ID = SpawnUnit(aCaller, "Sprites/Enemies.dds", x, y);
  g_Enemies[#g_Enemies + 1] = enemy
end

function ShootProjectile(aCaller)
  local projectile = {}
  local x,y = GetObjectPosition(aCaller, g_Player.ID)
  projectile.ID = SpawnUnit(aCaller, "Sprites/Projectile.dds", x, y);

  g_Player.Projectiles[#g_Player.Projectiles + 1] = projectile

end

function Init(aCaller)
  RegisterCallback(aCaller, "KeyPress", "OnKeyPress");

  ClearUnits()
  GameInit()

  --TestPop(10, 13.13, 7.143, "arararaarar", 10034.45093845098)
  --PlayterID = SpawnUnit(aCaller, "Sprites/Player.dds", 345.0, 300.0);
  --enemyID = SpawnUnit(aCaller, "Sprites/Enemies.dds", 125.0, 300.0);


end

function OnKeyPress(aCaller, aKeyIndex)
  if (aKeyIndex == 1) then
    g_Input.Right = true;

  elseif aKeyIndex == 2 then
    g_Input.Down = true;

  elseif aKeyIndex == 3 then
    g_Input.Left = true;

  elseif aKeyIndex == 4 then
    g_Input.Up = true;

  elseif aKeyIndex == 5 then
    g_Input.Shoot = true;

  end
end

function HandleInput(aCaller, aDeltaTime)
  local x,y = 0, 0
  if (g_Input.Right == true) then
    g_Input.Right = false
    x = g_Player.MovementSpeed

  end

  if (g_Input.Left == true) then
    g_Input.Left = false
    x = -g_Player.MovementSpeed

  end

  if (g_Input.Up == true) then
    g_Input.Up = false
    y = -g_Player.MovementSpeed

  end

  if (g_Input.Down == true) then
    g_Input.Down = false
    y = g_Player.MovementSpeed

  end

  if (g_Input.Shoot == true) then
    g_Input.Shoot = false
    ShootProjectile(aCaller);

  end

  local deltaX = x * aDeltaTime
  local deltaY = y * aDeltaTime

  AddToObjectPosition(g_Player.ID, deltaX, deltaY)

end

function PlayerUpdate(aCaller, aDeltaTime)
  HandleInput(aCaller, aDeltaTime)
end

function RemoveEnemy(aIndexOfEnemy)
  RemoveUnit(g_Enemies[aIndexOfEnemy].ID)

  local lastIndex = #g_Enemies
  for iEnemy = aIndexOfEnemy, #g_Enemies - 1 do
    g_Enemies[iEnemy] = g_Enemies[iEnemy + 1]
  end

  g_Enemies[lastIndex] = nil
end

function RemoveProjectile(IndexOfProjectile)
  RemoveUnit(g_Player.Projectiles[IndexOfProjectile].ID)

  local lastIndex = #g_Player.Projectiles
  for iShoot = IndexOfProjectile, #g_Player.Projectiles - 1 do
    g_Player.Projectiles[iShoot] = g_Player.Projectiles[iShoot + 1]
  end

  g_Player.Projectiles[lastIndex] = nil

end

function ProjectileUpdate(aCaller, aDeltaTime)

local deltaY = -g_Player.ProjectileSpeed * aDeltaTime

  local projectilesToRemove = {}
  for iShoot = #g_Player.Projectiles, 1, - 1  do
    Print(iShoot)
    AddToObjectPosition(aCaller, g_Player.Projectiles[iShoot].ID, 0, deltaY)

    local x,y = GetObjectPosition(g_Player.Projectiles[iShoot].ID)
    if y < 0.0 then
      projectilesToRemove[#projectilesToRemove + 1] = iShoot
    end
  end

  for iShoot = 1, #projectilesToRemove do
    RemoveProjectile(projectilesToRemove[iShoot])
  end

end

function CheckCollisions(aCaller)

local projectilesToRemove = {}
local unitsToRemove = {}

  for iEnemy = #g_Enemies, 1, -1 do
    for iShoot = #g_Player.Projectiles, 1, -1 do
      if CheckCollision(aCaller, g_Enemies[iEnemy].ID, g_Player.Projectiles[iShoot].ID) then
        projectilesToRemove[#projectilesToRemove + 1] = iShoot
        unitsToRemove[#unitsToRemove + 1] = iEnemy
      end
    end
  end

  for iShoot = 1, #projectilesToRemove do
    RemoveProjectile(projectilesToRemove[iShoot])
  end

  for iEnemy = 1, #unitsToRemove do
    RemoveEnemy(unitsToRemove[iEnemy])
  end

end

function Update(aCaller, aDeltaTime)
  PlayerUpdate(aCaller, aDeltaTime);
  ProjectileUpdate(aCaller, aDeltaTime)
  CheckCollisions(aCaller)

  --if (CheckCollision(PlayterID, enemyID)) then
    --Print("IT COLLIDDEDEDED")
    --local x,y = GetObjectPosition(aCaller, enemyID);
    --x = x + 10
    --SetObjectPosition(enemyID, x, y)
  --end
end
