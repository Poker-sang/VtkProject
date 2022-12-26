using Manager.Attributes;

namespace Manager;

[GenerateConstructor]
public partial record AppConfig
{
    public int Theme { get; set; }
}
