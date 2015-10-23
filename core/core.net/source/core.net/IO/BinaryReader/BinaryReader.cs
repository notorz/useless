//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

using System;
using System.Text;
using System.Runtime.InteropServices;
using System.Collections;
using System.Reflection;

namespace Useless.IO
{
	public class BinaryReader : IDisposable
	{
		private static byte[] m_internalBuffer = new byte[ 8 ];

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
		
		public void Read( Type type, ref object val )
		{
			if( TypeTraits.IsArithmetic.Invoke( type ) )
			{
				Read( m_internalBuffer, Marshal.SizeOf( type ) );
				val = Utility.BitConverter.To( type, m_internalBuffer );
			}
			else if( TypeTraits.IsString.Invoke( type ) )
			{
				uint countUnsigned = ReadU32();
				if( countUnsigned > int.MaxValue )
				{
					throw new NotSupportedException( "count" );
				}

				int count = ( int )countUnsigned;
				byte[] buffer = new byte[ count ];
				Read( buffer, count );
				val = Encoding.UTF8.GetString( buffer );
			}
			else if( val is IDictionary )
			{
				uint countUnsigned = ReadU32();
				if( countUnsigned > int.MaxValue )
				{
					throw new NotSupportedException( "count" );
				}

				Type key_type = val.GetType().GetTypeInfo().GenericTypeArguments[ 0 ];
				Type value_type = val.GetType().GetTypeInfo().GenericTypeArguments[ 1 ];
				IDictionary dictionaryVal = ( IDictionary )val;
				int count = ( int )countUnsigned;
				for( int i = 0; i < count; ++i )
				{
					object key_temp = null;
					Read( key_type, ref key_temp );

					object value_temp = null;
					Read( value_type, ref value_temp );
					dictionaryVal.Add( key_temp, value_temp );
                }
            }
			else if( val is IList )
			{
				uint countUnsigned = ReadU32();
				if( countUnsigned > int.MaxValue )
				{
					throw new NotSupportedException( "count" );
				}

				Type element_type = val.GetType().GetTypeInfo().GenericTypeArguments[ 0 ];
				IList listVal = ( IList )val;
				int count = ( int )countUnsigned;
				for( int i = 0; i < count; ++i )
				{
					object temp = null;
					Read( element_type, ref temp );
					listVal.Add( temp );
				}
			}
			else if( val is IEnumerable || val is ICollection )
			{
				uint countUnsigned = ReadU32();
				if( countUnsigned > int.MaxValue )
				{
					throw new NotSupportedException( "count" );
				}

				Type element_type = val.GetType().GetTypeInfo().GenericTypeArguments[ 0 ];
				int count = ( int )countUnsigned;

				MethodInfo method = type.GetMethod( "Add", new Type[] { element_type } );
				if( method == null )
				{
					method = type.GetMethod( "AddLast", new Type[] { element_type } );
                }
				if( method == null )
				{
					method = type.GetMethod( "Enqueue", new Type[] { element_type } );
				}
				if( method == null )
				{
					method = type.GetMethod( "Push", new Type[] { element_type } );
				}

				if( method != null )
				{
					for( int i = 0; i < count; ++i )
					{
						object temp = null;
						Read( element_type, ref temp );
						method.Invoke( val, new object[] { temp } );
					}
				}
            }
			
			else
			{
				ISerializable serializable = val as ISerializable;
				if( serializable == null )
				{
					throw new ObjectSerializeException();
				}

				BinaryReader refThis = this;
				serializable.Deserialize( ref refThis );
			}
		}

		public void Read<T>( ref T val )
		{
			object temp = val;
			Read( typeof( T ), ref temp );
			val = ( T )temp;
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
