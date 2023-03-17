using System;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Manager.Views;
using Microsoft.UI.Xaml.Input;
using WinUI3Utilities;
using Manager.Enums;
using Manager.Models;
using Manager.Services.VisualizerDllImport;
using Vanara.PInvoke;

namespace Manager;

public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        CurrentContext.Window = this;
        InitializeComponent();
        CurrentContext.TitleBar = TitleBar;
        CurrentContext.TitleTextBlock = TitleTextBlock;

        CurrentContext.NavigationView = NavigationView;
        CurrentContext.Frame = NavigateFrame;
    }

    private void Loaded(object sender, RoutedEventArgs e)
    {
        NavigationView.SettingsItem.To<NavigationViewItem>().Tag = typeof(SettingsPage);

        NavigationHelper.GotoPage<IndexPage>();
        NavigationView.SelectedItem = NavigationView.MenuItems[0];
    }

    private void BackRequested(NavigationView sender, NavigationViewBackRequestedEventArgs e)
    {
        NavigateFrame.GoBack();
        NavigationView.SelectedItem = NavigateFrame.Content switch
        {
            IndexPage => NavigationView.MenuItems[0],
            SettingsPage => NavigationView.SettingsItem,
            _ => NavigationView.SelectedItem
        };
        NavigationView.IsBackEnabled = NavigateFrame.CanGoBack;
    }

    private void ItemInvoked(NavigationView sender, NavigationViewItemInvokedEventArgs e)
    {
        if (e.InvokedItemContainer.Tag is Type item && item != NavigateFrame.Content.GetType())
            NavigationHelper.GotoPage(item);
    }

    //private void UIElement_OnTapped(object sender, TappedRoutedEventArgs e)
    //{
    //    var file = new FileModel("dem.grd", @"C:\WorkSpace\VtkProject\Manager\Assets", FileExtension.Grd);
    //    var data = file.GetDataFromFile(out var width, out var height);
    //    SetData2D.SetElevation(data, width);
    //    SetData2D.SetScalarFromElevation();
    //    SetConfig.SetCellType(CellType.Line);
    //    var a = User32.FindWindowEx(new HWND(CurrentContext.HWnd), lpszClass: null);
    //    var b = User32.FindWindowEx(new HWND(CurrentContext.HWnd), a, null);
    //    var c = User32.FindWindowEx(b, lpszClass: null);
    //    User32.SetWindowPos(a, HWND.NULL, 0, 0, 200, 300, User32.SetWindowPosFlags.SWP_NOMOVE);
    //    User32.SetWindowPos(b, HWND.NULL, 0, 0, 200, 300, User32.SetWindowPosFlags.SWP_NOMOVE);
    //    ShowData2D.Show2D((nint)a);
    //}
}
