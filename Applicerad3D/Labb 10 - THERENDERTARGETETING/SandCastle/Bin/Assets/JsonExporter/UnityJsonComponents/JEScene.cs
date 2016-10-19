using System;
using System.Collections.Generic;
using Newtonsoft.Json;
using UnityEngine;
using UnityEditor;

public class JEScene : JEObject
{
    public static string sceneName;

    public static JEScene TraverseScene()
    {
        var scene = new JEScene();
        List<GameObject> root = new List<GameObject>();

        // Unity has no root object, so collect root game objects this way
        object[] objects = GameObject.FindObjectsOfType(typeof(GameObject));
        foreach (object o in objects)
        {
            GameObject go = (GameObject)o;

            if (go.transform.parent == null)
                root.Add(go);
        }
        if (root.Count == 0)
        {
            ExportError.FatalError("Cannot Export Empty Scene");
        }
        // traverse the "root" game objects, collecting child game objects and components
        foreach (var go in root)
        {
            scene.rootGameObjects.Add(Traverse(go));
        }

        return scene;
    }

    public void Init()
    {
        foreach (var jgo in rootGameObjects)
        {
            jgo.Init();
        }
    }

    List<JEGameObject> rootGameObjects = new List<JEGameObject>();

    static JEGameObject Traverse(GameObject obj, JEGameObject jparent = null)
    {
        JEGameObject jgo = new JEGameObject(obj, jparent);

        foreach (Transform child in obj.transform)
        {
            Traverse(child.gameObject, jgo);
        }

        return jgo;
    }

    public new JSONScene ToJSON()
    {
        var json = new JSONScene();
        json.name = sceneName;
        json.hierarchy = new List<JSONGameObject>();
        foreach (var go in rootGameObjects)
        {
            json.hierarchy.Add(go.ToJSON());
        }
        return json;
    }
}

public class JSONScene
{
    public string name;
    public List<JSONGameObject> hierarchy;
}