/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.io;

public class MemoryStream implements StreamBase
{
	private byte[] m_base = null;
	private int m_size = 0;
	private int m_position = 0;

	public MemoryStream( byte[] address, int size )
	{
		if( address == null )
		{
			throw new IllegalArgumentException( "buffer" );
		}

		if( size < 1 )
		{
			throw new IllegalArgumentException( "size" );
		}

		m_base = address;
		m_size = size;
	}

	public int getSize()
	{
		return m_size;
	}

	public boolean canRead()
	{
		return true;
	}

	public boolean canWrite()
	{
		return ( m_size > m_position );
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

		if( count < 1 )
		{
			throw new IllegalArgumentException( "count" );
		}

		if( !canRead() )
		{
			return 0;
		}

		int read = ( ( m_position + count ) > m_size ) ? ( m_size - m_position ) : count;

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

		int write = ( ( m_position + count ) > m_size ) ? ( m_size - m_position ) : count;

		System.arraycopy( buffer, 0, m_base, m_position, write );
		m_position += write;

		return write;
	}

	public int setPos( SeekDir way, int off )
	{
		if( way == SeekDir.end )
		{
			off += m_size;
		}
		else if( way == SeekDir.cur )
		{
			off += m_position;
		}

		if( off >= 0 && m_size >= off )
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
}
