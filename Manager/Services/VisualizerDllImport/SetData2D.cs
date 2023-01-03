using System.Runtime.InteropServices;

namespace Manager.Services.VisualizerDllImport;

public static partial class SetData2D
{
    [LibraryImport(VisualizerInfo.DllName)]
    private static partial void SetElevationData(double[] arr, int width, int height);

    [LibraryImport(VisualizerInfo.DllName)]
    private static partial void SetScalarData(double[] arr);

    [LibraryImport(VisualizerInfo.DllName)]
    private static partial void SetScalarDataFromElevation();

    [LibraryImport(VisualizerInfo.DllName)]
    private static partial void ReleaseData2D();

    public static void SetElevation(double[] array, int width) => SetElevationData(array, width, array.Length / width);

    public static void SetScalar(double[] array) => SetScalarData(array);

    public static void SetScalarFromElevation() => SetScalarDataFromElevation();
}
