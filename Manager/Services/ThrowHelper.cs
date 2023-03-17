using System.Diagnostics.CodeAnalysis;
using System.Runtime.CompilerServices;
using System.IO;

namespace Manager.Services;

public static class ThrowHelper
{
    [DoesNotReturn]
    [MethodImpl(MethodImplOptions.NoInlining)]
    public static void InOut(string? message = null) => throw new IOException(message);
}
