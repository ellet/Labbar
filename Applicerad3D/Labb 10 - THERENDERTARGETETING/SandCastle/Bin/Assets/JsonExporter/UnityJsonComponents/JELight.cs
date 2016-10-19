using System.Collections.Generic;
using Newtonsoft.Json;
using UnityEngine;
using UnityEditor;

public class JELight : JEComponent
{
    override public void Init()
    {
        unityLight = unityComponent as Light;
    }

    public override JSONComponent ToJSON()
    {
        var json = new JSONLight();
        json.type = "Light";

        json.lightType = "Point";
        json.color = unityLight.color;
        json.range = unityLight.range;
        json.castsShadows = unityLight.shadows != LightShadows.None;
        json.realtime = true;

        SerializedObject serial = new SerializedObject(unityLight);
        SerializedProperty lightmapProp = serial.FindProperty("m_Lightmapping");
        if (lightmapProp.intValue != 0)
        {
            // not a realtime light
            json.realtime = false;
        }
        return json;
    }

    Light unityLight;
}

public class JSONLight : JSONComponent
{
    public Color color;
    public float range;
    public string lightType;
    public bool castsShadows;
    public bool realtime;
}

