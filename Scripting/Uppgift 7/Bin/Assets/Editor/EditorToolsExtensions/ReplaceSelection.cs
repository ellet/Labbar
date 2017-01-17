using UnityEngine;
using UnityEditor;
using System.Collections;
using System.Collections.Generic;
 
public class ReplaceSelection : ScriptableWizard
{
	static GameObject replacement;
	static GameObject[] saveList;
    static bool keep = false;
 
    public GameObject[] ReplaceObjects;
    public bool KeepOriginals = false;
 
    [MenuItem("Tools/Replace Selection... %&#s")]
    static void CreateWizard()
    {
		GameObject[] gameObjects = Selection.gameObjects;
		List<GameObject> foundObjects = new List<GameObject>();

		for (int i = 0; i < gameObjects.Length; i++)
		{
			if (!gameObjects[i].activeInHierarchy)
			{
				foundObjects.Add(gameObjects[i]);
			}
		}

		if (foundObjects.Count > 0)
		{
			saveList = foundObjects.ToArray();
		}

        ScriptableWizard.DisplayWizard(
            "Replace Selection", typeof(ReplaceSelection), "Replace", "Reset");
    }
 
    public ReplaceSelection()
    {
        ReplaceObjects = saveList;
		if (ReplaceObjects == null)
		{
			GameObject[] arr = {null};
			ReplaceObjects = arr;
		}
        KeepOriginals = keep;
    }
 
    void OnWizardUpdate()
    {
		saveList = ReplaceObjects;
        keep = KeepOriginals;
    }

	void OnWizardOtherButton()
	{
		GameObject[] newArr = {};

		ReplaceObjects = newArr;
	}
 
    void OnWizardCreate()
    {
        if (ReplaceObjects.Length == 0)
		{
			return;
		}
 
        //Undo.RegisterSceneUndo("Replace Selection");
 
        Transform[] transforms = Selection.GetTransforms(
            SelectionMode.TopLevel | SelectionMode.OnlyUserModifiable);

        foreach (Transform t in transforms)
        {
            GameObject g;
			replacement = GetPrefab();
            PrefabType pref = PrefabUtility.GetPrefabType(replacement);
 
            if (pref == PrefabType.Prefab || pref == PrefabType.ModelPrefab)
            {
                g = (GameObject)PrefabUtility.InstantiatePrefab(replacement);
            }
            else
            {
                g = (GameObject)Editor.Instantiate(replacement);
            }
 
            Transform gTransform = g.transform;
            gTransform.parent = t.parent;
            g.name = replacement.name;
            gTransform.localPosition = t.localPosition;
            gTransform.localScale = t.localScale;
            gTransform.localRotation = t.localRotation;
        }
 
        if (!keep)
        {
            foreach (GameObject g in Selection.gameObjects)
            {
                GameObject.DestroyImmediate(g);
            }
        }
    }
	public GameObject GetPrefab()
	{
		int i = Random.Range(0,ReplaceObjects.Length);
		GameObject go = ReplaceObjects[i];

		return go;
	}


}