using Microsoft.UI.Xaml;
using WinUI3Utilities;

namespace Manager;

public partial class App : Application
{
    public static AppConfig AppConfig { get; private set; } = null!;

    public App()
    {
        InitializeComponent();
        CurrentContext.App = this;
        CurrentContext.Title = nameof(Manager);
        AppContext.InitializeConfigurationContainer();
        AppConfig = AppContext.LoadConfiguration() ?? new AppConfig();
    }

    protected override void OnLaunched(LaunchActivatedEventArgs args)
    {
        CurrentContext.Window = new MainWindow();
        AppHelper.Initialize(WindowHelper.PredetermineEstimatedWindowSize());
    }
}
