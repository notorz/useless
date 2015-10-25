/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.type_traits;

public class IsString
{
	public static <T> boolean invoke( Class<T> type )
	{
		return ( type == String.class );
	}
}
