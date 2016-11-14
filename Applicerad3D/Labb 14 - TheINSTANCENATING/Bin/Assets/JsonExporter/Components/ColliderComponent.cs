using UnityEngine;
using System.Collections;

public class ColliderComponent : MonoBehaviour
{
    public Vector3 Center = Vector3.zero;
    public float Radius = 1.0f;
    public bool Trigger = false;
    public bool RenderCollider = true;
    void OnDrawGizmosSelected()
    {
        Gizmos.color = Color.green;
        Gizmos.DrawWireSphere(transform.position + Center, Radius);
    }
}
