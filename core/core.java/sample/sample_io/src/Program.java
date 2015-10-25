/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

import useless.io.*;
import useless.io.Serializable;

import java.io.*;

public class Program
{
	public static void main( String[] args ) throws Exception
	{
		try
		{
			boolean test = false;
			if( Integer.class == Integer.TYPE )
			{
				test = true;
			}
			DynamicStream ds = new DynamicStream( 100 );

			BinaryWriter bw = new BinaryWriter( ds );
			//int[] arrayVal = new int[ 3 ];
			//arrayVal[ 0 ] = 12;
			//arrayVal[ 1 ] = 22;
			//arrayVal[ 2 ] = 32;
			//bw.write( int[].class, arrayVal );

			TestValue[] arrayVal = new TestValue[ 3 ];
			arrayVal[ 0 ] = new TestValue( 33 );
			arrayVal[ 1 ] = new TestValue( 44 );
			arrayVal[ 2 ] = new TestValue( 55 );
			bw.write( TestValue[].class, arrayVal );

			//bw.write( Integer.class, 10 );

			TestValue testValue = new TestValue( 123 );
			//bw.write( TestValue.class, testValue );

			ds.setPos( SeekDir.beg, 0 );
			BinaryReader br = new BinaryReader( ds );
			//int[] arrayVal2 = br.read( int[].class );
			TestValue[] arrayVal2 = br.read( TestValue[].class );
			//int intValue = br.read( Integer.class );

			//TestValue testValue2 = br.read( TestValue.class );

			System.out.println( arrayVal2 );
			//System.out.println( intValue );

		}
		catch( Exception e )
		{
			e.printStackTrace();
		}
	}
}

