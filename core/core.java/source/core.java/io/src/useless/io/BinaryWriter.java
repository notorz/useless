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
import java.util.*;

public class BinaryWriter
{
	private StreamBase m_stream = null;

	public BinaryWriter()
	{

	}

	public BinaryWriter( StreamBase stream )
	{
		open( stream );
	}

	public BinaryWriter( int size, boolean growable )
	{
		open( size, growable );
	}

	public BinaryWriter( int size )
	{
		open( size );
	}

	public BinaryWriter( byte[] address, int size )
	{
		open( address, size );
	}

	public void open( StreamBase stream )
	{
		if( stream == null || !stream.canWrite() )
		{
			throw new IllegalArgumentException( "stream" );
		}

		m_stream = stream;
	}

	public void open( int size, boolean growable )
	{
		if( growable )
		{
			m_stream = new DynamicStream( size );
		}
		else
		{
			m_stream = new FixedStream( size );
		}
	}

	public void open( int size )
	{
		open( size, true );
	}

	public void open( byte[] address, int size )
	{
		m_stream = new MemoryStream( address, size );
	}

	public StreamBase getStream()
	{
		return m_stream;
	}

	public void write( byte[] buffer, int count )
	{
		if( m_stream == null )
		{
			throw new NullPointerException( "stream" );
		}

		int write = m_stream.write( buffer, count );
		if( write != count )
		{
			throw new WriteFailedException();
		}
	}

	public void write( Object val ) throws UnsupportedEncodingException, ObjectSerializeException
	{
		Class<?> type = val.getClass();
		if( IsArithmetic.invoke( type ) )
		{
			if( type == Boolean.class || type == boolean.class )
			{
				writeBoolean( ( Boolean ) val );
			}
			else if( type == Byte.class || type == byte.class )
			{
				writeS8( ( Byte ) val );
			}
			else if( type == Short.class || type == short.class )
			{
				writeS16( ( Short ) val );
			}
			else if( type == Integer.class || type == int.class )
			{
				writeS32( ( Integer ) val );
			}
			else if( type == Long.class || type == long.class )
			{
				writeS64( ( Long ) val );
			}
			else if( type == Float.class || type == float.class )
			{
				writeF32( ( Float ) val );
			}
			else if( type == Double.class || type == double.class )
			{
				writeF64( ( Double ) val );
			}
			else
			{
				throw new UnsupportedOperationException();
			}
		}
		else if( IsChar.invoke( type ) )
		{
			write( BitConverter.getBytes( ( Character )val ), 2 );
		}
		else if( IsString.invoke( type ) )
		{
			writeString( ( String ) val );
		}
		else if( type.isArray() )
		{
			writeArray( type, val );
		}
		else
		{
			if( val instanceof Collection<?> )
			{
				Collection<?> collectionVal = ( Collection<?> )val;
				int count = collectionVal.size();
				writeU32( ( long ) count );
				for( Object temp : collectionVal )
				{
					write( temp );
				}
			}
			else if( val instanceof Map<?, ?> )
			{
				Map<?, ?> mapVal = ( Map<?, ?> )val;
				int count = mapVal.size();
				writeU32( ( long ) count );
				Iterator<?> iterator = mapVal.entrySet().iterator();
				while( iterator.hasNext() )
				{
					Map.Entry temp = ( Map.Entry )iterator.next();
					write( temp.getKey() );
					write( temp.getValue() );
				}
			}
			else if( val instanceof Serializable )
			{
				( ( Serializable )val ).serialize( this );
			}
			else
			{
				throw new ObjectSerializeException();
			}
		}
	}

	public void writeBoolean( boolean val )
	{
		write( BitConverter.getBytes( val ), 1 );
	}

	public void writeS8( byte val )
	{
		write( BitConverter.getBytes( val ), 1 );
	}

	public void writeU8( short val )
	{
		write( BitConverter.getBytes_U8( val ), 1 );
	}

	public void writeS16( short val )
	{
		write( BitConverter.getBytes( val ), 2 );
	}

	public void writeU16( int val )
	{
		write( BitConverter.getBytes_U16( val ), 2 );
	}

	public void writeS32( int val )
	{
		write( BitConverter.getBytes( val ), 4 );
	}

	public void writeU32( long val )
	{
		write( BitConverter.getBytes_U32( val ), 4 );
	}

	public void writeS64( long val )
	{
		write( BitConverter.getBytes( val ), 8 );
	}

	public void writeF32( float val )
	{
		write( BitConverter.getBytes( val ), 4 );
	}

	public void writeF64( double val )
	{
		write( BitConverter.getBytes( val ), 8 );
	}

	public void writeString( String val ) throws UnsupportedEncodingException
	{
		String stringVal = ( String )val;
		byte[] stringBytes = stringVal.getBytes( "UTF-8" );
		int count = stringBytes.length;
		writeU32( ( long ) count );
		write( stringBytes, count );
	}

	public void writeArray( Class<?> type, Object val ) throws UnsupportedEncodingException, ObjectSerializeException
	{
		Class<?> element_type = type.getComponentType();
		if( IsArithmetic.invoke( element_type ) )
		{
			if( element_type == Boolean.class || element_type == boolean.class )
			{
				boolean[] ba = ( boolean[] )val;
				writeU32( ( long )ba.length );
				for( boolean temp : ba )
				{
					writeBoolean( temp );
				}
			}
			else if( element_type == Byte.class || element_type == byte.class )
			{
				byte[] ba = ( byte[] )val;
				writeU32( ( long )ba.length );
				for( byte temp : ba )
				{
					writeS8( temp );
				}
			}
			else if( element_type == Short.class || element_type == short.class )
			{
				short[] sa = ( short[] )val;
				writeU32( ( long )sa.length );
				for( short temp : sa )
				{
					writeS16( temp );
				}
			}
			else if( element_type == Integer.class || element_type == int.class )
			{
				int[] ia = ( int[] )val;
				writeU32( ( long )ia.length );
				for( int temp : ia )
				{
					writeS32( temp );
				}
			}
			else if( element_type == Long.class || element_type == long.class )
			{
				long[] la = ( long[] )val;
				writeU32( ( long )la.length );
				for( long temp : la )
				{
					writeS64( temp );
				}
			}
			else if( element_type == Float.class || element_type == float.class )
			{
				float[] fa = ( float[] )val;
				writeU32( ( long )fa.length );
				for( float temp : fa )
				{
					writeF32( temp );
				}
			}
			else if( element_type == Double.class || element_type == double.class )
			{
				double[] da = ( double[] )val;
				writeU32( ( long )da.length );
				for( double temp : da )
				{
					writeF64( temp );
				}
			}
			else
			{
				throw new UnsupportedOperationException();
			}
		}
		else if( IsChar.invoke( element_type ) )
		{
			char[] ca = ( char[] )val;
			writeU32( ( long )ca.length );
			for( char temp : ca )
			{
				write( BitConverter.getBytes( temp ), 2 );
			}
		}
		else
		{
			Object[] arrayVal = ( Object[] )val;
			writeU32( ( long )arrayVal.length );

			for( Object obj : arrayVal )
			{
				write( obj );
			}
		}
	}
}
