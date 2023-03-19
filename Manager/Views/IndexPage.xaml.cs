using System;
using Manager.Enums;
using Manager.Interfaces;
using Manager.Models;
using Manager.Services.VisualizerDllImport;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;

namespace Manager.Views;

public sealed partial class IndexPage : Page, ITypeGetter
{
    public IndexPage() => InitializeComponent();

    public static Type TypeGetter => typeof(IndexPage);

    private nint _interActor = 0;

    private void NewTap(object s, RoutedEventArgs e)
    {
        var file = new FileModel("dem.grd", @"C:\WorkSpace\VtkProject\Manager\Assets", FileExtension.Grd);
        var data = file.GetDataFromFile(out var width, out var height);
        SetData2D.SetElevation(data, width);
        SetData2D.SetScalarFromElevation();
        SetConfig.SetCellType(CellType.Line);
        _interActor = ShowData2D.GetInterActor(0, 100, 100, 500, 500);
        ShowData2D.Start(_interActor);
    }

    private void OnUnloaded(object sender, RoutedEventArgs e)
    {
        if (_interActor is not 0)
            ShowData2D.ReleaseObject(_interActor);
    }
}
