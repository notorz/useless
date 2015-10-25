/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.type_traits;

public class IsFundamental
{
	public static <T> boolean invoke( Class<T> type )
	{
		return ( IsArithmetic.invoke( type ) || IsChar.invoke( type ) || IsVoid.invoke( type ) );
	}
}
