/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

import useless.io.*;
import useless.io.Serializable;
import java.util.*;
import java.io.*;
import java.lang.reflect.*;

public class Program
{
	public static void main( String[] args ) throws Exception
	{
		try
		{
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
			//bw.write( arrayVal );

			LinkedList<Short> listVal = new LinkedList<Short>();
			listVal.addLast( ( short )53 );
			listVal.addLast( ( short ) 63 );
			listVal.addLast( ( short ) 73 );
			//bw.write( listVal );
			//bw.write( "abc가나다" );

			HashMap<Byte, Short> mapVal = new HashMap<Byte, Short>();
			mapVal.put( ( byte )4, ( short )97 );
			mapVal.put( ( byte )9, ( short )74 );
			mapVal.put( ( byte )10, ( short )53 );
			//bw.write( mapVal );

			bw.write( 10 );

			TestValue testValue = new TestValue( 123 );
			//bw.write( TestValue.class, testValue );

			ds.setPos( SeekDir.beg, 0 );
			BinaryReader br = new BinaryReader( ds );
			//int[] arrayVal2 = br.read( int[].class );
			//TestValue[] arrayVal2 = br.read( TestValue[].class );
			int intValue = br.read( Integer.class );
			//LinkedList<Short> listVal2 = br.read( new Class<?>[] { LinkedList.class, short.class } );
			//HashMap<Byte, Short> mapVal2 = br.read( new Class<?>[] { HashMap.class, byte.class, short.class } );

			//TestValue testValue2 = br.read( TestValue.class );

			System.out.println( intValue );
			//System.out.println( listVal2 );
			//System.out.println( intValue );

		}
		catch( Exception e )
		{
			e.printStackTrace();
		}
	}
}

