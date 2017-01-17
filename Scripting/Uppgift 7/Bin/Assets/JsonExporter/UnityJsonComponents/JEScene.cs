using System;
using System.Collections.Generic;
using Newtonsoft.Json;
using UnityEngine;
using UnityEditor;

public class JEScene : JEObject
{
    public static string sceneName;

    public static JEScene TraversePrefabs()
    {
        var scene = new JEScene();

        List<GameObject> root = new List<GameObject>();

        List<object> prefabs = new List<object>();

        string sAssetFolderPath = "/Prefabs/";
        // Construct the system path of the asset folder 
        string sDataPath = Application.dataPath;
        string sFolderPath = /*sDataPath.Substring(0, sDataPath.Length - 6)*/sDataPath + sAssetFolderPath;
        // get the system file paths of all the files in the asset folder
        string[] aFilePaths = System.IO.Directory.GetFiles(sFolderPath);
        // enumerate through the list of files loading the assets they represent and getting their type

        foreach (string sFilePath in aFilePaths)
        {
            string sAssetPath = sFilePath.Substring(sDataPath.Length - 6);
            //Debug.Log(sAssetPath);

            object objAsset = AssetDatabase.LoadAssetAtPath(sAssetPath, typeof(UnityEngine.Object));

            if (objAsset != null)
            {
                prefabs.Add(objAsset);
            }
            //Debug.Log(objAsset.GetType().Name);
        }
        object[] objects = prefabs.ToArray();

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

    public static JEScene TraverseScene()
    {
        var scene = new JEScene();
        List<GameObject> root = new List<GameObject>();

        // Unity has no root object, so collect root game objects this way

        object[] objects = GameObject.FindObjectsOfType(typeof(GameObject));
        
        //object[] prefabs = GameObject.F
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
