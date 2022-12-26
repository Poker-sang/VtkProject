using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Manager.Services;
using Microsoft.UI;

namespace Manager.Views;

public partial class SettingsPage : Page
{
    public SettingsPage() => InitializeComponent();

    private void OnThemeChecked(object sender, RoutedEventArgs e)
    {
        var selectedTheme = (int)((FrameworkElement)sender).Tag switch
        {
            1 => ElementTheme.Light,
            2 => ElementTheme.Dark,
            _ => ElementTheme.Default
        };

        // 内含 App.AppConfiguration.Theme = selectedTheme;
        ThemeHelper.RootTheme = selectedTheme;
        Application.Current.Resources["WindowCaptionForeground"] = selectedTheme switch
        {
            ElementTheme.Dark => Colors.White,
            ElementTheme.Light => Colors.Black,
            _ => Application.Current.RequestedTheme is ApplicationTheme.Dark ? Colors.White : Colors.Black
        };

        TitleBarHelper.TriggerTitleBarRepaint();
        AppContext.SaveConfiguration(App.AppConfig);
    }
    
}
