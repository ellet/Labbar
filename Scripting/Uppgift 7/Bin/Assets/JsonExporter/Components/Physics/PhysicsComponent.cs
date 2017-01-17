﻿using UnityEngine;
using System.Collections;

public class PhysicsComponent : MonoBehaviour
{
    public float StartSpeed;
    public float Drag;
    public Vector3 WorldDirection;
    public bool NotAffectedByOthers = false;
    public bool DontMoveWithPhysics = false;
}
