using System;
using Manager.Enums;
using Manager.Interfaces;
using Manager.Models;
using Manager.Services;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;

namespace Manager.Views;

public sealed partial class IndexPage : Page, ITypeGetter
{
    public IndexPage() => InitializeComponent();

    public static Type TypeGetter => typeof(IndexPage);

    private void NewTap(object s, RoutedEventArgs e)
    {
        var file = new FileModel("dem.grd", @"C:\WorkSpace\VtkProject\Manager\Assets", FileExtension.Grd);
        var data = file.GetDataFromFile(out var width, out var height);
        VisualizerDllImport.SetData2D(data, width);
        var a = VisualizerDllImport.Show2D();
    }
}
