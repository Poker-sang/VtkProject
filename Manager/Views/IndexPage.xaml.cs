using System;
using Manager.Enums;
using Manager.Interfaces;
using Manager.Models;
using Manager.Services.VisualizerDllImport;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using WinUI3Utilities;

namespace Manager.Views;

public sealed partial class IndexPage : Page, ITypeGetter
{
    public IndexPage() => InitializeComponent();

    public static Type TypeGetter => typeof(IndexPage);

    private void NewTap(object s, RoutedEventArgs e)
    {
        var file = new FileModel("dem.grd", @"C:\WorkSpace\VtkProject\Manager\Assets", FileExtension.Grd);
        var data = file.GetDataFromFile(out var width, out var height);
        SetData2D.SetElevation(data, width);
        SetData2D.SetScalarFromElevation();
        SetConfig.SetCellType(CellType.Vertex);
        ShowData2D.Show2D();
    }
}
