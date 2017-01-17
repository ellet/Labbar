using System;
using System.Linq;
using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using UnityEngine;
using UnityEditor;

public class TypeConverter : JsonConverter
{
    public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
    {
        if (value != null)
        {
            if (value.GetType() == typeof(Color))
            {
                Color color = (Color)value;
                writer.WriteStartArray();
                writer.WriteValue(color.r);
                writer.WriteValue(color.g);
                writer.WriteValue(color.b);
                writer.WriteValue(color.a);
                writer.WriteEndArray();
            }
            else if (value.GetType() == typeof(Vector2))
            {
                Vector2 v = (Vector2)value;
                writer.WriteStartArray();
                writer.WriteValue(v.x);
                writer.WriteValue(v.y);
                writer.WriteEndArray();
            }
            else if (value.GetType() == typeof(Vector3))
            {
                Vector3 v = (Vector3)value;
                writer.WriteStartArray();
                writer.WriteValue(v.x);
                writer.WriteValue(v.y);
                writer.WriteValue(v.z);
                writer.WriteEndArray();
            }
            else if (value.GetType() == typeof(Vector4))
            {
                Vector4 v = (Vector4)value;
                writer.WriteStartArray();
                writer.WriteValue(v.x);
                writer.WriteValue(v.y);
                writer.WriteValue(v.z);
                writer.WriteValue(v.w);
                writer.WriteEndArray();
            }
            else if (value.GetType() == typeof(Quaternion))
            {
                Quaternion q = (Quaternion)value;
                writer.WriteStartArray();
                writer.WriteValue(q.x);
                writer.WriteValue(q.y);
                writer.WriteValue(q.z);
                writer.WriteValue(q.w);
                writer.WriteEndArray();
            }
            else if (value.GetType() == typeof(Matrix4x4))
            {
                Matrix4x4 m = (Matrix4x4)value;
                writer.WriteStartArray();

                for (int y = 0; y < 4; y++)
                {
                    for (int x = 0; x < 4; x++)
                    {
                        writer.WriteValue(m[y, x]);
                    }
                }
                writer.WriteEndArray();
            }
        }
    }

    public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
    {
        return null;
    }

    public override bool CanRead
    {
        get { return true; }
    }

    public override bool CanConvert(Type objectType)
    {
        Type[] types = new Type[] { typeof(Color), typeof(Vector2), typeof(Vector3), typeof(Vector4), typeof(Quaternion), typeof(Matrix4x4) };
        return Array.IndexOf(types, objectType) != -1;
    }
}
