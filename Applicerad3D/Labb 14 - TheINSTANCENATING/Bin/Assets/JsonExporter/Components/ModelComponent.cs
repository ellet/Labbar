﻿using UnityEngine;
using System.Collections;
using UnityEditor;

[ExecuteInEditMode]
public class ModelComponent : MonoBehaviour
{
    public string TexturePath = "CURRENTLY UNUSED";
    /*private Object model;

    public void Update()
    {
        model = PrefabUtility.GetPrefabParent(transform.gameObject);
    }*/

    public Object GetModel()
    {
        Object obj = PrefabUtility.GetPrefabParent(transform.gameObject);
        if (obj == null)
        {
            obj = transform.gameObject;
            //return null;
        }
        return ((GameObject)obj).GetComponent<MeshFilter>().sharedMesh;
    }
}
