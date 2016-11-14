using UnityEngine;
using UnityEditor;
using System.Collections;
using System.Collections.Generic;

[InitializeOnLoad]
class ObjectiveCurveTsoolUpdater : Editor
{
    static ObjectiveCurveTsoolUpdater()
    {
        EditorApplication.update += ToolUpdate;
    }

    static void ToolUpdate()
    {
        List<ObjectCurveGenerator> curveGeneratorList = new List<ObjectCurveGenerator>();
        curveGeneratorList.AddRange(GameObject.FindObjectsOfType<ObjectCurveGenerator>());
        //Debug.Log("Hello");
        foreach (ObjectCurveGenerator curveGen in curveGeneratorList)
        {
            if (curveGen.AnyToolObjectSelected())
            {
                curveGen.GenerateObjects();
            }
        }
    }
}
