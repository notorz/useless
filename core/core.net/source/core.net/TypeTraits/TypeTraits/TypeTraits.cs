//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

namespace Useless.TypeTraits
{
	public class IsFloat<T>
	{
		public static bool value = (
			typeof( T ) == typeof( float ) ||
			typeof( T ) == typeof( double ) ) ?
			true : false;
	}

	public class IsIntegral<T>
	{
		public static bool value = (
			typeof( T ) == typeof( bool ) ||
			typeof( T ) == typeof( sbyte ) ||
			typeof( T ) == typeof( byte ) ||
			typeof( T ) == typeof( short ) ||
			typeof( T ) == typeof( ushort ) ||
			typeof( T ) == typeof( int ) ||
			typeof( T ) == typeof( uint ) ||
			typeof( T ) == typeof( long ) ||
			typeof( T ) == typeof( ulong ) ) ?
			true : false;
	}

	public class IsChar<T>
	{
		public static bool value = ( typeof( T ) == typeof( char ) ) ? true : false;
	}

	public class IsBoolean<T>
	{
		public static bool value = ( typeof( T ) == typeof( bool ) ) ? true : false;
	}

	public class IsDecimal<T>
	{
		public static bool value = ( typeof( T ) == typeof( decimal ) ) ? true : false;
	}

	public class IsVoid<T>
	{
		public static bool value = ( typeof( T ) == typeof( void ) ) ? true : false;
	}

	public class IsArithmetic<T>
	{
		public static bool value = ( IsFloat<T>.value || IsIntegral<T>.value ) ? true : false;
	}

	public class IsFundamental<T>
	{
		public static bool value = (
			IsArithmetic<T>.value ||
			IsChar<T>.value ||
			IsDecimal<T>.value ||
			IsVoid<T>.value ) ? 
			true : false;
	}
}
