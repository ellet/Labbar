using System.Collections.Generic;
using Newtonsoft.Json;
using UnityEngine;
using UnityEditor;

public class JEModelComponent : JEComponent
{
    override public void Init()
    {
        modelComponent = unityComponent as ModelComponent;
    }

    public override JSONComponent ToJSON()
    {
        var json = new JSONDynamicComponent();
        json.properties.Add("modelPath", AssetDatabase.GetAssetPath(modelComponent.GetModel()));
        
        // json.texturePath = "";
        json.type = "ModelComponent";
        return json;
    }

    ModelComponent modelComponent;
}
