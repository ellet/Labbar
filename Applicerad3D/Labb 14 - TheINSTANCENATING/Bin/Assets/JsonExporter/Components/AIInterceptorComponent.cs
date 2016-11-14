using UnityEngine;
using System.Collections;

public class AIInterceptorComponent : MonoBehaviour
{
    //with recommended values! :D
    public float maxForwardSpeed = 200.0f; // 
    public float minForwardSpeed = 20.0f; // 
    public float acceleration = 30.0f; // 
    public float breakPower = 10.0f; // 
    public float distanceToPlayerUntilRotate = 300.0f; // 
    public int rotateTowardsPlayerPoints = 200; // 
    public int isRotatingPoints = 100; // 
    public int shootAtPlayerPoints = 75; // 
    public int turnAwayFromClusterPoints = 400; // 
    public int turnAwayFromObjectPoints = 400; // 
}
