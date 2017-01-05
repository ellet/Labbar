using UnityEngine;
using System.Collections;
using UnityEditor;

[ExecuteInEditMode]
public class ModelComponent : MonoBehaviour
{
    public Object GetModel()
    {
        Object obj = PrefabUtility.GetPrefabParent(transform.gameObject);


        LODGroup temp = GetComponent<LODGroup>();
        if (temp != null)
        {
            LOD[] lodArray = temp.GetLODs();

            return lodArray[0].renderers[0].GetComponent<MeshFilter>().sharedMesh;
        }
        else if (obj == null)
        {
            obj = transform.gameObject;
        }
        return ((GameObject)obj).GetComponent<MeshFilter>().sharedMesh;
    }
}
