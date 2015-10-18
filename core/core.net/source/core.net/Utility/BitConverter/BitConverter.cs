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
		public static bool ToBoolean( byte[] buffer )
		{
			return System.BitConverter.ToBoolean( buffer, 0 );
		}

		public static sbyte ToS8( byte[] buffer )
		{
			return ( sbyte )buffer[ 0 ];
		}

		public static byte ToU8( byte[] buffer )
		{
			return buffer[ 0 ];
		}

		public static short ToS16( byte[] buffer )
		{
			return System.BitConverter.ToInt16( buffer, 0 );
		}

		public static ushort ToU16( byte[] buffer )
		{
			return System.BitConverter.ToUInt16( buffer, 0 );
		}

		public static int ToS32( byte[] buffer )
		{
			return System.BitConverter.ToInt32( buffer, 0 );
		}

		public static uint ToU32( byte[] buffer )
		{
			return System.BitConverter.ToUInt32( buffer, 0 );
		}

		public static long ToS64( byte[] buffer )
		{
			return System.BitConverter.ToInt64( buffer, 0 );
		}

		public static ulong ToU64( byte[] buffer )
		{
			return System.BitConverter.ToUInt64( buffer, 0 );
		}

		public static float ToF32( byte[] buffer )
		{
			return System.BitConverter.ToSingle( buffer, 0 );
		}

		public static double ToF64( byte[] buffer )
		{
			return System.BitConverter.ToDouble( buffer, 0 );
		}

		private static T Error<T>()
		{
			throw new NotSupportedException();
		}

		public static T To<T>( byte[] buffer )
		{
			return typeof( T ) == typeof( bool ) ? ( T )( object )ToBoolean( buffer ) :
				typeof( T ) == typeof( sbyte ) ? ( T )( object )ToS8( buffer ) : 
				typeof( T ) == typeof( byte ) ? ( T )( object )ToU8( buffer ) :
				typeof( T ) == typeof( short ) ? ( T )( object )ToS16( buffer ) :
				typeof( T ) == typeof( ushort ) ? ( T )( object )ToU16( buffer ) :
				typeof( T ) == typeof( int ) ? ( T )( object )ToS32( buffer ) :
				typeof( T ) == typeof( uint ) ? ( T )( object )ToU32( buffer ) :
				typeof( T ) == typeof( long ) ? ( T )( object )ToS64( buffer ) :
				typeof( T ) == typeof( ulong ) ? ( T )( object )ToU64( buffer ) :
				typeof( T ) == typeof( float ) ? ( T )( object )ToF32( buffer ) :
				typeof( T ) == typeof( double ) ? ( T )( object )ToF64( buffer ) :
				Error<T>();
		}
	}
}
