using UnityEngine;
using System.Collections;
using System.Collections.Generic;


[System.Serializable]
public class WaveEncounter
{
    public string enemyPrefab;
    public float spawnDelay = 0.0f;
    public short spawnPointIndex = 0;
    public bool randomizeSpawnPoint = true;
}

[System.Serializable]
public class Wave
{
    public List<WaveEncounter> waveEncounters = new List<WaveEncounter>();
    public short spawnCap;
}

public class WaveManagerComponent : MonoBehaviour
{
    public List<Wave> waves = new List<Wave>();
}
