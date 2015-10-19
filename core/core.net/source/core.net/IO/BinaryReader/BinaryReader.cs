//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

using System;

namespace Useless.IO
{
	public partial class BinaryReader : IDisposable
	{
		private IStream m_stream = null;
		private bool m_mustBeDispose = false;

		public BinaryReader()
		{
			
        }

		public BinaryReader( IStream stream )
		{
			if( stream == null || !stream.CanRead )
			{
				throw new ArgumentException( "stream" );
			}

			m_stream = stream;
		}

		public BinaryReader( byte[] address, int size )
		{
			m_stream = new MemoryStream( address, size );
			m_mustBeDispose = true;
        }

		public BinaryReader( String path, System.IO.FileMode openmode )
		{
			m_stream = new FileStream( path, openmode );
			m_mustBeDispose = true;
		}

		public void Dispose()
		{
			if( m_stream != null && m_mustBeDispose )
			{
				m_stream.Dispose();
			}

			m_stream = null;
		}

		public void SetStream( IStream stream )
		{
			if( stream == null || !stream.CanRead )
			{
				throw new ArgumentException( "stream" );
			}

			if( m_stream != null && m_mustBeDispose )
			{
				m_stream.Dispose();
			}

			m_stream = stream;
			m_mustBeDispose = false;
        }

		public IStream GetStream()
		{
			return m_stream;
		}

		public void Read( byte[] buffer, int count )
		{
			if( m_stream == null  )
			{
				throw new ObjectDisposedException( "stream" );
			}

			m_stream.Read( buffer, count );
		}
		
		public void Read<T>( ref T val )
		{
			BinaryReader refThis = this;
            ReadHelper<T>.Invoke( ref refThis, ref val );
		}

		public bool ReadBoolean()
		{
			bool val = false;
			Read<bool>( ref val );
			return val;
		}

		public sbyte ReadS8()
		{
			sbyte val = 0;
			Read<sbyte>( ref val );
			return val;
		}

		public byte ReadU8()
		{
			byte val = 0;
			Read<byte>( ref val );
			return val;
		}
		
		public short ReadS16()
		{
			short val = 0;
			Read<short>( ref val );
			return val;
		}

		public ushort ReadU16()
		{
			ushort val = 0;
			Read<ushort>( ref val );
			return val;
		}
		
		public int ReadS32()
		{
			int val = 0;
			Read<int>( ref val );
			return val;
		}

		public uint ReadU32()
		{
			uint val = 0;
			Read<uint>( ref val );
			return val;
		}

		public long ReadS64()
		{
			long val = 0;
			Read<long>( ref val );
			return val;
		}

		public ulong ReadU64()
		{
			ulong val = 0;
			Read<ulong>( ref val );
			return val;
		}

		public float ReadF32()
		{
			float val = 0;
			Read<float>( ref val );
			return val;
		}

		public double ReadF64()
		{
			double val = 0;
			Read<double>( ref val );
			return val;
		}

		public String ReadString()
		{
			String val = null;
			Read<String>( ref val );
			return val;
		}
	}
}
