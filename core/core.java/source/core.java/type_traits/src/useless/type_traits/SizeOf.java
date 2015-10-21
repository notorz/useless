/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.type_traits;

public class SizeOf
{
	public static <T> int invoke( Class<T> classT )
	{
		if( classT == Boolean.class )
		{
			return 1;
		}
		else if( classT == Character.class )
		{
			return 2;
		}
		else if( classT == Byte.class )
		{
			return 1;
		}
		else if( classT == Short.class )
		{
			return 2;
		}
		else if( classT == Integer.class )
		{
			return 4;
		}
		else if( classT == Long.class )
		{
			return 8;
		}
		else if( classT == Float.class )
		{
			return 4;
		}
		else if( classT == Double.class )
		{
			return 8;
		}

		throw new UnsupportedOperationException();
	}

}
