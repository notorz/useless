/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.type_traits;

public class IsIntegral
{
	public static <T> boolean invoke( Class<T> type )
	{
		return (
				type == Boolean.class ||
				type == Byte.class ||
				type == Short.class ||
				type == Integer.class ||
				type == Long.class ||
				type == boolean.class ||
				type == byte.class ||
				type == short.class ||
				type == int.class ||
				type == long.class );
	}
}
