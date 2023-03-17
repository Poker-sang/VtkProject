using System.Runtime.InteropServices;

namespace Manager.Services.VisualizerDllImport;

public static partial class ShowData2D
{
    [LibraryImport(VisualizerInfo.DllName)]
    // [return: MarshalAs(UnmanagedType.I1)]
    public static partial void Show2D(nint hWnd);
}
