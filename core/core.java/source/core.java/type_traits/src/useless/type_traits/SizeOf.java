/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.type_traits;

public class SizeOf
{
	public static <T> int invoke( Class<T> type )
	{
		if( type == Boolean.class || type == boolean.class )
		{
			return 1;
		}
		else if( type == Character.class || type == char.class )
		{
			return 2;
		}
		else if( type == Byte.class || type == byte.class )
		{
			return 1;
		}
		else if( type == Short.class || type == short.class )
		{
			return 2;
		}
		else if( type == Integer.class || type == int.class )
		{
			return 4;
		}
		else if( type == Long.class || type == long.class )
		{
			return 8;
		}
		else if( type == Float.class || type == float.class )
		{
			return 4;
		}
		else if( type == Double.class || type == double.class )
		{
			return 8;
		}

		throw new UnsupportedOperationException();
	}

}
