using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public enum CollisionFilterID
{
    ePlayer = 1 << 0,
    eEnemy = 1 << 1,
    eEnvironment = 1 << 2,
    eEnemyProjectile = 1 << 3,
    eEnemySwarmer = 1 << 4,
    eDefault = 1 << 5
}

public enum ColliderTypes
{
    Sphere,
    Capsule
}

public class ColliderComponent : MonoBehaviour
{
    public ColliderTypes ColliderType = ColliderTypes.Sphere;
    public Vector3 Center = Vector3.zero;
    public float Radius = 1.0f;
    public Vector3 CapsuleRotation = Vector3.up;
    public float CapsuleLength = 10.0f;
    public bool Trigger = false;
    public bool RenderCollider = true;
    public CollisionFilterID CollisionID = CollisionFilterID.eEnvironment;
    public List<CollisionFilterID> CollisionFilter = new List<CollisionFilterID>{ CollisionFilterID.eDefault };

    [HideInInspector]
    public float radiusDontTouch = 1.0f;
    [HideInInspector]
    public Vector3 centerDontTouch = Vector3.zero;
    [HideInInspector]
    public Vector3 DontTouch = Vector3.zero;
    [HideInInspector]
    public Vector3 OtherDontTouch = Vector3.zero;

    void OnDrawGizmosSelected()
    {
        Vector3 scale = transform.localScale;

        float scaleMultiplier = 1.0f;

        scaleMultiplier = scale.x;
        radiusDontTouch = Radius * scaleMultiplier;
        centerDontTouch = Center * scaleMultiplier;

        float scaledRadius = radiusDontTouch;

        Vector3 renderPosition = transform.position + (transform.rotation * centerDontTouch);

        if (ColliderType == ColliderTypes.Sphere)
        {
            Gizmos.color = Color.green;
            Gizmos.DrawWireSphere(renderPosition, scaledRadius);
        }
        else
        {
            float scaledCapsuleLength = CapsuleLength * scaleMultiplier;

            Quaternion objectRotation =  Quaternion.identity;
            objectRotation.eulerAngles = CapsuleRotation;

            Vector3 localDirectionAndLength = objectRotation * (Vector3.up);
            localDirectionAndLength = localDirectionAndLength * scaledCapsuleLength;


            Quaternion worldRotation = transform.rotation * objectRotation;
            Vector3 worldDirectionAndLength = worldRotation * (Vector3.up);
            worldDirectionAndLength = worldDirectionAndLength * scaledCapsuleLength;

            Vector3 halfLength = worldDirectionAndLength * 0.5f;

            Vector3 firstPosition = renderPosition - (halfLength);
            Vector3 secondPosition = renderPosition + (halfLength);

            Vector3 capsuleDirection = worldDirectionAndLength.normalized;
            Vector3 lengthAndDirectionOfRadius = capsuleDirection * scaledRadius;
            

            DebugExtension.DrawCapsule(firstPosition - lengthAndDirectionOfRadius, secondPosition + lengthAndDirectionOfRadius, Color.green, scaledRadius);

            DontTouch = localDirectionAndLength;
            
            OtherDontTouch = (centerDontTouch) - localDirectionAndLength / 2.0f;
        }
    }
}
