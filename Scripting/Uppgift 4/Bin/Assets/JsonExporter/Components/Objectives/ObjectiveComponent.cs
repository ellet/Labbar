using UnityEngine;
using System.Collections;


public enum ObjectiveType
{
    BossObjective,
    DefendObjective,
    AttackObjective
}

public class ObjectiveComponent : MonoBehaviour
{
    public string identity;
    public ObjectiveType objectiveType = ObjectiveType.AttackObjective;
   
}
