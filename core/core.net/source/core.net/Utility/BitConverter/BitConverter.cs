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
		
		public static T To<T>( byte[] bytes )
		{
			if( typeof( T ) == typeof( bool ) )
			{
				return ( T )( object )ToBoolean( bytes );
            }
			else if( typeof( T ) == typeof( sbyte ) )
			{
				return ( T )( object )ToS8( bytes );
            }
			else if( typeof( T ) == typeof( byte ) )
			{
				return ( T )( object )ToU8( bytes );
            }
			else if( typeof( T ) == typeof( short ) )
			{
				return ( T )( object )ToS16( bytes );
            }
			else if( typeof( T ) == typeof( ushort ) )
			{
				return ( T )( object )ToU16( bytes );
            }
			else if( typeof( T ) == typeof( int ) )
			{
				return ( T )( object )ToS32( bytes );
            }
			else if( typeof( T ) == typeof( uint ) )
			{
				return ( T )( object )ToU32( bytes );
            }
			else if( typeof( T ) == typeof( long ) )
			{
				return ( T )( object )ToS64( bytes );
            }
			else if( typeof( T ) == typeof( ulong ) )
			{
				return ( T )( object )ToU64( bytes );
            }
			else if( typeof( T ) == typeof( float ) )
			{
				return ( T )( object )ToF32( bytes );
			}
			else if( typeof( T ) == typeof( double ) )
			{
				return ( T )( object )ToF64( bytes );
            }

			throw new NotSupportedException();
		}
	}
}
