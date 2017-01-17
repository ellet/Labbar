using UnityEngine;
using UnityEditor;
using System.Collections;
using System.Collections.Generic;
using System;

[ExecuteInEditMode]
public class ObjectCurveGenerator : MonoBehaviour
{
    public List<GameObject> objectsToGenerate;

    [HideInInspector]
    public int frequency;
    [HideInInspector]
    public AnimationCurve curveAddidativeX = new AnimationCurve(new Keyframe(0, 0), new Keyframe(1, 1));
    [HideInInspector]
    public AnimationCurve curveAddidativeY = new AnimationCurve(new Keyframe(0, 0), new Keyframe(1, 1));
    [HideInInspector]
    public AnimationCurve curveAddidativeZ = new AnimationCurve(new Keyframe(0, 0), new Keyframe(1, 1));

    [HideInInspector]
    public AnimationCurve curveOffsetMulX = new AnimationCurve(new Keyframe(0, 0), new Keyframe(1, 1));
    [HideInInspector]
    public AnimationCurve curveOffsetMulY = new AnimationCurve(new Keyframe(0.5f, 0.5f), new Keyframe(0.5f, 0.5f));
    [HideInInspector]
    public AnimationCurve curveOffsetMulZ = new AnimationCurve(new Keyframe(0, 0), new Keyframe(1, 1));

    [HideInInspector]
    public Vector3 randomOffsetMin = Vector3.zero;
    [HideInInspector]
    public Vector3 randomOffsetMax = Vector3.zero;
    [HideInInspector]
    public AnimationCurve offsetAffectCurve = new AnimationCurve(new Keyframe(1, 1), new Keyframe(1, 1));
    [HideInInspector]
    public Vector3 randomRotMin = Vector3.zero;
    [HideInInspector]
    public Vector3 randomRotMax = Vector3.zero;
    [HideInInspector]
    public Vector2 randomScale = new Vector2(1, 1);

    [HideInInspector]
    public List<GameObject> generatedObjects = null;
    [HideInInspector]
    public List<float> ranOffsetVals = null;
    [HideInInspector]
    public List<Vector3> curvePosValsMultiply = null;
    [HideInInspector]
    public bool doUpdateInRealtime = false;
    [HideInInspector]
    public List<Vector3> curvePosValsAdditative = null;

    [HideInInspector]
    public Transform nodeA;
    [HideInInspector]
    public Transform nodeB;
    [HideInInspector]
    public Transform objectsParent;

    private List<Vector3> oldNodePositions = new List<Vector3>();
    private enum NodeType { NODE_A, NODE_B, OBJ_PARENT, ROOT };

    private void AddEmptyPositions()
    {
        for (int i = 0; i < 4; i++)
        {
            oldNodePositions.Add(Vector3.zero);
        }
    }

    void Update()
    {

    }

    private bool PositionDeltaChanged(NodeType aNodeType)
    {
        if (oldNodePositions.Count < 1)
        {
            AddEmptyPositions();
        }
        bool result = false;
        if (aNodeType == NodeType.NODE_A)
        {
            if (nodeA.position != oldNodePositions[(int)aNodeType])
            {
                result = true;
                oldNodePositions[(int)aNodeType] = nodeA.position;
            }
        }
        else if (aNodeType == NodeType.NODE_B)
        {
            if (nodeB.position != oldNodePositions[(int)aNodeType])
            {
                result = true;
                oldNodePositions[(int)aNodeType] = nodeB.position;
            }
        }
        else if (aNodeType == NodeType.OBJ_PARENT)
        {
            if (objectsParent.position != oldNodePositions[(int)aNodeType])
            {
                result = true;
                oldNodePositions[(int)aNodeType] = objectsParent.position;
            }
        }
        else if (aNodeType == NodeType.ROOT)
        {
            if (this.transform.position != oldNodePositions[(int)aNodeType])
            {
                result = true;
                oldNodePositions[(int)aNodeType] = this.transform.position;
            }
        }
        return result;
    }

    public bool AnyToolObjectSelected()
    {
        bool result = false;
        if (Selection.activeGameObject != null)
        {
            if (Selection.activeGameObject.transform == nodeA && PositionDeltaChanged(NodeType.NODE_A))
            {
                result = true;
            }
            if (Selection.activeGameObject.transform == nodeB && PositionDeltaChanged(NodeType.NODE_B))
            {
                result = true;
            }
            if (Selection.activeGameObject.transform == objectsParent.transform && PositionDeltaChanged(NodeType.OBJ_PARENT))
            {
                result = true;
            }
            //if (Selection.activeGameObject == this.gameObject && PositionDeltaChanged(NodeType.ROOT))
            //{
            //    result = true;
            //}
        }
        return result;
    }

    public void GenerateObjects()
    {
        CreateToolObjects();

        if (objectsToGenerate != null)
        {
            ClearGenerator();
            float stepSize = 1f / frequency;

            for (int i = 0; i < frequency; i++)
            {
                AddMulCurveStepVector(stepSize, i);
                SetRandomStepOffset(stepSize, i);
                AddAdditativeCurveStepVector(stepSize, i);
            }
            Vector2 xRange = new Vector2(nodeA.position.x, nodeB.position.x);
            Vector2 yRange = new Vector2(nodeA.position.y, nodeB.position.y);
            Vector2 zRange = new Vector2(nodeA.position.z, nodeB.position.z);

            // GENERATION LOOP
            for (int i = 0; i < frequency; i++)
            {
                // POSITION & ROTATION
                Vector3 pos = GetNewPosition(xRange, yRange, zRange, i);
                Vector3 rot = GetNewRotation();

                //SCALE
                float randomScaleVal = UnityEngine.Random.Range(randomScale.x, randomScale.y);
                Vector3 scale = GetNewScale(randomScaleVal);

                GenerateObject(pos, rot, scale);
            }
        }
    }

    private void AddMulCurveStepVector(float stepSize, int i)
    {
        Vector3 stepVector = new Vector3(curveOffsetMulX.Evaluate(i * stepSize), curveOffsetMulY.Evaluate(i * stepSize), curveOffsetMulZ.Evaluate(i * stepSize));
        curvePosValsMultiply.Add(stepVector);
    }

    private void SetRandomStepOffset(float stepSize, int i)
    {
        float randomOffsetVal = offsetAffectCurve.Evaluate(i * stepSize);
        ranOffsetVals.Add(randomOffsetVal);
    }

    private void AddAdditativeCurveStepVector(float stepSize, int i)
    {
        Vector3 v2 = new Vector3(curveAddidativeX.Evaluate(i * stepSize), curveAddidativeY.Evaluate(i * stepSize), curveAddidativeZ.Evaluate(i * stepSize));
        curvePosValsAdditative.Add(v2);
    }

    private static Vector3 GetNewScale(float ran)
    {
        return new Vector3(ran, ran, ran);
    }

    private Vector3 GetNewRotation()
    {
        return new Vector3(UnityEngine.Random.Range(randomRotMin.x, randomRotMax.x), UnityEngine.Random.Range(randomRotMin.y, randomRotMax.y), UnityEngine.Random.Range(randomRotMin.z, randomRotMax.z));
    }

    private Vector3 GetNewPosition(Vector2 xRange, Vector2 yRange, Vector2 zRange, int i)
    {
        Vector3 pos;

        float xDelta = xRange.x - xRange.y;
        float yDelta = (yRange.x - yRange.y != 0f) ? yRange.x - yRange.y : 1f;
        float zDelta = zRange.x - zRange.y;

        pos.x = nodeA.position.x - (xDelta * curvePosValsAdditative[i].x + UnityEngine.Random.Range(randomOffsetMin.x * ranOffsetVals[i], randomOffsetMax.x * ranOffsetVals[i]));
        pos.y = nodeA.position.y - ((yDelta*-1) * curvePosValsAdditative[i].y + UnityEngine.Random.Range(randomOffsetMin.y * ranOffsetVals[i], randomOffsetMax.y * ranOffsetVals[i]));
        pos.z = nodeA.position.z - (zDelta * curvePosValsAdditative[i].z + UnityEngine.Random.Range(randomOffsetMin.z * ranOffsetVals[i], randomOffsetMax.z * ranOffsetVals[i]));

        // OLD METHOD USING MUL
        //pos.x = nodeA.position.x - (curvePosValsAdditative[i].x * (xRange.x - xRange.y)) + UnityEngine.Random.Range(randomOffsetMin.x * ranOffsetVals[i], randomOffsetMax.x * ranOffsetVals[i]);
        //pos.y = nodeA.position.y - (curvePosValsAdditative[i].y * (yRange.x - yRange.y)) + UnityEngine.Random.Range(randomOffsetMin.y * ranOffsetVals[i], randomOffsetMax.y * ranOffsetVals[i]);
        //pos.z = nodeA.position.z - (curvePosValsAdditative[i].z * (zRange.x - zRange.y)) + UnityEngine.Random.Range(randomOffsetMin.z * ranOffsetVals[i], randomOffsetMax.z * ranOffsetVals[i]);

        return pos;
    }

    private void CreateToolObjects()
    {
        if (nodeA == null)
        {
            Debug.LogError("Object Curve Generator - nodeA WAS NULL, AUTO-CREATED NEW nodeA .");
            GameObject go = new GameObject();
            go.transform.position = transform.position;
            go.transform.position += new Vector3(-1, 0, 0);
            go.name = "NodeA";
            nodeA = go.transform;
            nodeA.SetParent(transform);
        }
        if (nodeB == null)
        {
            Debug.LogError("Object Curve Generator - nodeB WAS NULL, AUTO-CREATED NEW nodeB .");
            GameObject go = new GameObject();
            go.transform.position = transform.position;
            go.transform.position += new Vector3(1, 0, 0);
            go.name = "NodeB";
            nodeB = go.transform;
            nodeB.SetParent(transform);
        }
        if (objectsParent == null)
        {
            Debug.LogError("Object Curve Generator - objectsParent WAS NULL, AUTO-CREATED NEW objectsParent .");
            GameObject go = new GameObject();
            go.transform.position = transform.position;
            go.name = "objectsParent";
            objectsParent = go.transform;
            objectsParent.SetParent(transform);
        }
    }

    public void GenerateObject(Vector3 aPosition, Vector3 aRotation, Vector3 aScale)
    {
        UnityEngine.Object gameObjectToCreate = objectsToGenerate[Mathf.RoundToInt(UnityEngine.Random.Range(0, objectsToGenerate.Count))] as UnityEngine.Object;
        GameObject instancedPrefab = PrefabUtility.InstantiatePrefab(gameObjectToCreate) as GameObject;
        instancedPrefab.name = gameObjectToCreate.name;
        instancedPrefab.transform.position = aPosition;
        instancedPrefab.transform.localScale = aScale;
        instancedPrefab.transform.eulerAngles = aRotation;
        instancedPrefab.transform.SetParent(objectsParent);
        generatedObjects.Add(instancedPrefab);
    }

    private void ClearGenerator()
    {
        if (generatedObjects != null)
        {
            if (generatedObjects.Count > 0)
            {
                foreach (GameObject go in generatedObjects)
                {
                    DestroyImmediate(go);
                }
                generatedObjects.Clear();
            }
        }

        if (curvePosValsMultiply != null)
        {
            curvePosValsMultiply.Clear();
        }

        if (ranOffsetVals != null)
        {
            ranOffsetVals.Clear();
        }

        if (curvePosValsAdditative != null)
        {
            curvePosValsAdditative.Clear();
        }
    }


    void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawIcon(this.transform.position, "CenterIcon.png", true);
        if (nodeA != null)
        {
            Gizmos.DrawIcon(nodeA.position, "NodeGizmo.png", true);
        }
        if (nodeB != null)
        {
            Gizmos.DrawIcon(nodeB.position, "NodeGizmo.png", true);
        }
        if ((nodeA != null) && (nodeB != null))
        {
            Gizmos.DrawLine(nodeA.position, nodeB.position);
            Gizmos.DrawLine(nodeA.position, this.transform.position);
            Gizmos.DrawLine(nodeB.position, this.transform.position);
        }
    }
}
