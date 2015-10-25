//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

using System;

namespace Useless.Utility
{
	public class BitConverter
	{
		public static byte[] GetBytes( Type type, object val )
		{
			if( type == typeof( bool ) )
			{
				return System.BitConverter.GetBytes( ( bool )val );
			}
			else if( type == typeof( sbyte ) )
			{
				return System.BitConverter.GetBytes( ( sbyte )val );
			}
			else if( type == typeof( byte ) )
			{
				return System.BitConverter.GetBytes( ( byte )val );
			}
			else if( type == typeof( short ) )
			{
				return System.BitConverter.GetBytes( ( short )val );
			}
			else if( type == typeof( ushort ) )
			{
				return System.BitConverter.GetBytes( ( ushort )val );
			}
			else if( type == typeof( int ) )
			{
				return System.BitConverter.GetBytes( ( int )val );
			}
			else if( type == typeof( uint ) )
			{
				return System.BitConverter.GetBytes( ( uint )val );
			}
			else if( type == typeof( long ) )
			{
				return System.BitConverter.GetBytes( ( long )val );
			}
			else if( type == typeof( ulong ) )
			{
				return System.BitConverter.GetBytes( ( ulong )val );
			}
			else if( type == typeof( float ) )
			{
				return System.BitConverter.GetBytes( ( float )val );
			}
			else if( type == typeof( double ) )
			{
				return System.BitConverter.GetBytes( ( double )val );
			}
			else if( type == typeof( char ) )
			{
				return System.BitConverter.GetBytes( ( char )val );
			}

			throw new NotSupportedException();
			
		}

		public static bool ToBoolean( byte[] bytes )
		{
			return System.BitConverter.ToBoolean( bytes, 0 );
		}

		public static char ToChar( byte[] bytes )
		{
			return System.BitConverter.ToChar( bytes, 0 );
		}

		public static sbyte ToS8( byte[] bytes )
		{
			return ( sbyte )bytes[ 0 ];
		}

		public static byte ToU8( byte[] bytes )
		{
			return bytes[ 0 ];
		}

		public static short ToS16( byte[] bytes )
		{
			return System.BitConverter.ToInt16( bytes, 0 );
		}

		public static ushort ToU16( byte[] bytes )
		{
			return System.BitConverter.ToUInt16( bytes, 0 );
		}

		public static int ToS32( byte[] bytes )
		{
			return System.BitConverter.ToInt32( bytes, 0 );
		}

		public static uint ToU32( byte[] bytes )
		{
			return System.BitConverter.ToUInt32( bytes, 0 );
		}

		public static long ToS64( byte[] bytes )
		{
			return System.BitConverter.ToInt64( bytes, 0 );
		}

		public static ulong ToU64( byte[] bytes )
		{
			return System.BitConverter.ToUInt64( bytes, 0 );
		}

		public static float ToF32( byte[] bytes )
		{
			return System.BitConverter.ToSingle( bytes, 0 );
		}

		public static double ToF64( byte[] bytes )
		{
			return System.BitConverter.ToDouble( bytes, 0 );
		}
		
		public static object To( Type type, byte[] bytes )
		{
			if( type == typeof( bool ) )
			{
				return ToBoolean( bytes );
			}
			else if( type == typeof( sbyte ) )
			{
				return ToS8( bytes );
			}
			else if( type == typeof( byte ) )
			{
				return ToU8( bytes );
			}
			else if( type == typeof( short ) )
			{
				return ToS16( bytes );
			}
			else if( type == typeof( ushort ) )
			{
				return ToU16( bytes );
			}
			else if( type == typeof( int ) )
			{
				return ToS32( bytes );
			}
			else if( type == typeof( uint ) )
			{
				return ToU32( bytes );
			}
			else if( type == typeof( long ) )
			{
				return ToS64( bytes );
			}
			else if( type == typeof( ulong ) )
			{
				return ToU64( bytes );
			}
			else if( type == typeof( float ) )
			{
				return ToF32( bytes );
			}
			else if( type == typeof( double ) )
			{
				return ToF64( bytes );
			}
			else if( type == typeof( char ) )
			{
				return ToChar( bytes );
			}

			throw new NotSupportedException();
		}

		public static T To<T>( byte[] bytes )
		{
			return ( T )( To( typeof( T ), bytes ) );
		}
	}
}
