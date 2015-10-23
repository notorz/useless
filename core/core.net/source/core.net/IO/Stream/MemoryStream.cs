//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

using System;

namespace Useless.IO
{
	/// <summary>
	/// 외부에서 생성된 메모리를 읽을 때 사용하는 스트림입니다.
	/// </summary>
	public class MemoryStream : IStream
    {
        private byte[] m_base = null;
        private int m_size = 0;
        private int m_position = 0;

		public int Length { get { return m_size; } }
		public int Position { get { return m_position; } set { m_position = value; } }
		public bool CanRead { get { return true; } }
		public bool CanWrite { get { return ( m_size > m_position ); } }

		public MemoryStream( byte[] address, int size )
        {
			if( address == null )
			{
				throw new ArgumentNullException( "buffer" );
			}

			if( size < 1 )
			{
				throw new ArgumentOutOfRangeException( "size" );
			}

			if( address.Length < size )
			{
				throw new ArgumentOutOfRangeException( "size" );
			}

			m_base = address;
            m_size = size;
        }

        public void Dispose()
        {

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

            int read = ( ( m_position + count ) > m_size ) ? ( m_size - m_position ) : count;

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

            int write = ( ( m_position + count ) > m_size ) ? ( m_size - m_position ) : count;

            Buffer.BlockCopy( buffer, 0, m_base, m_position, write );
            m_position += write;

            return write;
        }

        public int Seek( int offset, SeekDir way )
        {
			if( way == SeekDir.End )
            {
                offset += m_size;
            }
            else if( way == SeekDir.Current )
            {
                offset += m_position;
            }

            if( offset >= 0 && m_size >= offset )
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
