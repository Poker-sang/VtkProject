using Manager.Services.ExtensionMethods;
using Microsoft.UI.Xaml;

namespace Manager.Services;

public class ThemeHelper
{
    public static ElementTheme RootTheme
    {
        get => WindowHelper.Window.Content is FrameworkElement rootElement
            ? rootElement.RequestedTheme
            : ElementTheme.Default;
        set
        {
            if (WindowHelper.Window.Content is FrameworkElement rootElement)
                rootElement.RequestedTheme = value;

            App.AppConfig.Theme = (int)value;
            AppContext.ChangeTheme = (int)value;
        }
    }
}
