using UnityEngine;
using System.Collections;

public class PlayerControllerComponent : MonoBehaviour
{
    public bool RestrictPlayer = false;
    public Vector3 CenterPosition = Vector3.zero;
    public float GameAreaRadius = 1000.0f;
    public bool DrawGameAreaSolid = false;

    void OnDrawGizmosSelected()
    {

        Gizmos.color = Color.green;
        if (DrawGameAreaSolid == false)
        {
            Gizmos.DrawWireSphere(CenterPosition, GameAreaRadius);
        }
        else
        {
            Gizmos.DrawSphere(CenterPosition, GameAreaRadius);
        }
    }
}
