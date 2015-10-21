/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.type_traits;

public class IsBoolean
{
	public static <T> boolean invoke( Class<T> classT )
	{
		return ( classT == Boolean.class );
	}
}
