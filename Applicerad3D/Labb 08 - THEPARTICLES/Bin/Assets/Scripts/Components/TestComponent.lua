function self:Initialize ()
	
end

function self:Update (aDeltaTime)
	local speed = 0.0
	
	local x, y, z = self:GetPosition ()
	--x = x + speed * aDeltaTime
	z = z - speed * aDeltaTime
	self:SetPosition(x, y, z)
end

function self:Render ()
	-- Render immersive 3D world
end