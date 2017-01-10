using UnityEngine;
using UnityEditor;
using System.Collections.Generic;
using System.Collections;

public class SetColliderSizeTool
{
    [MenuItem("Tools/Set Collider Size &_b")]
    static void ScaleCollider()
    {
        List<GameObject> gameObjectsToChange = new List<GameObject>();
        gameObjectsToChange.AddRange(Selection.gameObjects);
        foreach(GameObject targetGameObject in gameObjectsToChange)
        {
            if(targetGameObject.GetComponent<Terrain>() == null && targetGameObject.GetComponent<ColliderComponent>() != null)
            {
                List<ColliderComponent> collidersToChange = new List<ColliderComponent>();
                collidersToChange.AddRange(targetGameObject.GetComponents<ColliderComponent>());
                foreach (ColliderComponent targetCollider in collidersToChange)
                {
                    Undo.RegisterCompleteObjectUndo(targetGameObject.gameObject, "Set Collider Size...");
                    float scaleValueMultiplier = SetColliderSizeToolWindow.myValueToScaleColliders;
                    targetCollider.Radius = targetCollider.Radius * scaleValueMultiplier;
                    targetCollider.Center.x = targetCollider.Center.x * scaleValueMultiplier;
                    targetCollider.Center.y = targetCollider.Center.y * scaleValueMultiplier;
                    targetCollider.Center.z = targetCollider.Center.z * scaleValueMultiplier;
                    targetCollider.CapsuleLength = targetCollider.CapsuleLength * scaleValueMultiplier;
                    
                }
            }
        }
    }
}
