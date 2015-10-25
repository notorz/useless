/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

import useless.io.BinaryReader;
import useless.io.BinaryWriter;
import useless.io.Serializable;
import useless.io.exception.ReadFailedException;

public class TestValue implements Serializable
{
	private int test1 = 0;

	public TestValue()
	{
	}
	public TestValue( int value )
	{
		test1 = value;
	}

	public void serialize( BinaryWriter bw )
	{
		bw.writeS32( test1 );
	}
	public void deserialize( BinaryReader br )
	{
		test1 = br.readS32();
	}
}
