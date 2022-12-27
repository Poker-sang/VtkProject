using System;
using System.Diagnostics.CodeAnalysis;
using System.IO;
using System.Text;

namespace Manager.Services;

public class SkipWhiteSpaceReader : StreamReader
{
    private readonly StringBuilder _stringBuilder = new();

    public T ReadNext<T>() where T : IParsable<T>
    {
        if (TryReadNext<T>(out var result))
            return result;
        ThrowHelper.InOut(nameof(ReadNext));
        return default;
    }

    public bool TryReadNext<T>([NotNullWhen(true)] out T? result) where T : IParsable<T> 
        => T.TryParse(ReadNextString(), null, out result);

    public string ReadNextString()
    {
        _ = _stringBuilder.Clear();
        int next;
        while ((next = Read()) is not -1)
        {
            var c = (char)next;
            if (char.IsWhiteSpace(c))
            {
                if (_stringBuilder.Length is not 0)
                    break;
            }
            else
                _ = _stringBuilder.Append(c);
        }

        return _stringBuilder.ToString();
    }


    public SkipWhiteSpaceReader(Stream stream) : base(stream)
    {
    }

    #region 其他构造

    public SkipWhiteSpaceReader(Stream stream, bool detectEncodingFromByteOrderMarks) : base(stream, detectEncodingFromByteOrderMarks)
    {
    }

    public SkipWhiteSpaceReader(Stream stream, Encoding encoding) : base(stream, encoding)
    {
    }

    public SkipWhiteSpaceReader(Stream stream, Encoding encoding, bool detectEncodingFromByteOrderMarks) : base(stream, encoding, detectEncodingFromByteOrderMarks)
    {
    }

    public SkipWhiteSpaceReader(Stream stream, Encoding encoding, bool detectEncodingFromByteOrderMarks, int bufferSize) : base(stream, encoding, detectEncodingFromByteOrderMarks, bufferSize)
    {
    }

    public SkipWhiteSpaceReader(Stream stream, Encoding? encoding = null, bool detectEncodingFromByteOrderMarks = true, int bufferSize = -1, bool leaveOpen = false) : base(stream, encoding, detectEncodingFromByteOrderMarks, bufferSize, leaveOpen)
    {
    }

    public SkipWhiteSpaceReader(string path) : base(path)
    {
    }

    public SkipWhiteSpaceReader(string path, bool detectEncodingFromByteOrderMarks) : base(path, detectEncodingFromByteOrderMarks)
    {
    }

    public SkipWhiteSpaceReader(string path, FileStreamOptions options) : base(path, options)
    {
    }

    public SkipWhiteSpaceReader(string path, Encoding encoding) : base(path, encoding)
    {
    }

    public SkipWhiteSpaceReader(string path, Encoding encoding, bool detectEncodingFromByteOrderMarks) : base(path, encoding, detectEncodingFromByteOrderMarks)
    {
    }

    public SkipWhiteSpaceReader(string path, Encoding encoding, bool detectEncodingFromByteOrderMarks, int bufferSize) : base(path, encoding, detectEncodingFromByteOrderMarks, bufferSize)
    {
    }

    public SkipWhiteSpaceReader(string path, Encoding encoding, bool detectEncodingFromByteOrderMarks, FileStreamOptions options) : base(path, encoding, detectEncodingFromByteOrderMarks, options)
    {
    }

    #endregion
}
