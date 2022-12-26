using System;

namespace Manager.Attributes;

[AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct, Inherited = false)]
public sealed class GenerateConstructorAttribute : Attribute
{

}
