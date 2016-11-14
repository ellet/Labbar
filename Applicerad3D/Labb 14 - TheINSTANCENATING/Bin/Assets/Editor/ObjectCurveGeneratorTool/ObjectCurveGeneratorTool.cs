using UnityEngine;
using UnityEditor;
using System.Collections;

[CustomEditor(typeof(ObjectCurveGenerator))]
public class ObjectCurveGeneratorTool: Editor {

    public ObjectCurveGenerator objCurveGenerator;

    public bool myUpdateInRealtime = false;

    //private string updateON = "Auto Update - ON";
    //private string updateOFF = "Auto Update - OFF";
    //private string updateToolTip = "Auto Update - OFF";

    public void OnSceneGUI()
    { 
        Event e = Event.current;
        if (Selection.activeGameObject != null)
        {
            if (Selection.activeGameObject.GetComponent<ObjectCurveGenerator>() != null)
            {
                objCurveGenerator = Selection.activeGameObject.GetComponent<ObjectCurveGenerator>();
            }
            if (Selection.activeGameObject != objCurveGenerator)
            {
                return;
            }
        }

        if (IsHotkeyPressed(e))
        {
            objCurveGenerator.GenerateObjects();
        }
    }


    public override void OnInspectorGUI()
    {
        base.OnInspectorGUI();
        EditorGUI.BeginChangeCheck();
        ObjectCurveGenerator objectCurveGenerator = (ObjectCurveGenerator)target;
        EditorGUILayout.LabelField(" ");
        EditorGUILayout.LabelField("General Options", EditorStyles.boldLabel);
        objectCurveGenerator.frequency = EditorGUILayout.IntField("Frequency", objectCurveGenerator.frequency);
        EditorGUILayout.LabelField(" ");
        EditorGUILayout.LabelField("Random Placement Offset", EditorStyles.boldLabel);
        objectCurveGenerator.randomOffsetMin = EditorGUILayout.Vector3Field("Offset Min", objectCurveGenerator.randomOffsetMin);
        objectCurveGenerator.randomOffsetMax = EditorGUILayout.Vector3Field("Offset Max", objectCurveGenerator.randomOffsetMax);
        objectCurveGenerator.offsetAffectCurve = EditorGUILayout.CurveField("Random Offset Affection Curve", objectCurveGenerator.offsetAffectCurve);
        EditorGUILayout.LabelField(" ");
        EditorGUILayout.LabelField("Random Rotation", EditorStyles.boldLabel);
        objectCurveGenerator.randomRotMin = EditorGUILayout.Vector3Field("Rotation Min", objectCurveGenerator.randomRotMin);
        objectCurveGenerator.randomRotMax = EditorGUILayout.Vector3Field("Rotation Max", objectCurveGenerator.randomRotMax);
        EditorGUILayout.LabelField(" ");
        EditorGUILayout.LabelField("Random Scale", EditorStyles.boldLabel);
        objectCurveGenerator.randomScale = EditorGUILayout.Vector2Field("Scale Min/Max", objectCurveGenerator.randomScale);
        /*EditorGUILayout.LabelField(" ");
        EditorGUILayout.LabelField("Offset Curves (Multiplied)", EditorStyles.boldLabel);
        objectCurveGenerator.curveOffsetMulX = EditorGUILayout.CurveField("X-pos Mul-Curve", objectCurveGenerator.curveOffsetMulX);
        objectCurveGenerator.curveOffsetMulY = EditorGUILayout.CurveField("Y-pos Mul-Curve", objectCurveGenerator.curveOffsetMulY);
        objectCurveGenerator.curveOffsetMulZ = EditorGUILayout.CurveField("Z-pos Mul-Curve", objectCurveGenerator.curveOffsetMulZ); */
        EditorGUILayout.LabelField(" ");
        EditorGUILayout.LabelField("Offset Curves (Additative)", EditorStyles.boldLabel);
        objectCurveGenerator.curveAddidativeX = EditorGUILayout.CurveField("X-pos Add-Curve", objectCurveGenerator.curveAddidativeX);
        objectCurveGenerator.curveAddidativeY = EditorGUILayout.CurveField("Y-pos Add-Curve", objectCurveGenerator.curveAddidativeY);
        objectCurveGenerator.curveAddidativeZ = EditorGUILayout.CurveField("Z-pos Add-Curve", objectCurveGenerator.curveAddidativeZ);
        EditorGUILayout.LabelField(" ");
        EditorGUILayout.LabelField("Help", EditorStyles.boldLabel);
        EditorGUILayout.LabelField(" Random Offset Affection Curve = How much spawned- ");
        EditorGUILayout.LabelField(" object will be randomly placed along the curve. ");
        EditorGUILayout.LabelField(" ");
        EditorGUILayout.LabelField(" X-pos Curve = Spawn density along the curve. ");
        EditorGUILayout.LabelField(" Y-pos Curve = Height spread of spawned object. ");
        EditorGUILayout.LabelField(" Z-pos Curve = Sideway spread of spawned object. ");
        EditorGUILayout.LabelField(" ");
        if (EditorGUI.EndChangeCheck())
        {
            objectCurveGenerator.GenerateObjects();
        }

        //BUTTONS

        Event e = Event.current;

        if (GUILayout.Button("Generate (Shift+G)") || IsHotkeyPressed(e))
        {
            objectCurveGenerator.GenerateObjects();
        }

        //if (GUILayout.Button(updateToolTip))
        //{
        //    myUpdateInRealtime = !myUpdateInRealtime;
        //    objectCurveGenerator.doUpdateInRealtime = myUpdateInRealtime;
        //    updateToolTip = (myUpdateInRealtime) ? updateON : updateOFF;
        //}

    }

        
    private bool IsHotkeyPressed(Event e)
    {
        bool isPressed = false;
        if (e.type == EventType.KeyDown)
        {
            if ((e.keyCode == KeyCode.G) && (e.modifiers == EventModifiers.Shift))
            {
                isPressed = true;
            }
        }
        return isPressed;
    }
}
