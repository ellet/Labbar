using UnityEngine;
using UnityEditor;
using System.Collections;

public class RandomRotationToolWindow : EditorWindow
{
    public static Vector3 myRandomRotation = new Vector3(0, 0, 0);
    [MenuItem ("Tools/Random Rotation Tool Settings..")]
    static void OpenWindow()
    {
        RandomRotationToolWindow window = (RandomRotationToolWindow)EditorWindow.GetWindow<RandomRotationToolWindow>(typeof(RandomRotationToolWindow));
        window.Show();
    }
	void OnGUI()
    {
        EditorGUILayout.LabelField("Random Rotation Tool Settings", EditorStyles.boldLabel);
        EditorGUILayout.LabelField("");

        myRandomRotation = EditorGUILayout.Vector3Field("Random Rotation", myRandomRotation);
        if(GUILayout.Button("Exit"))
        {
            RandomRotationToolWindow window = (RandomRotationToolWindow)EditorWindow.GetWindow<RandomRotationToolWindow>(typeof(RandomRotationToolWindow));
            window.Close();
        }
    }
}
