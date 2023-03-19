using System.Runtime.InteropServices;

namespace Manager.Services.VisualizerDllImport;

public static partial class ShowData2D
{
    [LibraryImport(VisualizerInfo.DllName)]
    public static partial nint GetInterActor(nint hWnd, int x, int y, int width, int height);

    [LibraryImport(VisualizerInfo.DllName)]
    public static partial nint GetWindowFromInterActor(nint ptr);

    [LibraryImport(VisualizerInfo.DllName)]
    public static partial void Render(nint ptr);

    [LibraryImport(VisualizerInfo.DllName)]
    public static partial void Start(nint ptr);

    [LibraryImport(VisualizerInfo.DllName)]
    public static partial void ReleaseObject(nint ptr);
}
