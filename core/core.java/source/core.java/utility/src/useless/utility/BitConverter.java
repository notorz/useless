/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.utility;

import com.sun.org.apache.xpath.internal.operations.Bool;

public class BitConverter
{
	public static byte[] getBytes( boolean value )
	{
		return new byte[]
				{
					( byte )( value ? 1 : 0 )
				};
	}

	public static byte[] getBytes( byte value )
	{
		return new byte[]
				{
					value
				};
	}

	public static byte[] getBytes( char value )
	{
		return new byte[]
				{
					( byte )( ( value ) & 0xFF ),
					( byte )( ( value >> 8 ) & 0xFF )
				};
	}

	public  static byte[] getBytes( short value )
	{
		return new byte[]
				{
					( byte ) ( ( value ) & 0xFF ),
					( byte ) ( ( value >> 8 ) & 0xFF )
				};
	}

	public static byte[] getBytes( int value )
	{
		return new byte[]
				{
					( byte )( ( value ) & 0xFF ),
					( byte )( ( value >> 8 ) & 0xFF ),
					( byte )( ( value >> 16 ) & 0xFF ),
					( byte )( ( value >> 24 ) & 0xFF )
				};
	}

	public static byte[] getBytes( long value )
	{
		return new byte[]
				{
					( byte )( ( value ) & 0xFF ),
					( byte )( ( value >> 8 ) & 0xFF ),
					( byte )( ( value >> 16 ) & 0xFF ),
					( byte )( ( value >> 24 ) & 0xFF ),
					( byte )( ( value >> 32 ) & 0xFF ),
					( byte )( ( value >> 40 ) & 0xFF ),
					( byte )( ( value >> 48 ) & 0xFF ),
					( byte )( ( value >> 56 ) & 0xFF ),
				};
	}

	public static byte[] getBytes( float value )
	{
		return getBytes( Float.floatToRawIntBits( value ) );
	}

	public static byte[] getBytes( double value )
	{
		return getBytes( Double.doubleToRawLongBits( value ) );
	}

	public static byte[] getBytes( String value )
	{
		return value.getBytes();
	}

	public static byte[] getBytes_U8( short value )
	{
		return new byte[]
				{
						( byte ) ( ( value ) & 0xFF )
				};
	}

	public static byte[] getBytes_U16( int value )
	{
		return new byte[]
				{
						( byte ) ( ( value ) & 0xFF ),
						( byte ) ( ( value >> 8 ) & 0xFF )
				};
	}

	public static byte[] getBytes_U32( long value )
	{
		return new byte[]
				{
						( byte )( ( value ) & 0xFF ),
						( byte )( ( value >> 8 ) & 0xFF ),
						( byte )( ( value >> 16 ) & 0xFF ),
						( byte )( ( value >> 24 ) & 0xFF )
				};
	}

	public static <T> byte[] getBytes( Class<T> type, T value )
	{
		if( type == Boolean.class || type == boolean.class )
		{
			return getBytes( ( Boolean )value );
		}
		else if( type == Character.class || type == char.class )
		{
			return getBytes( ( Character )value );
		}
		else if( type == Byte.class || type == byte.class )
		{
			return getBytes( ( Byte )value );
		}
		else if( type == Short.class || type == short.class )
		{
			return getBytes( ( Short )value );
		}
		else if( type == Integer.class || type == int.class )
		{
			return getBytes( ( Integer )value );
		}
		else if( type == Long.class || type == long.class )
		{
			return getBytes( ( Long )value );
		}
		else if( type == Float.class || type == float.class )
		{
			return getBytes( ( Float )value );
		}
		else if( type == Double.class || type == double.class )
		{
			return getBytes( ( Double )value );
		}

		throw new UnsupportedOperationException();
	}

	public static boolean toBoolean( byte[] bytes ) throws IllegalArgumentException
	{
		if( bytes == null || bytes.length < 1 )
		{
			throw new IllegalArgumentException( "bytes" );
		}

		return ( bytes[ 0 ] != 0 );
	}

	public static char toChar( byte[] bytes ) throws IllegalArgumentException
	{
		if( bytes == null || bytes.length < 2 )
		{
			throw new IllegalArgumentException( "bytes" );
		}

		return ( char )
				(
					( ( char )( bytes[ 0 ] ) << 8 ) |
					( ( char )( bytes[ 1 ] ) )
				);
	}

	public static byte toS8( byte[] bytes ) throws IllegalArgumentException
	{
		if( bytes == null || bytes.length < 1 )
		{
			throw new IllegalArgumentException( "bytes" );
		}

		return bytes[ 0 ];
	}

	public static short toU8( byte[] bytes ) throws IllegalArgumentException
	{
		if( bytes == null || bytes.length < 1 )
		{
			throw new IllegalArgumentException( "bytes" );
		}

		return ( short )bytes[ 0 ];
	}

	public static short toS16( byte[] bytes ) throws IllegalArgumentException
	{
		if( bytes == null || bytes.length < 2 )
		{
			throw new IllegalArgumentException( "bytes" );
		}

		return ( short )
				(
					( ( short )( bytes[ 0 ] ) |
					( ( short )( bytes[ 1 ] ) << 8 ) )
				);
	}

	public static int toU16( byte[] bytes ) throws IllegalArgumentException
	{
		if( bytes == null || bytes.length < 2 )
		{
			throw new IllegalArgumentException( "bytes" );
		}

		return ( int )
				(
					( ( short )( bytes[ 0 ] ) |
					( ( short )( bytes[ 1 ] ) << 8 ) )
				);
	}

	public static int toS32( byte[] bytes ) throws IllegalArgumentException
	{
		if( bytes == null || bytes.length < 4 )
		{
			throw new IllegalArgumentException( "bytes" );
		}

		return ( int )
				(
					( ( int )( bytes[ 0 ] ) |
					( ( int )( bytes[ 1 ] ) << 8 ) |
					( ( int )( bytes[ 2 ] ) << 16 ) |
					( ( int )( bytes[ 3 ] ) << 24 ) )
				);
	}

	public static long toU32( byte[] bytes ) throws IllegalArgumentException
	{
		if( bytes == null || bytes.length < 4 )
		{
			throw new IllegalArgumentException( "bytes" );
		}

		return ( long )
				(
					( ( long )( bytes[ 0 ] ) |
					( ( long )( bytes[ 1 ] ) << 8 ) |
					( ( long )( bytes[ 2 ] ) << 16 ) |
					( ( long )( bytes[ 3 ] ) << 24 ) )
				);
	}

	public static long toS64( byte[] bytes ) throws IllegalArgumentException
	{
		if( bytes == null || bytes.length < 8 )
		{
			throw new IllegalArgumentException( "bytes" );
		}

		return ( long )
				(
					( ( long )( bytes[ 0 ] ) |
					( ( long )( bytes[ 1 ] ) << 8 ) |
					( ( long )( bytes[ 2 ] ) << 16 ) |
					( ( long )( bytes[ 3 ] ) << 24 ) |
					( ( long )( bytes[ 4 ] ) << 32 ) |
					( ( long )( bytes[ 5 ] ) << 40 ) |
					( ( long )( bytes[ 6 ] ) << 48 ) |
					( ( long )( bytes[ 7 ] ) << 56 ) )
				);
	}

	public static float toF32( byte[] bytes ) throws IllegalArgumentException
	{
		if( bytes == null || bytes.length < 4 )
		{
			throw new IllegalArgumentException( "bytes" );
		}

		return Float.intBitsToFloat( toS32( bytes ) );
	}

	public static double toF64( byte[] bytes ) throws IllegalArgumentException
	{
		if( bytes == null || bytes.length < 8 )
		{
			throw new IllegalArgumentException( "bytes" );
		}

		return Double.longBitsToDouble( toS64( bytes ) );
	}

	public static String toString( byte[] bytes ) throws IllegalArgumentException
	{
		if( bytes == null )
		{
			throw new IllegalArgumentException( "bytes" );
		}

		return new String( bytes );
	}

	public static <T> T to( Class<T> type, byte[] bytes )
	{
		if( type == Boolean.class || type == boolean.class )
		{
			return ( T )( Object )toBoolean( bytes );
		}
		else if( type == Character.class || type == char.class )
		{
			return ( T )( Object )toChar( bytes );
		}
		else if( type == Byte.class || type == byte.class )
		{
			return ( T )( Object )toS8( bytes );
		}
		else if( type == Short.class || type == short.class )
		{
			return ( T )( Object )toS16( bytes );
		}
		else if( type == Integer.class || type == int.class )
		{
			return ( T )( Object )toS32( bytes );
		}
		else if( type == Long.class || type == long.class )
		{
			return ( T )( Object )toS64( bytes );
		}
		else if( type == Float.class || type == float.class )
		{
			return ( T )( Object )toF32( bytes );
		}
		else if( type == Double.class || type == double.class )
		{
			return ( T )( Object )toF64( bytes );
		}

		throw new UnsupportedOperationException();
	}
}
