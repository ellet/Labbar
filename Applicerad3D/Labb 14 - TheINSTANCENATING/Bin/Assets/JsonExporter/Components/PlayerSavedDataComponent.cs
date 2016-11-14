using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class PlayerSavedDataComponent : MonoBehaviour
{
    PlayerSavedDataComponent()
    {
        bool MiniGun = true;
        OwnedPrimaryWeapons.Add(MiniGun);
        OwnedPrimaryWeapons.Add(false);
        OwnedSecondaryWeapons.Add(true);
        OwnedSecondaryWeapons.Add(false);
    }


    public float StartingHealth;
    public List<bool> OwnedPrimaryWeapons = new List<bool>();
    public List<bool> OwnedSecondaryWeapons = new List<bool>();
}
