/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.type_traits;

public class IsFloat
{
	public static <T> boolean invoke( Class<T> type )
	{
		return ( type == Float.class || type == Double.class || type == float.class || type == double.class );
	}
}
