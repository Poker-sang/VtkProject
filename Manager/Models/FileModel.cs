using System;
using System.IO;
using Manager.Enums;
using Manager.Services;

namespace Manager.Models;

public record FileModel(
    string Name,
    string Path,
    FileExtension Extension)
{
    public string FullName => $"{Path}\\{Name}";

    public double[] GetDataFromFile(out int width, out int height)
    {
        using var fs = File.OpenRead(FullName);
        using var reader = new SkipWhiteSpaceReader(fs);
        switch (Extension)
        {
            case FileExtension.Grd:
                width = reader.ReadNext<int>();
                height = reader.ReadNext<int>();
                _ = reader.ReadNextString();
                _ = reader.ReadNextString();
                _ = reader.ReadNextString();
                _ = reader.ReadNextString();
                break;
            case FileExtension.Dem:
                _ = reader.ReadNextString();
                _ = reader.ReadNextString();
                _ = reader.ReadNextString();
                _ = reader.ReadNextString();
                _ = reader.ReadNextString();
                _ = reader.ReadNextString();
                _ = reader.ReadNextString();
                _ = reader.ReadNextString();
                width = reader.ReadNext<int>();
                height = reader.ReadNext<int>();
                _ = reader.ReadNextString();
                _ = reader.ReadNextString();
                break;
            case FileExtension.Unknown:
            default:
                width = height = 0;
                return Array.Empty<double>();
        }

        var data = new double[width * height];
        for (var i = 0; i < width * height; ++i)
            data[i] = reader.ReadNext<double>();
        return data;
    }
}
