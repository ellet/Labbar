using UnityEngine;
using System.Collections;
using System.Collections.Generic;


public class ObjectiveHandlerComponent : MonoBehaviour
{
    public List<ListableClass> objectiveChains = new List<ListableClass>();
}

[System.Serializable]
public class ListableClass
{
    public List<Objective> objectives = new List<Objective>();
}

[System.Serializable]
public class Objective
{
    public DialogChain dialogChain;

    public string identity;
    public string description;

    public int counter;
    public int target;
}

[System.Serializable]
public class DialogChain
{
    public List<DialogNode> dialogNodes = new List<DialogNode>();
}

[System.Serializable]
public class DialogNode
{
    public string subtitles;
    public string voiceClip;
    public float trailDelay = 0.0f;
}