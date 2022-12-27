using System.Runtime.InteropServices;

namespace Manager.Services;

public static partial class VisualizerDllImport
{
    private const string DllName = @"C:\WorkSpace\VtkProject\x64\Debug\Visualizer.dll";

    [LibraryImport(DllName)]
    private static partial void SetData2D(double[] arr, int width, int height);

    [LibraryImport(DllName)]
    [return: MarshalAs(UnmanagedType.I1)]
    public static partial bool Show2D();

    public static void SetData2D(double[] array, int width) => SetData2D(array, width, array.Length / width);
}
