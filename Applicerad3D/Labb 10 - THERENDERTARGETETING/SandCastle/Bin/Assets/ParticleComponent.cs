using UnityEngine;
using System.Collections;

public class ParticleComponent : MonoBehaviour
{
    public Color StartColor;
    public Color EndColor;

    public Vector2 MinMaxVelocityX = new Vector2(-1, 1);
    public Vector2 MinMaxVelocityY = new Vector2(-1, 1);
    public Vector2 MinMaxVelocityZ = new Vector2(-1, 1);

    public Vector2 MinMaxLifetime = new Vector2(1, 10);
    public Vector2 MinMaxSize = new Vector2(0.01f, 0.2f);
    public float EndSizeInPercent = 0.1f;
    public float EmitCoolDown = 0.1f;

    public int AmountOfParticles = 100;
}
