using UnityEngine;
using System.Collections;

public class PointLightComponent : MonoBehaviour {

    public float Radius = 4.0f;

    public Color Color;

    void OnDrawGizmosSelected()
    {
        Gizmos.color = Color.yellow;
        Gizmos.DrawWireSphere(transform.position, Radius);
    }

}
