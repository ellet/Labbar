using UnityEngine;
using UnityEditor;
using System.Collections.Generic;
using System.Collections;

public class RandomPositionOffsetTool
{
    [MenuItem("Tools/Set Random Position Offset &_c")]
    static void SetRandomRotation()
    {
        List<Transform> transformsToChange = new List<Transform>();
        transformsToChange.AddRange(Selection.transforms);
        foreach(Transform targetTransform in transformsToChange)
        {
            if(targetTransform.GetComponent<Terrain>() == null)
            {
                Undo.RegisterCompleteObjectUndo(targetTransform.gameObject, "Random Position Offset..");
                float RandomPosX = Random.Range(RandomPositionOffsetToolWindow.myRandomPositionOffsetX.x, RandomPositionOffsetToolWindow.myRandomPositionOffsetX.y);
                float RandomPosY = Random.Range(RandomPositionOffsetToolWindow.myRandomPositionOffsetY.x, RandomPositionOffsetToolWindow.myRandomPositionOffsetY.y);
                float RandomPosZ = Random.Range(RandomPositionOffsetToolWindow.myRandomPositionOffsetZ.x, RandomPositionOffsetToolWindow.myRandomPositionOffsetZ.y);

                Vector3 newPosition = new Vector3(RandomPosX, RandomPosY, RandomPosZ);
                targetTransform.position += newPosition;
            }
        }
    }
}
