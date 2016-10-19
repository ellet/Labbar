using System;
using System.Collections.Generic;
using Newtonsoft.Json;
using UnityEngine;
using UnityEditor;

public class JEObject
{

    public object ToJSON()
    {
        throw new NotImplementedException("Attempting to call JEObject ToJSON (override method)");
    }

    public string name;
}

