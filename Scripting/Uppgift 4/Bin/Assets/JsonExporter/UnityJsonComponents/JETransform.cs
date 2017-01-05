using System;
using System.Collections.Generic;
using Newtonsoft.Json;
using UnityEngine;
using UnityEditor;

public class JETransform : JEComponent
{
    override public void Init()
    {
        unityTransform = unityComponent as Transform;
    }

    public override JSONComponent ToJSON()
    {
        var json = new JSONTransform();
        json.type = "Transform";
        json.localPosition = unityTransform.localPosition;
        json.localRotation = unityTransform.localRotation;
        json.localScale = unityTransform.localScale;
        return json;
    }

    Transform unityTransform;
}
public class JSONTransform : JSONComponent
{
    public Vector3 localPosition;
    public Quaternion localRotation;
    public Vector3 localScale;
}
