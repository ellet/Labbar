using UnityEngine;
using UnityEditor;
using System.Collections.Generic;
using System;
using System.Collections;

public class GroupTargetObjects
{
    public static bool snapPivotToTerrain = false;
    public static string myTargetName = "NewGroup";

    [MenuItem("Tools/Group Objects.. %_g")]
    static void GroupSelectedObjects()
    {
        GroupObjects();
    }

    [MenuItem("Tools/Ungroup Objects.. #_g")]
    static void UngroupSelectedObjects()
    {
        UngroupObjects();
    }

    public static void GroupObjects()
    {
        Transform[] selectedTransforms = Selection.transforms;
        GameObject newParent = CreateNewParent(selectedTransforms);
        TrySnapParentToTerrain(newParent);
        ParentSelectedObjects(selectedTransforms, newParent);
        Selection.activeTransform = newParent.transform;
    }
    public static void UngroupObjects()
    {
        Transform[] selectedTransforms = Selection.transforms;
        List<Transform> parentsToRemove = new List<Transform>();
        parentsToRemove = FindParents(selectedTransforms);
        RemoveParents(parentsToRemove);
    }
    private static GameObject CreateNewParent(Transform[] someTransforms)
    {
        GameObject newParent = new GameObject();
        newParent.name = myTargetName;
        newParent.tag = "EditorOnly";
        newParent.transform.position = FindPivot(someTransforms);
        return newParent;
    }
    private static void TrySnapParentToTerrain(GameObject newParent)
    {
        if (snapPivotToTerrain == true)
        {
            float newYpos = newParent.transform.position.y;
            newYpos = Terrain.activeTerrain.SampleHeight(new Vector2(newParent.transform.position.x, newParent.transform.position.z));
            newParent.transform.position = new Vector3(newParent.transform.position.x, newYpos, newParent.transform.position.z);
        }
    }
    private static void ParentSelectedObjects(Transform[] someTransformsSelected, GameObject aGameObjectParent)
    {
        for (int i = 0; i<someTransformsSelected.Length; i++)
        {
            Undo.SetTransformParent(someTransformsSelected[i], aGameObjectParent.transform, "Set Target Objects Parent..");
        }
    }
    private static List<Transform> FindParents(Transform[] someTransforms)
    {
        List<Transform> parentsFound = new List<Transform>();
        foreach(Transform t in someTransforms)
        {
            if (t.parent != null)
            {
                if (t.parent.tag == "EditorOnly")
                {
                    if(!parentsFound.Contains(t))
                    {
                        parentsFound.Add(t.parent);
                    }
                }
                if (t.tag == "EditorOnly")
                {
                    if (!parentsFound.Contains(t))
                    {
                        parentsFound.Add(t);
                    }
                }
            }
            else
            {
                if(t.tag == "EditorOnly")
                {
                    if(!parentsFound.Contains(t))
                    {
                        parentsFound.Add(t);
                    }
                }
            }
        }
        return parentsFound;
    }
    public static Vector3 FindPivot(Transform[] trans)
    {
        if (trans == null || trans.Length == 0)
        {
            return Vector3.zero;
        }

        if (trans.Length == 1)
        {
            return trans[0].position;
        }
        float minX = Mathf.Infinity;
        float minY = Mathf.Infinity;
        float minZ = Mathf.Infinity;

        float maxX = Mathf.Infinity;
        float maxY = Mathf.Infinity;
        float maxZ = Mathf.Infinity;

        foreach (Transform tr in trans)
        {
            if (tr.position.x < minX)
            {
                minX = tr.position.x;
            }
            if (tr.position.y < minY)
            {
                minY = tr.position.y;
            }
            if (tr.position.z < minZ)
            {
                minZ = tr.position.z;
            }

            if (tr.position.x > maxX)
            {
                maxX = tr.position.x;
            }
            if (tr.position.y > maxY)
            {
                maxY = tr.position.y;
            }
            if (tr.position.z > maxZ)
            {
                maxZ = tr.position.z;
            }
        }
        Vector3 newPos = new Vector3((minX + maxX) / 2.0f, (minY + maxY) / 2.0f, (minZ + maxZ) / 2.0f);
        return newPos;
    }
    
    private static void RemoveParents(List<Transform> someTransformParents)
    {
        List<GameObject> restGameObjectsToSelect = new List<GameObject>();
        foreach(Transform transformParent in someTransformParents)
        {
            if(transformParent != null)
            {
                restGameObjectsToSelect.AddRange(GetAllChildrenAsGameObjects(transformParent));
                transformParent.DetachChildren();
                GameObject.DestroyImmediate(transformParent.gameObject);
            }
        }
        SelectRestChildrenGameObjects(someTransformParents, restGameObjectsToSelect);
    }
    private static void SelectRestChildrenGameObjects(List<Transform> someTransformParents, List<GameObject> restGameObjectsToSelect)
    {
        foreach (Transform t in someTransformParents)
        {
            if (t!=null)
            {
                restGameObjectsToSelect.Add(t.gameObject);
            }
        }
        Selection.objects = restGameObjectsToSelect.ToArray();
    }
    private static GameObject [] GetAllChildrenAsGameObjects(Transform aTransformParent)
    {
        Transform[] children = aTransformParent.GetComponentsInChildren<Transform>();
        List<GameObject> childrenAsGameObjects = new List<GameObject>();
        foreach(Transform child in children)
        {
            childrenAsGameObjects.Add(child.gameObject);
        }
        return childrenAsGameObjects.ToArray();
    }
}
