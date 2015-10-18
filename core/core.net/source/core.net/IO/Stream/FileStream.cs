//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

using System;
using System.IO;

namespace Useless.IO
{
	/// <summary>
	/// 파일을 읽거나 쓸 때 사용하는 스트림입니다.
	/// </summary>
	public class FileStream : IStream
    {
		System.IO.FileStream m_file;

		public int Length { get { return ( int )m_file.Length; } }
		public int Position { get { return ( int )m_file.Position; } set { m_file.Position = ( long )value; } }
		public bool CanRead { get { return m_file.CanRead; } }
		public bool CanWrite { get { return m_file.CanWrite; } }

		public FileStream( String path, System.IO.FileMode filemode )
		{
			m_file = File.Create( path );
		}

		public void Dispose()
		{
			m_file.Dispose();
		}

		public byte[] GetBuffer()
		{
			return null;
		}

		public int Read( byte[] buffer, int count )
		{
			if( buffer == null )
			{
				throw new ArgumentNullException( "buffer" );
			}

			if( count < 0 )
			{
				throw new ArgumentOutOfRangeException( "count" );
			}
			
			return m_file.Read( buffer, 0, count );
		}

		public int Write( byte[] buffer, int count )
		{
			if( buffer == null )
			{
				throw new ArgumentNullException( "buffer" );
			}

			if( count < 0 )
			{
				throw new ArgumentOutOfRangeException( "count" );
			}

			m_file.Write( buffer, 0, count );
			return count;
		}

		public int Seek( int offset, SeekDir way )
		{
			return ( int )m_file.Seek( offset, ( SeekOrigin )way );
		}
	}
}
