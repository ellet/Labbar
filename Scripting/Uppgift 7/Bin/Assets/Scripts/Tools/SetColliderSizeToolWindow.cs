using UnityEngine;
using UnityEditor;
using System.Collections;

public class SetColliderSizeToolWindow : EditorWindow
{
    public static float myValueToScaleColliders;
    [MenuItem ("Tools/Set Collider Size Tool Settings ..")]
    static void OpenWindow()
    {
        SetColliderSizeToolWindow window = (SetColliderSizeToolWindow)EditorWindow.GetWindow<SetColliderSizeToolWindow>(typeof(SetColliderSizeToolWindow));
        window.Show();
    }
	void OnGUI()
    {
        EditorGUILayout.LabelField("Set Collider Size Tool Settings", EditorStyles.boldLabel);
        EditorGUILayout.LabelField("");

        myValueToScaleColliders = EditorGUILayout.FloatField("Value To Scale", myValueToScaleColliders);
        if (GUILayout.Button("Exit"))
        {
            SetColliderSizeToolWindow window = (SetColliderSizeToolWindow)EditorWindow.GetWindow<SetColliderSizeToolWindow>(typeof(SetColliderSizeToolWindow));
            window.Close();
        }
    }
}
