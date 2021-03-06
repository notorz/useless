/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.type_traits;

public class IsArithmetic
{
	public static <T> boolean invoke( Class<T> type )
	{
		return ( IsFloat.invoke( type ) || IsIntegral.invoke( type ) );
	}
}
