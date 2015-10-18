//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

using System;

namespace Useless.IO
{
	/// <summary>
	/// 처음 주어진 크기를 기준으로 크기가 늘어날 수 있는 스트림입니다.
	/// 스트림에 쓰기를 할 때 공간이 부족하면 크기를 늘리게 되며, 크기는 피보나치 수열에 기반하여 늘어납니다.
	/// </summary>
	public class DynamicStream : IStream
	{
		private byte[] m_base = null;
		private int m_position = 0;
		private int m_seekhigh = 0;

		public int Length { get { return m_base.Length; } }
		public int Position { get { return m_position; } set { m_position = value; } }
		public bool CanRead { get { return m_seekhigh > m_position; } }
		public bool CanWrite { get { return true; } }

		public DynamicStream( uint size )
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

			if( ( m_position + count ) > m_base.Length )
			{
				byte[] newBuffer = new byte[ GetFibonacci( m_position + count ) ];
				Buffer.BlockCopy( m_base, 0, newBuffer, 0, m_seekhigh );
				m_base = newBuffer;
			}

			Buffer.BlockCopy( buffer, 0, m_base, m_position, count );
			m_position += count;

			if( m_position > m_seekhigh )
			{
				m_seekhigh = m_position;
			}

			return count;
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

		private static int GetFibonacci( int number )
		{
			int f = 0;
			int s = 1;
			int r = 0;
			while( r <= number )
			{
				r = f + s;
				f = s;
				s = r;
			}

			return r;
		}
    }
}
