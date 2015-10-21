/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

import useless.io.*;
import useless.io.Serializable;

import java.io.*;

class TestValue implements Serializable
{
	private int test1 = 0;

	public void Serialize( BinaryReader br )
	{
		test1 = br.readS32();
	}
}

public class Program
{
	public static void main( String[] args ) throws Exception
	{
		try
		{
			DataInputStream in = new DataInputStream(new FileInputStream(""));

			BinaryReader br = new BinaryReader();
			TestValue testval = br.read( TestValue.class );

			System.out.println( testval );

		}
		catch( Exception e )
		{
			e.printStackTrace();
		}
	}
}

