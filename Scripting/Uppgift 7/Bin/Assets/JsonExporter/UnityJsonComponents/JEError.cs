using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;


static class ExportError
{
    public static void FatalError(string message)
    {
        EditorUtility.DisplayDialog("Error", message, "Ok");
        throw new Exception(message);
    }
}