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
using System.IO;

namespace Useless.IO
{
	public class BinaryReader : IDisposable
	{
		class StreamProxy
		{
			private IStream m_uselessStream = null;
			private Stream m_stream = null;

			public StreamProxy( IStream stream )
			{
				m_uselessStream = stream;
			}

			public StreamProxy( Stream stream )
			{
				m_stream = stream;
			}

			public void Dispose()
			{
				if( m_uselessStream != null )
				{
					m_uselessStream.Dispose();
				}
				else if( m_stream !=  null )
				{
					m_stream.Dispose();
				}
			}

			public object GetStream()
			{
				if( m_uselessStream != null )
				{
					return m_uselessStream;
				}
				else
				{
					return m_stream;
				}
			}

			public int Seek( int offset, SeekDir way )
			{
				if( m_uselessStream != null )
				{
					return m_uselessStream.Seek( offset, way );
				}
				else
				{
					return ( int )m_stream.Seek( offset, ( SeekOrigin )way );
				}
			}

			public int GetPosition()
			{
				if( m_uselessStream != null )
				{

					return m_uselessStream.Position;
				}
				else
				{
					return ( int )m_stream.Position;
				}
			}

			public int Read( byte[] buffer, int count )
			{
				if( m_uselessStream != null )
				{
					return m_uselessStream.Read( buffer, count );
				}
				else
				{
					return m_stream.Read( buffer, 0, count );
				}
			}
		}

		private static byte[] m_internalBuffer = new byte[ 8 ];

		private StreamProxy m_stream = null;
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

			m_stream = new StreamProxy( stream );
		}

		public BinaryReader( Stream stream )
		{
			if( stream == null || !stream.CanRead )
			{
				throw new ArgumentException( "stream" );
			}

			m_stream = new StreamProxy( stream );
		}

		public BinaryReader( byte[] address, int size )
		{
			m_stream = new StreamProxy( new MemoryStream( address, size ) );
			m_mustBeDispose = true;
        }

		public BinaryReader( String path, System.IO.FileMode openmode )
		{
			m_stream = new StreamProxy( new FileStream( path, openmode ) );
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

			m_stream = new StreamProxy( stream );
			m_mustBeDispose = false;
        }

		public void SetStream( Stream stream )
		{
			if( stream == null || !stream.CanRead )
			{
				throw new ArgumentException( "stream" );
			}

			if( m_stream != null && m_mustBeDispose )
			{
				m_stream.Dispose();
			}

			m_stream = new StreamProxy( stream );
			m_mustBeDispose = false;
		}

		public object GetStream()
		{
			return m_stream.GetStream();
		}

		public int Seek( int offset, SeekDir way )
		{
			return m_stream.Seek( offset, way );
		}

		public int GetPosition()
		{
			return m_stream.GetPosition();
        }

		public void Read( byte[] buffer, int count )
		{
			if( m_stream == null )
			{
				throw new ObjectDisposedException( "stream" );
			}

			m_stream.Read( buffer, count );
		}
		
		public void Read( Type type, ref object val )
		{
			if( TypeTraits.IsArithmetic.Invoke( type ) || TypeTraits.IsChar.Invoke( type ) )
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
			else if( type.IsArray )
			{
				long count = ( long )ReadU32();
				Type element_type = type.GetElementType();

				Array arrayVal = ( Array )val;
				for( long i = 0; i < count; ++i )
				{
					object temp = null;
					Read( element_type, ref temp );
					arrayVal.SetValue( temp, i );
				}
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
				else
				{
					throw new NotSupportedException();
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
		
		public T Read<T>()
		{
			T val = default( T );
			Read<T>( ref val );
			return val;
		}

		public bool ReadBoolean()
		{
			return Read<bool>();
		}

		public sbyte ReadS8()
		{
			return Read<sbyte>();
		}

		public byte ReadU8()
		{
			return Read<byte>();
		}
		
		public short ReadS16()
		{
			return Read<short>();
		}

		public ushort ReadU16()
		{
			return Read<ushort>();
		}
		
		public int ReadS32()
		{
			return Read<int>();
		}

		public uint ReadU32()
		{
			return Read<uint>();
		}

		public long ReadS64()
		{
			return Read<long>();
		}

		public ulong ReadU64()
		{
			return Read<ulong>();
		}

		public float ReadF32()
		{
			return Read<float>();
		}

		public double ReadF64()
		{
			return Read<double>();
		}

		public String ReadString()
		{
			return Read<String>();
		}
	}
}
