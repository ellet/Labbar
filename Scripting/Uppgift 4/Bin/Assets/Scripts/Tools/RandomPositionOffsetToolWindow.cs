using UnityEngine;
using UnityEditor;
using System.Collections;

public class RandomPositionOffsetToolWindow : EditorWindow
{
    public static Vector2 myRandomPositionOffsetX = new Vector2(0, 0);
    public static Vector2 myRandomPositionOffsetY = new Vector2(0, 0);
    public static Vector2 myRandomPositionOffsetZ = new Vector2(0, 0);
    [MenuItem ("Tools/Random Position Offset Tool Settings..")]
    static void OpenWindow()
    {
        RandomPositionOffsetToolWindow window = (RandomPositionOffsetToolWindow)EditorWindow.GetWindow<RandomPositionOffsetToolWindow>(typeof(RandomPositionOffsetToolWindow));
        window.Show();
    }
	void OnGUI()
    {
        EditorGUILayout.LabelField("Random Position Offset Tool Settings", EditorStyles.boldLabel);
        EditorGUILayout.LabelField("");

        myRandomPositionOffsetX = EditorGUILayout.Vector2Field("Random Position X", myRandomPositionOffsetX);
        myRandomPositionOffsetY = EditorGUILayout.Vector2Field("Random Position Y", myRandomPositionOffsetY);
        myRandomPositionOffsetZ = EditorGUILayout.Vector2Field("Random Position Z", myRandomPositionOffsetZ);
        if (GUILayout.Button("Exit"))
        {
            RandomPositionOffsetToolWindow window = (RandomPositionOffsetToolWindow)EditorWindow.GetWindow<RandomPositionOffsetToolWindow>(typeof(RandomPositionOffsetToolWindow));
            window.Close();
        }
    }
}
