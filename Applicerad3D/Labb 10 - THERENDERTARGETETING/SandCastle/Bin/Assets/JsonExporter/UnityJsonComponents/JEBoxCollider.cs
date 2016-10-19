using System.Collections.Generic;
using Newtonsoft.Json;
using UnityEngine;
using UnityEditor;

public class JEBoxCollider : JEComponent
{
    override public void Init()
    {
        unityBoxCollider = unityComponent as BoxCollider;
    }

    public override JSONComponent ToJSON()
    {
        var json = new JSONBoxCollider();
        json.type = "BoxCollider";
        json.size = unityBoxCollider.size;
        json.center = unityBoxCollider.center;
        return json;
    }

    BoxCollider unityBoxCollider;
}
public class JSONBoxCollider : JSONComponent
{
    public Vector3 center;
    public Vector3 size;
}

