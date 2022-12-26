// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;
using CommunityToolkit.Mvvm.ComponentModel;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Windows.Foundation.Metadata;
using Manager.Views;

namespace Manager;

[INotifyPropertyChanged]
public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
        // 加载窗口后设置标题，拖拽区域才能达到原定效果
        ExtendsContentIntoTitleBar = true;
        SetTitleBar(AppTitleBar);
        Title = nameof(Manager);
        // TODO: Microsoft.WindowsAppSDK 1.2后，最小化的NavigationView没有高度
        App.RootNavigationView = NavigationView;
        App.RootFrame = NavigateFrame;
    }

    private void Loaded(object sender, RoutedEventArgs e)
    {
        ((NavigationViewItem)NavigationView.SettingsItem).Tag = typeof(SettingsPage);

        _ = NavigateFrame.Navigate(typeof(IndexPage));
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
        {
            _ = NavigateFrame.Navigate(item);
            NavigationView.IsBackEnabled = true;
            GC.Collect();
        }
    }

    #region AppTitle相关

    private void PaneClosing(NavigationView sender, NavigationViewPaneClosingEventArgs e) => UpdateAppTitleMargin(sender);

    private void PaneOpening(NavigationView sender, object e) => UpdateAppTitleMargin(sender);

    private void DisplayModeChanged(NavigationView sender, NavigationViewDisplayModeChangedEventArgs e)
    {
        var currentMargin = AppTitleBar.Margin;
        AppTitleBar.Margin = sender.DisplayMode is NavigationViewDisplayMode.Minimal
            ? new() { Left = sender.CompactPaneLength * 2, Top = currentMargin.Top, Right = currentMargin.Right, Bottom = currentMargin.Bottom }
            : new Thickness { Left = sender.CompactPaneLength, Top = currentMargin.Top, Right = currentMargin.Right, Bottom = currentMargin.Bottom };

        UpdateAppTitleMargin(sender);
    }

    private void UpdateAppTitleMargin(NavigationView sender)
    {
        const int smallLeftIndent = 4, largeLeftIndent = 24;

        if (ApiInformation.IsApiContractPresent("Windows.Foundation.UniversalApiContract", 7))
        {
            AppTitle.TranslationTransition = new Vector3Transition();

            AppTitle.Translation = (sender.DisplayMode is NavigationViewDisplayMode.Expanded && sender.IsPaneOpen) ||
                     sender.DisplayMode is NavigationViewDisplayMode.Minimal
                ? new(smallLeftIndent, 0, 0)
                : new System.Numerics.Vector3(largeLeftIndent, 0, 0);
        }
        else
        {
            var currentMargin = AppTitle.Margin;

            AppTitle.Margin = (sender.DisplayMode is NavigationViewDisplayMode.Expanded && sender.IsPaneOpen) ||
                     sender.DisplayMode is NavigationViewDisplayMode.Minimal
                ? new() { Left = smallLeftIndent, Top = currentMargin.Top, Right = currentMargin.Right, Bottom = currentMargin.Bottom }
                : new Thickness { Left = largeLeftIndent, Top = currentMargin.Top, Right = currentMargin.Right, Bottom = currentMargin.Bottom };
        }
    }

    #endregion
}
