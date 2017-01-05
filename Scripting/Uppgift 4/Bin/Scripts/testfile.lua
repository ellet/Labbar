RegisterCallback("VolumeEnter","OnVolumeEnter")
RegisterCallback("VolumeExit","OnVolumeExit")
--RegisterCallback("Voruga","OnVolumeE")

function Init()
end

function Update(aFirst)

end

function OnVolumeEnter(aObjectID, aVolumeID)
  print("Object with ID: " .. tostring(aObjectID) .. " Entered Volume with ID " .. tostring(aVolumeID))
end

function OnVolumeExit(aObjectID, aVolumeID)
  print("Object with ID: " .. tostring(aObjectID) .. " Exited Volume with ID " .. tostring(aVolumeID))
end
