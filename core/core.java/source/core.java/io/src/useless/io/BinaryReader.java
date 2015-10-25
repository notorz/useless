/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.io;

import useless.io.exception.*;
import useless.type_traits.*;
import useless.utility.*;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.Array;

public class BinaryReader
{
	private StreamBase m_stream = null;
	private static byte[] m_internalBuffer = new byte[ 8 ];

	public BinaryReader()
	{

	}

	public BinaryReader( StreamBase stream )
	{
		open( stream );
	}

	public BinaryReader( byte[] address, int size )
	{
		open( address, size );
	}

	public void open( StreamBase stream )
	{
		if( stream == null || !stream.canRead() )
		{
			throw new IllegalArgumentException( "stream" );
		}

		m_stream = stream;
	}

	public void open( byte[] address, int size )
	{
		m_stream = new MemoryStream( address, size );
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

		int read = m_stream.read( buffer, count );
		if( read != count )
		{
			throw new ReadFailedException();
		}
	}

	@SuppressWarnings( "unchecked" )
	public <T> T read( Class<T> type ) throws UnsupportedEncodingException, InstantiationException, IllegalAccessException, ObjectSerializeException
	{
		if( IsArithmetic.invoke( type ) || IsChar.invoke( type ) )
		{
			read( m_internalBuffer, SizeOf.invoke( type ) );
			return BitConverter.to( type, m_internalBuffer );
		}
		else if( IsString.invoke( type ) )
		{
			return ( T )readString();
	 	}
		else if( type.isArray() )
		{
			return ( T )readArray( type );
		}
		else
		{
			T val = type.newInstance();
			if( val instanceof Serializable )
			{
				( ( Serializable )val ).deserialize( this );
				return val;
			}
			else
			{
				throw new ObjectSerializeException();
			}
		}
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

	public short readU8()
	{
		read( m_internalBuffer, 1 );
		return BitConverter.toU8( m_internalBuffer );
	}

	public short readS16()
	{
		read( m_internalBuffer, 2 );
		return BitConverter.toS16( m_internalBuffer );
	}

	public int readU16()
	{

		read( m_internalBuffer, 2 );
		return BitConverter.toU16( m_internalBuffer );
	}

	public int readS32()
	{
		read( m_internalBuffer, 4 );
		return BitConverter.toS32( m_internalBuffer );
	}

	public long readU32()
	{
		read( m_internalBuffer, 4 );
		return BitConverter.toU32( m_internalBuffer );
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

	public String readString() throws UnsupportedEncodingException
	{
		long countUnsigned = readU32();
		if( countUnsigned > Integer.MAX_VALUE )
		{
			throw new UnsupportedOperationException( "count" );
		}

		int count = ( int )countUnsigned;
		byte[] buffer = new byte[ count ];
		read( buffer, count );
		return new String( buffer, "UTF-8" );
	}

	public Object readArray( Class<?> type ) throws UnsupportedEncodingException, InstantiationException, IllegalAccessException, ObjectSerializeException
	{
		Class<?> element_type = type.getComponentType();
		if( IsArithmetic.invoke( element_type ) )
		{
			if( element_type == Boolean.class || element_type == boolean.class )
			{
				long countUnsigned = readU32();
				if( countUnsigned > Integer.MAX_VALUE )
				{
					throw new UnsupportedOperationException( "count" );
				}

				int count = ( int )countUnsigned;
				boolean[] ba = new boolean[ count ];

				for( int i = 0; i < count; ++i )
				{
					ba[ i ] = readBoolean();
				}

				return ba;
			}
			else if( element_type == Byte.class || element_type == byte.class )
			{
				long countUnsigned = readU32();
				if( countUnsigned > Integer.MAX_VALUE )
				{
					throw new UnsupportedOperationException( "count" );
				}

				int count = ( int )countUnsigned;
				byte[] ba = new byte[ count ];

				for( int i = 0; i < count; ++i )
				{
					ba[ i ] = readS8();
				}

				return ba;
			}
			else if( element_type == Short.class || element_type == short.class )
			{
				long countUnsigned = readU32();
				if( countUnsigned > Integer.MAX_VALUE )
				{
					throw new UnsupportedOperationException( "count" );
				}

				int count = ( int )countUnsigned;
				short[] sa = new short[ count ];

				for( int i = 0; i < count; ++i )
				{
					sa[ i ] = readS16();
				}

				return sa;
			}
			else if( element_type == Integer.class || element_type == int.class )
			{
				long countUnsigned = readU32();
				if( countUnsigned > Integer.MAX_VALUE )
				{
					throw new UnsupportedOperationException( "count" );
				}

				int count = ( int )countUnsigned;
				int[] ia = new int[ count ];

				for( int i = 0; i < count; ++i )
				{
					ia[ i ] = readS32();
				}

				return ia;
			}
			else if( element_type == Long.class || element_type == long.class )
			{
				long countUnsigned = readU32();
				if( countUnsigned > Integer.MAX_VALUE )
				{
					throw new UnsupportedOperationException( "count" );
				}

				int count = ( int )countUnsigned;
				long[] la = new long[ count ];

				for( int i = 0; i < count; ++i )
				{
					la[ i ] = readS64();
				}

				return la;
			}
			else if( element_type == Float.class || element_type == float.class )
			{
				long countUnsigned = readU32();
				if( countUnsigned > Integer.MAX_VALUE )
				{
					throw new UnsupportedOperationException( "count" );
				}

				int count = ( int )countUnsigned;
				float[] fa = new float[ count ];

				for( int i = 0; i < count; ++i )
				{
					fa[ i ] = readF32();
				}

				return fa;
			}
			else if( element_type == Double.class || element_type == double.class )
			{
				long countUnsigned = readU32();
				if( countUnsigned > Integer.MAX_VALUE )
				{
					throw new UnsupportedOperationException( "count" );
				}

				int count = ( int )countUnsigned;
				double[] da = new double[ count ];

				for( int i = 0; i < count; ++i )
				{
					da[ i ] = readF64();
				}

				return da;
			}
			else
			{
				throw new UnsupportedOperationException();
			}
		}
		else if( IsChar.invoke( element_type ) )
		{
			long countUnsigned = readU32();
			if( countUnsigned > Integer.MAX_VALUE )
			{
				throw new UnsupportedOperationException( "count" );
			}

			int count = ( int )countUnsigned;
			char[] ca = new char[ count ];

			for( int i = 0; i < count; ++i )
			{
				read( m_internalBuffer, 2 );
				ca[ i ] = BitConverter.toChar( m_internalBuffer );
			}

			return ca;
		}
		else
		{
			long countUnsigned = readU32();
			if( countUnsigned > Integer.MAX_VALUE )
			{
				throw new UnsupportedOperationException( "count" );
			}

			int count = ( int )countUnsigned;
			Object arrayVal = Array.newInstance( element_type, count );

			for( int i = 0; i < count; ++i )
			{
				Array.set( arrayVal, i, read( element_type ) );
			}

			return arrayVal;
		}
	}
}
