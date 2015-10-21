/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.utility;

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
						( byte ) ( ( value >> 8 ) & 0xFF ),
						( byte ) ( ( value ) & 0xFF )
				};
	}

	public static byte[] getBytes( int value )
	{
		return new byte[]
				{
						( byte )( ( value >> 24 ) & 0xFF ),
						( byte )( ( value >> 16 ) & 0xFF ),
						( byte )( ( value >> 8 ) & 0xFF ),
						( byte )( ( value ) & 0xFF )
				};
	}

	public static byte[] getBytes( long value )
	{
		return new byte[]
				{
					( byte )( ( value >> 56 ) & 0xFF ),
					( byte )( ( value >> 48 ) & 0xFF ),
					( byte )( ( value >> 40 ) & 0xFF ),
					( byte )( ( value >> 32 ) & 0xFF ),
					( byte )( ( value >> 24 ) & 0xFF ),
					( byte )( ( value >> 16 ) & 0xFF ),
					( byte )( ( value >> 8 ) & 0xFF ),
					( byte )( ( value ) & 0xFF )
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

	public static short toS16( byte[] bytes ) throws IllegalArgumentException
	{
		if( bytes == null || bytes.length < 2 )
		{
			throw new IllegalArgumentException( "bytes" );
		}

		return ( short )
				(
					( ( short )( bytes[ 0 ] ) << 8 ) |
					( ( short )( bytes[ 1 ] ) )
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
					( ( int )( bytes[ 0 ] ) << 24 ) |
					( ( int )( bytes[ 1 ] ) << 16 ) |
					( ( int )( bytes[ 2 ] ) << 8 ) |
					( ( int )( bytes[ 3 ] ) )
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
					( ( long )( bytes[ 0 ] ) << 56 ) |
					( ( long )( bytes[ 1 ] ) << 48 ) |
					( ( long )( bytes[ 2 ] ) << 40 ) |
					( ( long )( bytes[ 3 ] ) << 32 ) |
					( ( long )( bytes[ 4 ] ) << 24 ) |
					( ( long )( bytes[ 5 ] ) << 16 ) |
					( ( long )( bytes[ 6 ] ) << 8 ) |
					( ( long )( bytes[ 7 ] ) )
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

	public static <T> T to( Class<T> classT, byte[] bytes )
	{
		if( classT == Boolean.class )
		{
			return ( T )( Object )toBoolean( bytes );
		}
		else if( classT == Character.class )
		{
			return ( T )( Object )toChar( bytes );
		}
		else if( classT == Byte.class )
		{
			return ( T )( Object )toS8( bytes );
		}
		else if( classT == Short.class )
		{
			return ( T )( Object )toS16( bytes );
		}
		else if( classT == Integer.class )
		{
			return ( T )( Object )toS32( bytes );
		}
		else if( classT == Long.class )
		{
			return ( T )( Object )toS64( bytes );
		}
		else if( classT == Float.class )
		{
			return ( T )( Object )toF32( bytes );
		}
		else if( classT == Double.class )
		{
			return ( T )( Object )toF64( bytes );
		}

		throw new UnsupportedOperationException();
	}
}
