/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.io;

import useless.type_traits.IsFundamental;
import useless.type_traits.IsString;
import useless.type_traits.SizeOf;
import useless.utility.*;

import java.io.UnsupportedEncodingException;
import java.util.*;

public class BinaryReader
{
	private StreamBase m_stream = null;
	private static byte[] m_internalBuffer = new byte[ 8 ];

	public BinaryReader()
	{

	}

	public BinaryReader( StreamBase stream )
	{
		if( stream == null || !stream.canRead() )
		{
			throw new IllegalArgumentException( "stream" );
		}

		m_stream = stream;
	}

	public BinaryReader( byte[] address, int size )
	{
		m_stream = new MemoryStream( address, size );
	}

	public void setStream( StreamBase stream )
	{
		if( stream == null || !stream.canRead() )
		{
			throw new IllegalArgumentException( "stream" );
		}

		m_stream = stream;
	}

	public StreamBase getStream()
	{
		return m_stream;
	}

	public void read( byte[] buffer, int count )
	{
		if( m_stream == null  )
		{
			throw new NullPointerException( "stream" );
		}

		m_stream.read( buffer, count );
	}

	public boolean readBoolean()
	{
		read( m_internalBuffer, 1 );
		return BitConverter.toBoolean( m_internalBuffer );
	}

	public byte readS8()
	{
		read( m_internalBuffer, 1 );
		return BitConverter.toS8( m_internalBuffer );
	}

	public int readU8()
	{
		read( m_internalBuffer, 1 );
		return ( int )( BitConverter.toS8( m_internalBuffer ) & 0xFF );
	}

	public short readS16()
	{
		read( m_internalBuffer, 2 );
		return BitConverter.toS16( m_internalBuffer );
	}

	public int readU16()
	{
		read( m_internalBuffer, 2 );
		return ( int )( BitConverter.toS16( m_internalBuffer ) & 0xFFFF );
	}

	public int readS32()
	{
		read( m_internalBuffer, 4 );
		return BitConverter.toS32( m_internalBuffer );
	}

	public long readU32()
	{
		read( m_internalBuffer, 4 );
		return ( long )( BitConverter.toS32( m_internalBuffer ) & 0xFFFFFFFF );
	}

	public long readS64()
	{
		read( m_internalBuffer, 8 );
		return BitConverter.toS64( m_internalBuffer );
	}

	public float readF32()
	{
		read( m_internalBuffer, 4 );
		return BitConverter.toF32( m_internalBuffer );
	}

	public double readF64()
	{
		read( m_internalBuffer, 8 );
		return BitConverter.toF64( m_internalBuffer );
	}

	public <T> T read( Class<T> classT ) throws InstantiationException, IllegalAccessException, UnsupportedEncodingException
	{
		if( IsFundamental.invoke( classT ) )
		{
			read( m_internalBuffer, SizeOf.invoke( classT ) );
			return BitConverter.to( classT, m_internalBuffer );
		}
		else if( IsString.invoke( classT ) )
		{
			long longCount = readU32();
			if( longCount > Integer.MAX_VALUE )
			{
				throw new UnsupportedOperationException( "count" );
			}

			int count = ( int )longCount;
			byte[] buffer = new byte[ count ];
			read( buffer, count );
			return ( T )new String( buffer, "UTF-8" );
		}
		else
		{
			T val = classT.newInstance();
			if( val instanceof Serializable )
			{
				( ( Serializable )val ).Serialize( this );
				return val;
			}
		}

		throw new UnsupportedOperationException();
	}
}
