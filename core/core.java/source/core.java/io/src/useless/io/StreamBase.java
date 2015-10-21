/*
 * Copyright (c) 2015. SeongJun Park.
 *
 * Distributed under the MIT License.
 */

package useless.io;

public interface StreamBase
{
	public int getSize();
	public boolean canRead();
	public boolean canWrite();
	public byte[] getBuffer();
	public int read( byte[] buffer, int count );
	public int write( byte[] buffer, int count );
	public int setPos( SeekDir way, int off );
	public int getPos();
}
