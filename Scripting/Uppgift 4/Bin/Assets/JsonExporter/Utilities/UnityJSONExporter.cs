using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using Newtonsoft.Json;
using UnityEngine;
using UnityEditor;
using System.Diagnostics;

public class UnityJSONExporter : ScriptableObject
{
    static void Reset()
    {
        JEComponent.Reset();
        JEGameObject.Reset();
        JEComponent.RegisterStandardComponents();
    }

    public static JSONScene GeneratePrefabs()
    {
        Reset();
        JEScene.sceneName = "Prefabs";
        JEScene scene = JEScene.TraversePrefabs();
        scene.Init();
        JSONScene jsonScene = scene.ToJSON() as JSONScene;
        Reset();
        return jsonScene;
    }
    public static JSONScene GenerateJSONScene()
    {
        Reset();
        JEScene.sceneName = Path.GetFileNameWithoutExtension(UnityEditor.SceneManagement.EditorSceneManager.GetActiveScene().name);
        JEScene scene = JEScene.TraverseScene();
        scene.Init();
        JSONScene jsonScene = scene.ToJSON() as JSONScene;
        Reset();
        return jsonScene;
    }

    private static void ExportPrefabsToPath(string path)
    {
        var jsonScene = GeneratePrefabs();
        JsonConverter[] converters = new JsonConverter[] { new TypeConverter() };
        string json = JsonConvert.SerializeObject(jsonScene, Formatting.Indented, converters);
        System.IO.File.WriteAllText(path, json);
    }

    private static void ExportToPath(string path)
    {
        var jsonScene = GenerateJSONScene();
        JsonConverter[] converters = new JsonConverter[] { new TypeConverter() };
        string json = JsonConvert.SerializeObject(jsonScene, Formatting.Indented, converters);
        System.IO.File.WriteAllText(path, json);
    }
    [MenuItem("Sandbucket/Export prefabs to JSON")]
    public static void DoExportPrefabs()
    {
        var defaultFileName = "Prefabs.json";
        var path = EditorUtility.SaveFilePanel("Export Scene to JSON", "Assets/Data/Prefabs/", defaultFileName, "json");
        if (path.Length != 0)
        {
            ExportPrefabsToPath(path);
            EditorUtility.DisplayDialog("Sandbucket", "Export Successful", "OK");
        }
    }

    public static string rememberedPath = "";
    [MenuItem("Sandbucket/Export to JSON")]
    public static void DoExport()
    {
        var defaultFileName = Path.GetFileNameWithoutExtension(UnityEditor.SceneManagement.EditorSceneManager.GetActiveScene().name) + ".json";
        var path = EditorUtility.SaveFilePanel("Export Scene to JSON", rememberedPath, defaultFileName, "json");
        rememberedPath = path;
        if (path.Length != 0)
        {
            ExportToPath(path);
            EditorUtility.DisplayDialog("Sandbucket", "Export Successful", "OK");
        }
    }

    private static string executablePath = "";

    [MenuItem("Sandbucket/Set Game Path")]
    public static void SetGamePath()
    {
        var defaultFileName = Path.GetFileNameWithoutExtension(UnityEditor.SceneManagement.EditorSceneManager.GetActiveScene().name) + ".json";
        var path = EditorUtility.OpenFilePanelWithFilters("Export Scene to JSON", "", new string[] { "Game Executable", "exe" });
        if (path.Length != 0)
        {
            executablePath = path;
        }
    }

    [MenuItem("Sandbucket/Play this level _F5")]
    public static void PlayLevel()
    {
        if (string.IsNullOrEmpty(executablePath))
        {
            SetGamePath();
            
            if (string.IsNullOrEmpty(executablePath))
            {
                EditorUtility.DisplayDialog("Sandbucket", "A game path must be set!", "OK");
                return;
            }
        }
        var filename = Path.GetTempFileName();
        ExportToPath(filename);
        ProcessStartInfo info = new ProcessStartInfo();
        info.WorkingDirectory = Path.GetDirectoryName(executablePath) + "/";
        info.Arguments = string.Format("-level \"" + filename + "\"");
        info.FileName = executablePath;
        Process.Start(info);
    }
}