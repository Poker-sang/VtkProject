using WinUI3Utilities.Attributes;

namespace Manager;

[GenerateConstructor]
public partial record AppConfig
{
    public int Theme { get; set; }

    public AppConfig()
    {
        
    }
}
