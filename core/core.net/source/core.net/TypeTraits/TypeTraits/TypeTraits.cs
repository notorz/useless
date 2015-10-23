//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

using System;

namespace Useless.TypeTraits
{
	public class IsFloat
	{
		public static bool Invoke( Type type )
		{
			return (
				type == typeof( float ) ||
				type == typeof( double ) );
		}
	}

	public class IsIntegral
	{
		public static bool Invoke( Type type )
		{
			return (
				type == typeof( bool ) ||
				type == typeof( sbyte ) ||
				type == typeof( byte ) ||
				type == typeof( short ) ||
				type == typeof( ushort ) ||
				type == typeof( int ) ||
				type == typeof( uint ) ||
				type == typeof( long ) ||
				type == typeof( ulong ) );
		}
	}

	public class IsChar
	{
		public static bool Invoke( Type type )
		{
			return ( type == typeof( char ) );
		}
	}

	public class IsBoolean
	{
		public static bool Invoke( Type type )
		{
			return ( type == typeof( bool ) );
		}
	}

	public class IsDecimal
	{
		public static bool Invoke( Type type )
		{
			return ( type == typeof( decimal ) );
		}
	}

	public class IsVoid
	{
		public static bool Invoke( Type type )
		{
			return ( type == typeof( void ) );
		}
	}

	public class IsArithmetic
	{
		public static bool Invoke( Type type )
		{
			return ( IsFloat.Invoke( type ) || IsIntegral.Invoke( type ) );
		}
	}

	public class IsFundamental
	{
		public static bool Invoke( Type type )
		{
			return (
				IsArithmetic.Invoke( type ) ||
				IsChar.Invoke( type ) ||
				IsDecimal.Invoke( type ) ||
				IsVoid.Invoke( type ) );
		}
	}

	public class IsString
	{
		public static bool Invoke( Type type )
		{
			return ( type == typeof( string ) );
		}
	}

	public class IsFloat<T>
	{
		public static bool value = IsFloat.Invoke( typeof( T ) );
	}

	public class IsIntegral<T>
	{
		public static bool value = IsIntegral.Invoke( typeof( T ) );
	}

	public class IsChar<T>
	{
		public static bool value = IsChar.Invoke( typeof( T ) );
	}

	public class IsBoolean<T>
	{
		public static bool value = IsBoolean.Invoke( typeof( T ) );
	}

	public class IsDecimal<T>
	{
		public static bool value = IsDecimal.Invoke( typeof( T ) );
	}

	public class IsVoid<T>
	{
		public static bool value = IsVoid.Invoke( typeof( T ) );
	}

	public class IsArithmetic<T>
	{
		public static bool value = IsArithmetic.Invoke( typeof( T ) );
	}

	public class IsFundamental<T>
	{
		public static bool value = IsFundamental.Invoke( typeof( T ) );
	}

	public class IsString<T>
	{
		public static bool value = IsString.Invoke( typeof( T ) );
	}
}
