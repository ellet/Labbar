using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace JSONExporter
{
    public class JEDynamicExporter : JEComponent
    {
        public override JSONComponent ToJSON()
        {
            var json = new JSONDynamicComponent();
            if (unityComponent != null)
                {
                json.type = unityComponent.GetType().Name;

                foreach (var field in unityComponent.GetType().GetFields(BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Instance | BindingFlags.FlattenHierarchy))
                {
                    object val = field.GetValue(unityComponent);
                    json.properties.Add(field.Name, val != null ? val : "");
                }
            }
                return json;
            
        }
    }
}
