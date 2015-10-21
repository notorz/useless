/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.io;

public class DynamicStream implements StreamBase
{
	private byte[] m_base = null;
	private int m_position = 0;
	private int m_seekhigh = 0;

	DynamicStream( int size )
	{
		if( size < 1 )
		{
			throw new IllegalArgumentException( "size" );
		}

		m_base = new byte[ size ];
	}

	public int getSize()
	{
		return m_base.length;
	}

	public boolean canRead()
	{
		return ( m_seekhigh > m_position );
	}

	public boolean canWrite()
	{
		return true;
	}

	public byte[] getBuffer()
	{
		return m_base;
	}

	public int read( byte[] buffer, int count )
	{
		if( buffer == null )
		{
			throw new IllegalArgumentException( "buffer" );
		}

		if( count < 0 )
		{
			throw new IllegalArgumentException( "count" );
		}

		if( !canRead() )
		{
			return 0;
		}

		int read = ( ( m_position + count ) > m_seekhigh ) ? ( m_seekhigh - m_position ) : count;

		System.arraycopy( m_base, m_position, buffer, 0, read );
		m_position += read;

		return read;
	}

	public int write( byte[] buffer, int count )
	{
		if( buffer == null )
		{
			throw new IllegalArgumentException( "buffer" );
		}

		if( count < 0 )
		{
			throw new IllegalArgumentException( "count" );
		}

		if( !canWrite() )
		{
			return 0;
		}

		if( ( m_position + count ) > m_base.length )
		{
			byte[] newBuffer = new byte[ getFibonacci( m_position + count ) ];
			System.arraycopy( m_base, 0, newBuffer, 0, m_seekhigh );
			m_base = newBuffer;
		}

		System.arraycopy( buffer, 0, m_base, m_position, count );
		m_position += count;

		if( m_position > m_seekhigh )
		{
			m_seekhigh = m_position;
		}

		return count;
	}

	public int setPos( SeekDir way, int off )
	{
		if( way == SeekDir.end )
		{
			off += m_seekhigh;
		}
		else if( way == SeekDir.cur )
		{
			off += m_position;
		}

		if( off >= 0 && m_seekhigh >= off )
		{
			m_position = off;
		}
		else
		{
			off = -1;
		}

		return off;
	}

	public int getPos()
	{
		return m_position;
	}

	private static int getFibonacci( int number )
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
