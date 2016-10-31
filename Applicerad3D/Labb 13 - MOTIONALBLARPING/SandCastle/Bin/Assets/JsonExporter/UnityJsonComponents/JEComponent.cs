using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using JSONExporter;

public class JEComponent : JEObject
{
    public Component unityComponent;
    public JEGameObject jeGameObject;

    virtual public void Init()
    {

    }

    public virtual new JSONComponent ToJSON()
    {
        throw new NotImplementedException("Attempting to call JEComponent ToJSON (override method)");
    }

    public static void Reset()
    {
        conversions = new Dictionary<Type, Type>();
    }

    public static void QueryComponents(JEGameObject jgo)
    {
        HashSet<object> traversed = new HashSet<object>();

        // for every registered conversion get that component
        foreach (KeyValuePair<Type, Type> pair in conversions)
        {
            Component[] components = jgo.unityGameObject.GetComponents(pair.Key);
            foreach (Component component in components)
            {
                MeshRenderer meshRenderer = component as MeshRenderer;
                if (meshRenderer != null && !meshRenderer.enabled)
                {
                    continue;
                }

                var jcomponent = Activator.CreateInstance(pair.Value) as JEComponent;

                if (jcomponent == null)
                {
                    ExportError.FatalError("Export component creation failed");
                }

                if (traversed.Contains(component))
                    continue;

                traversed.Add(component);

                jcomponent.unityComponent = component;
                jcomponent.jeGameObject = jgo;
                jgo.AddComponent(jcomponent);
            }
        }
    }

    public static void RegisterConversion(Type componentType, Type exportType)
    {
        conversions[componentType] = exportType;
    }

    public static void RegisterStandardComponents()
    {
        foreach (var assembly in System.AppDomain.CurrentDomain.GetAssemblies())
        {
            if (assembly.GetName().FullName.ToLower().Contains("json"))
                continue;

            foreach (var declaredType in assembly.GetTypes())
            {
                if (typeof(MonoBehaviour).IsAssignableFrom(declaredType))
                {
                    RegisterConversion(declaredType, typeof(JEDynamicExporter));
                }
            }
        }

        RegisterConversion(typeof(Transform), typeof(JETransform));
        RegisterConversion(typeof(ModelComponent), typeof(JEModelComponent));
    }

    static Dictionary<Type, Type> conversions;
}

public class JSONComponent
{
    public string type;
}


public class JSONDynamicComponent : JSONComponent
{
    public Dictionary<string, object> properties = new Dictionary<string, object>();
}


