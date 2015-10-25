/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.io;

public interface Serializable
{
	public void serialize( BinaryWriter bw );
	public void deserialize( BinaryReader br );
}
