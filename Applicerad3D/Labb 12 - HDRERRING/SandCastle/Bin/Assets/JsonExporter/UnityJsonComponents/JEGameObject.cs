using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using Newtonsoft.Json;

public class JEGameObject : JEObject
{
    public void AddComponent(JEComponent component)
    {
        components.Add(component);
    }

    public JEGameObject(GameObject go, JEGameObject parent)
    {
        GameObjectLookup[go] = this;
        this.unityGameObject = go;

        this.parent = parent;
        this.name = go.name;

        if (parent != null)
        {
            parent.children.Add(this);

        }

        JEComponent.QueryComponents(this);
    }

    public void Init()
    {
        foreach (var component in components)
        {
            component.Init();
        }

        foreach (var child in children)
        {
            child.Init();
        }
    }

    public static void Reset()
    {
        GameObjectLookup = new Dictionary<GameObject, JEGameObject>();
    }

    public new JSONGameObject ToJSON()
    {
        JSONGameObject json = new JSONGameObject();

        json.name = name;
        json.children = new List<JSONGameObject>();
        foreach (var child in children)
        {
            json.children.Add(child.ToJSON());
        }
        json.components = new List<JSONComponent>();
        foreach (var component in components)
        {
            json.components.Add(component.ToJSON());
        }

        return json;
    }

    public static Dictionary<GameObject, JEGameObject> GameObjectLookup;
    public List<JEComponent> components = new List<JEComponent>();
    public List<JEGameObject> children = new List<JEGameObject>();
    public JETransform transform;
    public JEGameObject parent;
    public GameObject unityGameObject;
}

public class JSONGameObject
{
    public string name;
    public List<JSONComponent> components;
    public List<JSONGameObject> children;

    public T GetComponent<T>() where T : JSONComponent
    {
        foreach (var component in components)
        {
            if (component.GetType() == typeof(T))
            {
                return (T)component;
            }
        }
        return null;
    }
}
