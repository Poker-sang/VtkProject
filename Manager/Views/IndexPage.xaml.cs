using System;
using Manager.Interfaces;
using Microsoft.UI.Xaml.Controls;

namespace Manager.Views;

public sealed partial class IndexPage : Page, ITypeGetter
{
    public IndexPage() => InitializeComponent();

    //输入的格式
    public static Type TypeGetter => typeof(IndexPage);
}
