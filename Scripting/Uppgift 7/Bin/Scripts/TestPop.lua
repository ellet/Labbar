g_Player = {}

g_Input = {}

g_Enemies = {}

g_EnemiesData = {}

--e_GameState = {}
g_GameOverState = false

--g_GameState = {}

e_Direction = {}
e_Direction.Right = 1
e_Direction.Down = 2
e_Direction.Left = -1
e_Direction.Up = 3

g_ScreenSize = {}
g_ScreenSize.x = 1920
g_ScreenSize.y = 1080






function InitPlayer()
  g_Player.ID = SpawnUnit(aCaller, "Sprites/Player.dds", 345.0, 300.0);
  g_Player.MovementSpeed = 350.0
  g_Player.Projectiles = {}
  g_Player.ProjectileSpeed = 350.0
  g_Player.MaxHeight = 1080 - 300
end

function InitEnemies()
  g_EnemiesData = {}
  g_EnemiesData.StartX = 128
  g_EnemiesData.StartY = 32
  g_EnemiesData.PerRow = 10
  g_EnemiesData.RowAmount = 5
  g_EnemiesData.StartEnemyAmount = g_EnemiesData.PerRow * g_EnemiesData.RowAmount

  g_EnemiesData.XDistance = 128
  g_EnemiesData.YDistance = 82
  g_EnemiesData.CurrentSpeed = 128
  g_EnemiesData.DropHeight = 32
  g_EnemiesData.Direction = e_Direction.Right
  g_EnemiesData.PreviousDirection = e_Direction.Right
  g_EnemiesData.SpeedIncrease = 32
end

function SpawnEnemies()
  g_Enemies = {}
  local spawnX, spawnY = 0, 0
  for iRow = 1, g_EnemiesData.RowAmount do
    for iEnemy = 1, g_EnemiesData.PerRow do
      spawnX = g_EnemiesData.StartX + g_EnemiesData.XDistance * iEnemy
      spawnY = g_EnemiesData.StartY + (g_EnemiesData.YDistance * iRow)

      SpawnEnemy(spawnX, spawnY)
    end
  end

end

function GameInit()
  g_GameOverState = false
  InitPlayer()
  InitEnemies()
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

  local afterX, afterY = GetObjectPosition(aCaller, g_Player.ID)

  if afterY < g_Player.MaxHeight then
    afterY = g_Player.MaxHeight
  elseif afterY > g_ScreenSize.y - 32 then
    afterY = g_ScreenSize.y - 32
  end

  if afterX < 32 then
    afterX = 32
  elseif afterX > g_ScreenSize.x then
    afterX = g_ScreenSize.x
  end

  SetObjectPosition(g_Player.ID, afterX, afterY)

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

function CheckIfTouchingEdge(aCaller, xDelta, yDelta)
  for iEnemy = 1, #g_Enemies do
    local x, y = GetObjectPosition(aCaller, g_Enemies[iEnemy].ID)
    local tempX = x + xDelta

    if y > g_ScreenSize.y then
      g_GameOverState = true
      return true
    end

    if tempX > g_ScreenSize.x or tempX < 0 then
        return true
    end
  end

  return false
end

function MoveEnemy(aEnemyIndex, xDelta, yDelta)
  AddToObjectPosition(g_Enemies[aEnemyIndex].ID, xDelta, yDelta)
end

function EnemyUpdate(aCaller, aDeltaTime)
  local xMovementDelta yMovementDelta = 0, 0

  xMovementDelta = g_EnemiesData.CurrentSpeed * g_EnemiesData.Direction * aDeltaTime

  if CheckIfTouchingEdge(aCaller, xMovementDelta, yMovementDelta) == true then
    yMovementDelta = g_EnemiesData.DropHeight
    xMovementDelta = 0
    g_EnemiesData.Direction = g_EnemiesData.Direction * -1
    g_EnemiesData.CurrentSpeed = g_EnemiesData.CurrentSpeed * 1.2
  end


  for iEnemy = 1, #g_Enemies do
    MoveEnemy(iEnemy, xMovementDelta, yMovementDelta)
  end

end

function CheckCollisions(aCaller)

local projectilesToRemove = {}
local unitsToRemove = {}

for iShoot = #g_Player.Projectiles, 1, -1 do
  local shouldBreak = false
  for iEnemy = #g_Enemies, 1, -1 do
      if CheckCollision(aCaller, g_Enemies[iEnemy].ID, g_Player.Projectiles[iShoot].ID) then
        projectilesToRemove[#projectilesToRemove + 1] = iShoot
        unitsToRemove[#unitsToRemove + 1] = iEnemy

        shouldBreak = true
        break
      end
    end

    if shouldBreak == true then
      break
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
  if g_GameOverState == true then
    Init(aCaller)
  end


  PlayerUpdate(aCaller, aDeltaTime);
  ProjectileUpdate(aCaller, aDeltaTime)
  CheckCollisions(aCaller)

  if (#g_Enemies < 1) then
    g_GameOverState = true
  end

  EnemyUpdate(aCaller, aDeltaTime)

  --if (CheckCollision(PlayterID, enemyID)) then
    --Print("IT COLLIDDEDEDED")
    --local x,y = GetObjectPosition(aCaller, enemyID);
    --x = x + 10
    --SetObjectPosition(enemyID, x, y)
  --end
end
