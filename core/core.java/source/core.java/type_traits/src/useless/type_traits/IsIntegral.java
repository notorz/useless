/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.type_traits;

public class IsIntegral
{
	public static <T> boolean invoke( Class<T> classT )
	{
		return (
				classT == Boolean.class ||
				classT == Byte.class ||
				classT == Short.class ||
				classT == Integer.class ||
				classT == Long.class );
	}
}
