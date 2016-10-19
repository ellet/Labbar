using UnityEngine;
using UnityEditor;
using System.Collections.Generic;
using System.Collections;

public class RandomRotationTool
{
    [MenuItem("Tools/Set Random Rotation &_v")]
    static void SetRandomRotation()
    {
        List<Transform> transformsToChange = new List<Transform>();
        transformsToChange.AddRange(Selection.transforms);
        foreach(Transform targetTransform in transformsToChange)
        {
            if(targetTransform.GetComponent<Terrain>() == null)
            {
                Undo.RegisterCompleteObjectUndo(targetTransform.gameObject, "Random Rotation..");
                float RandomRotx = Random.Range((RandomRotationToolWindow.myRandomRotation.x * -1), RandomRotationToolWindow.myRandomRotation.x);
                float RandomRoty = Random.Range((RandomRotationToolWindow.myRandomRotation.y * -1), RandomRotationToolWindow.myRandomRotation.y);
                float RandomRotz = Random.Range((RandomRotationToolWindow.myRandomRotation.z * -1), RandomRotationToolWindow.myRandomRotation.z);

                Vector3 newRotation = new Vector3(RandomRotx, RandomRoty, RandomRotz);
                targetTransform.eulerAngles += newRotation;
            }
        }
    }
}
