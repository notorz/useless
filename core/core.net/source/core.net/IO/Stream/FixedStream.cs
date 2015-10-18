//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

using System;

namespace Useless.IO
{
	/// <summary>
	/// 처음에 주어진 크기만 사용하는 고정 크기의 스트림입니다.
	/// </summary>
	public class FixedStream : IStream
    {
        private byte[] m_base = null;
        private int m_position = 0;
        private int m_seekhigh = 0;

		public int Length { get { return m_base.Length; } }
		public int Position { get { return m_position; } set { m_position = value; } }
		public bool CanRead { get { return m_seekhigh > m_position; } }
		public bool CanWrite { get { return m_base.Length > m_position; } }

		public FixedStream( int size )
		{
			m_base = new byte[ size ];
		}

		public void Dispose()
		{
			m_base = null;
		}
		
		public byte[] GetBuffer()
		{
			return m_base;
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

			if( !CanRead )
			{
				return 0;
			}

			int read = ( ( m_position + count ) > m_seekhigh ) ? ( m_seekhigh - m_position ) : count;

			Buffer.BlockCopy( m_base, m_position, buffer, 0, read );
			m_position += read;

			return read;
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

			if( !CanWrite )
			{
				return 0;
			}

			int write = ( ( m_position + count ) > m_base.Length ) ? ( m_base.Length - m_position ) : count;

			Buffer.BlockCopy( buffer, 0, m_base, m_position, write );
			m_position += write;

			if( m_position > m_seekhigh )
			{
				m_seekhigh = m_position;
			}

			return write;
		}

        public int Seek( int offset, SeekDir way )
        {
			if( way == SeekDir.End )
			{
				offset += m_seekhigh;
			}
			else if( way == SeekDir.Current )
			{
				offset += m_position;
			}

			if( offset >= 0 && m_seekhigh >= offset )
			{
				m_position = offset;
			}
			else
			{
				offset = -1;
			}

			return offset;
		}
    }
}
