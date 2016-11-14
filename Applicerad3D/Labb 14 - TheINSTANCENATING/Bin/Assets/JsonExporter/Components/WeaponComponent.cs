using UnityEngine;
using System.Collections;

public class WeaponComponent : MonoBehaviour
{
    public string identifier = "";
	public string weaponModelPath = "";
	public string weaponIconPath = "";
	public string projectileModelPath = "";
	public string shootSound = "";
	public Vector3 barrelOffset = Vector3.zero;
	public Vector3 shotScale = Vector3.one;
	public float shotCooldown = 1.0f;
	public float damage = 1.0f;
	public float shotSpeed = 10.0f;
    public float firingRotationVelocityMax = 0.0f;
    public float firingRotationVelocityAccelerationTime = 0.0f;
}
