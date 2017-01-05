using UnityEngine;
using UnityEditor;
using System.Collections;
using System.Collections.Generic;
using System;

public class DropObjectToCollider
{ 
    private const float myRaycastStartHeight = 1000f;
    [MenuItem("Tools/Drop Object Parents to Collider.. &_t")]

    static void DropCollider()
    {
        DropToCollider();
    }
	
    public static void DropToCollider()
    {
        List<GameObject> someObjects = GetSelectionAsGameObjectList();
        for(int indexGameObject = 0; indexGameObject < someObjects.Count; indexGameObject++)
        {
            Undo.RegisterCompleteObjectUndo(someObjects[indexGameObject], "Dropped to collider..");
            DropTargetObjectToCollider(someObjects[indexGameObject]);
        }
    }

    private static void DropTargetObjectToCollider(GameObject gameObject)
    {
        Vector3 rayStartPosition = GetOffsetPosition(gameObject);
        RaycastHit raycastHit;
        int oldLayer = gameObject.layer;

        gameObject.layer = 2;

        if(Physics.Raycast(rayStartPosition, Vector3.down, out raycastHit ))
        {
            Collider hitCollider = raycastHit.collider;
            if(hitCollider !=null)
            {
                Vector3 newPosition = Vector3.zero;
                BoxCollider otherCollider = gameObject.GetComponent<BoxCollider>();

                if(otherCollider !=null)
                {
                    float hitboxOffset = (otherCollider.size.x * gameObject.transform.localScale.x) / 2f;
                    newPosition = new Vector3(raycastHit.point.x, raycastHit.point.y + hitboxOffset, raycastHit.point.z);
                }
                else
                {
                    newPosition = raycastHit.point;
                }

                gameObject.transform.position = newPosition;
            }
        }
        gameObject.layer = oldLayer;
    }

    private static Vector3 GetOffsetPosition(GameObject gameObject)
    {
        return new Vector3(
                            gameObject.transform.position.x,
                            gameObject.transform.position.y + myRaycastStartHeight,
                            gameObject.transform.position.z
                            );
    }

    private static List<GameObject> GetSelectionAsGameObjectList()
    {
        List<GameObject> objectsToDrop = new List<GameObject>();
        for(int indexTransform = 0; indexTransform <Selection.transforms.Length;indexTransform ++)
        {
            objectsToDrop.Add(PrefabUtility.FindPrefabRoot(Selection.transforms[indexTransform].gameObject));
        }
        return objectsToDrop;
    }
}
