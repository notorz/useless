//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

using System;

namespace Useless.IO
{
    public enum SeekDir
    {
        Begin = 0,
        Current = 1,
        End = 2
    }

    public interface IStream : IDisposable
    {
		int Length { get; }
		int Position { get; set; }
        bool CanRead { get; }
        bool CanWrite { get; }
        byte[] GetBuffer();
		int Read( byte[] buffer, int count );
		int Write( byte[] buffer, int count );
		int Seek( int offset, SeekDir way );
    }
}
