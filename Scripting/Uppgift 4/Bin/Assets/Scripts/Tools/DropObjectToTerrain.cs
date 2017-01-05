using UnityEngine;
using UnityEditor;
using System.Collections;
using System.Collections.Generic;
using System;

public class DropObjectToTerrain
{
    private const float myRaycastStartHeight = 1000f;
    [MenuItem("Tools/Drop Object Parents to Terrain... &_r")]

    static void DropTerrain()
    {
        DropToTerrain();
    }

    public static void DropToTerrain()
    {
        List <GameObject> myObjects = GetSelectionAsGameObjectList();
        for (int indexGameObject = 0; indexGameObject < myObjects.Count; indexGameObject++)
        {
            Undo.RegisterCompleteObjectUndo(myObjects[indexGameObject], "Dropped to ground..");
            DropTargetObjectToTerrain(myObjects[indexGameObject]);
        }
    }

    private static void DropTargetObjectToTerrain(GameObject aGameObject)
    {
        Vector3 oldPosition = aGameObject.transform.position;
        float yPosition = 0;
        yPosition = aGameObject.transform.position.y + myRaycastStartHeight;
        aGameObject.transform.position = new Vector3(aGameObject.transform.position.x, yPosition, aGameObject.transform.position.z);
        RaycastHit raycastHit;
        {
            if(Physics.Raycast(aGameObject.transform.position,Vector3.down, out raycastHit))
            {
                TrySetPosition(aGameObject, raycastHit);
            }
            else
            {
                aGameObject.transform.position = oldPosition;
            }
        }
    }

    private static void TrySetPosition(GameObject aGameObject, RaycastHit raycastHit)
    {
        Terrain terrain = raycastHit.collider.gameObject.GetComponent<Terrain>();
        Vector3 moveToPosition = raycastHit.point;
        if(terrain!=null)
        {
            moveToPosition.y = terrain.SampleHeight(raycastHit.point);
            moveToPosition += new Vector3(0, terrain.transform.position.y, 0);
            aGameObject.transform.position = moveToPosition;
        }
    }

    private static List <GameObject> GetSelectionAsGameObjectList()
    {
        List <GameObject> objectsToDrop = new List<GameObject>();
        for(int indexTransform = 0; indexTransform<Selection.transforms.Length; indexTransform++)
        {
            objectsToDrop.Add(PrefabUtility.FindPrefabRoot(Selection.transforms[indexTransform].gameObject));
        }
        return objectsToDrop;
    }
}
