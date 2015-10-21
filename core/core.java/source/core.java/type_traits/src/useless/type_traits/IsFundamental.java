/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.type_traits;

public class IsFundamental
{
	public static <T> boolean invoke( Class<T> classT )
	{
		return ( IsArithmetic.invoke( classT ) || IsChar.invoke( classT ) || IsVoid.invoke( classT ) );
	}
}
