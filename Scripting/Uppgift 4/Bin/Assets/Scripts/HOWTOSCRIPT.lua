----------------------------------------------------------------------
--!!!!!!!!!!!!!!!!!!!!!!!!!!EVENTFUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!--
	--Dessa kommer att kallas på när vi skickar en signal från c++
			--Om ni vill ha meddelanden för fler saker, 
			    --fråga en snäll programmerare.



--Kallas på av ett object som har en trigger collider. aObjectName är namnet på objektet som åker in i en.
--ex: ett object i världen skall göra något när spelaren åker nära. Sätt en trigger på objektet och skriv den här funktionen
		--i en lua-fil som du attachar på objektet. Den kommer att kallas på när ett objekt åker in i den. I detta fall ser
		--jag efter om objektets namn är player och gör i så fall saker.
self:OnTrigger(aObjectName)
	if (aObjectName == "Player") then
		--DoStuff
	end
end


--Kallas på av ett objekt som har en health component när hp når 0.
--ex: I detta fallet vill vi göra något coolt när hp når 0
self:ZeroHPEvent()
	--DoStuff
end


--Kallas på när ett objekt med detta skript som komponent skapas. Kan vara bra för att kanske sätta värden eller liknande.
self:Initialize()
	--Initialize stuff
end


--Kallas på när ett objekt med detta skript som komponent uppdateras (sker en gång per frame).
--ex: Här vill vi göra något var femte sekund. Därför uppdateras timern med deltaTime (hur lång tid framen tog på sig)
local timer = 0
self:Update(aDeltaTime)
	timer = timer + aDeltaTime
	
	if (timer > 5) then
		--DoStuff
		timer = 0
	end
end

--Kallas på när ett objekt med detta skript som komponent renderas.
--ex: Finns inget exempel än så länge vad jag vet
self:Render()
	--RenderStuff
end

----------------------------------------------------------------------------------
--!!!!!!!!!!!!!!!!!!!!!!!!!!FUNCTIONS FOR YOU TO CALL!!!!!!!!!!!!!!!!!!!!!!!!!!--
	--Dessa kommer ni att kalla på när ni vill få något gjort i spelet
			--Om ni vill kunna göra fler coola saker, 
			    --fråga en snäll programmerare.
				
--Sparar scenen i dess nuvarande state
self:SaveScene()

--Sätter positionen på objektet som scriptet är attachat till.
--ex: Sätt positionen till x = 10, y = 20 och z = 30
self:SetPosition(10, 20, 30)

--Hämtar positionen på objektet som scriptet är attachat till.
--ex: Spara positionen till de lokala variablerna x, y och z.
x, y, z = self:GetPosition()

--Roterar objektet run som scriptet är attachat till.
--ex: Rotera objektet 10 grader i x, 20 grader i y och 30 grader i z
self:RotateAroundLocal(10, 20, 30)


--Spawnar en prefab (som man tidigare sparat ut i unity genom "Export Prefabs" (Dessa prefabs måste ligga i prefabs-foldern)) på en position
--ex:Spawna prefaben med namnet "myTinyPrefab" på positionen x = 10, y = 20, z = 30.
self:SpawnPrefabAtPosition("myTinyPrefab", 10, 20, 30)

--Spawnar en prefab (som man tidigare sparat ut i unity genom "Export Prefabs" (Dessa prefabs måste ligga i prefabs-foldern)) på en position med en rotation
--ex:Spawna prefaben med namnet "myTinyPrefab" på positionen x = 10, y = 20, z = 30, med rotationen x = 10, y = 20, z = 30 grader.
self:SpawnPrefabAtPositionWithRotation("myTinyPrefab", 10, 20, 30, 10, 20, 30)


--Sätter countern på ett objective med hjälp av en identifier på objektet och ett tal som används som counter.
--ex: Sätt att objectivet "myFancyObjective" får countern 3.
self:ObjectiveSetCounter("myFancyObjective", 3)


--Ökar countern på ett objective med hjälp av en identifier på objektet och ett tal som används som counter-ökning.
--ex: Öka countern på objectivet "myFancyObjective" med 1.
self:ObjectiveIncrementCounter("myFancyObjective", 1)

--Minskar countern på ett objective med hjälp av en identifier på objektet och ett tal som används som counter-minskning.
--ex: Minska countern på objectivet "myFancyObjective" med 1.
self:ObjectiveDecrementCounter("myFancyObjective", 1)

--Aktiverar ett objective så att det kan uppdateras. Detta kommer ske automatiskt om objectivet som ligger före i listan precis blivit avklarat.
	--Det är alltså oftast användbart för att starta en hel chain.
--ex: Aktivera objectivet "myFancyObjective"
self:ActivateObjective("myFancyObjective")

--Hämtar antalet gåner som spelaren har skjutit. (osäker på om den fungerar)
--ex: sparar värdet i en local variabel som heter timesFired
local timesFired = self:GetTimesFired()

--Säger att banan är avklarad och att man kan röra sig vidare till nästa bana
	--I nuläget kommer en prompt som ber spelaren klicka på enter för att gå vidare.
self:LevelCleared()


















