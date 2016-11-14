using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class StreakComponent : MonoBehaviour {
    public List<Color> colors = new List<Color>(new Color[] {
        new Color(1.0f, 1.0f, 1.0f, 1.0f),
        new Color(1.0f, 1.0f, 1.0f, 0.0f),
    });

    public List<float> sizes = new List<float>(new float[] {
        1.0f,
        0.0f
    });

    public float streakTime;
    public int numberOfSegments;
}
