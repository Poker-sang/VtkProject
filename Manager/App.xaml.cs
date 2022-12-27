using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using CommunityToolkit.Mvvm.Messaging;
using System.Threading.Tasks;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using Microsoft.UI.Xaml.Shapes;
using Windows.ApplicationModel;
using Windows.Foundation;
using Windows.Foundation.Collections;
using CommunityToolkit.WinUI;
using Manager.Services.ExtensionMethods;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace Manager;

public partial class App : Application
{
    public static AppConfig AppConfig { get; private set; } = null!;
    public static NavigationView RootNavigationView { get; set; } = null!;
    public static Frame RootFrame { get; set; } = null!;

    public App()
    {
        InitializeComponent();
        RegisterUnhandledExceptionHandler();
        AppContext.Initialize();
        if (AppContext.LoadConfiguration() is not { } appConfigurations
#if FIRST_TIME
        || true
#endif
           )
            AppConfig = new AppConfig();
        else
            AppConfig = appConfigurations;
    }


    /// <param name="args">Details about the launch request and process.</param>
    protected override void OnLaunched(LaunchActivatedEventArgs args) =>
        WindowHelper.Initialize().SetWindowSize(800, 450).Activate();


    #region 错误捕捉

    private void RegisterUnhandledExceptionHandler()
    {
        UnhandledException += async (_, args) =>
        {
            args.Handled = true;
            await WindowHelper.Window.DispatcherQueue.EnqueueAsync(async () => await UncaughtExceptionHandler(args.Exception));
        };

        TaskScheduler.UnobservedTaskException += async (_, args) =>
        {
            args.SetObserved();
            await WindowHelper.Window.DispatcherQueue.EnqueueAsync(async () => await UncaughtExceptionHandler(args.Exception));
        };

        AppDomain.CurrentDomain.UnhandledException += async (_, args) =>
        {
            if (args.ExceptionObject is Exception e)
                await WindowHelper.Window.DispatcherQueue.EnqueueAsync(async () => await UncaughtExceptionHandler(e));
            else
                ExitWithPushedNotification();
        };

        DebugSettings.BindingFailed += (sender, args) => Debug.WriteLine(args.Message);

#if DEBUG
        static Task UncaughtExceptionHandler(Exception e)
        {
            if (Debugger.IsAttached)
                Debugger.Break();
            return Task.CompletedTask;
        }
#elif RELEASE
        static async Task UncaughtExceptionHandler(Exception e)
        {
            await ShowMessageDialog.Information(true, e.ToString());
            // ExitWithPushedNotification();
        }
#endif
    }
    private static void ExitWithPushedNotification()
    {
        _ = WeakReferenceMessenger.Default.Send(new ApplicationExitingMessage());
        Current.Exit();
    }
    public record ApplicationExitingMessage;

    #endregion
}
