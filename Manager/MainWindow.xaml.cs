using System;
using CommunityToolkit.Mvvm.ComponentModel;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Manager.Views;
using WinUI3Utilities;

namespace Manager;

[INotifyPropertyChanged]
public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
        CurrentContext.TitleBar = TitleBar;
        CurrentContext.TitleTextBlock = TitleTextBlock;
        // SetTitleBar(TitleBar);
        CurrentContext.NavigationView = NavigationView;
        CurrentContext.Frame = NavigateFrame;
    }

    private void Loaded(object sender, RoutedEventArgs e)
    {
        ((NavigationViewItem)NavigationView.SettingsItem).Tag = typeof(SettingsPage);

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
}
