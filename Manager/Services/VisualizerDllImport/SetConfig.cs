using System.Runtime.InteropServices;

namespace Manager.Services.VisualizerDllImport;

public static partial class SetConfig
{
    [LibraryImport(VisualizerInfo.DllName)]
    // [return: MarshalAs(UnmanagedType.I1)]
    public static partial void SetWindowSize(int width, int height);

    [LibraryImport(VisualizerInfo.DllName)]
    public static partial void SetCellType(CellType cellType);
}
