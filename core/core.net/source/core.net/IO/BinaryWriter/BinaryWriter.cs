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
	public class BinaryWriter : IDisposable
	{
		private IStream m_stream = null;
		private bool m_mustBeDispose = false;

		public BinaryWriter()
		{
		}

		public BinaryWriter( IStream stream )
		{
			if( stream == null || !stream.CanWrite )
			{
				throw new ArgumentException( "stream" );
			}

			m_stream = stream;
		}

		public BinaryWriter( int size, bool growable = true )
		{
			if( growable )
			{
				m_stream = new DynamicStream( size );
			}
			else
			{
				m_stream = new FixedStream( size );
			}

			m_mustBeDispose = true;
		}

		public BinaryWriter( byte[] address, int size )
		{
			m_stream = new MemoryStream( address, size );
			m_mustBeDispose = true;
		}
		
		public BinaryWriter( String path, System.IO.FileMode openmode )
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
			if( stream == null || !stream.CanWrite )
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

		public void Write( byte[] buffer, int count )
		{
			if( m_stream == null )
			{
				throw new ObjectDisposedException( "stream" );
			}

			m_stream.Write( buffer, count );
		}

		public void Write( Type type, object val )
		{
			if( TypeTraits.IsArithmetic.Invoke( type ) )
			{
				Write( Utility.BitConverter.GetBytes( type, val ), Marshal.SizeOf( type ) );
			}
			else if( TypeTraits.IsString.Invoke( type ) )
			{
				String stringVal = ( String )val;
				int count = Encoding.UTF8.GetByteCount( stringVal );
                WriteU32( ( uint )count );
				Write( Encoding.UTF8.GetBytes( stringVal ), count );
			}
			else if( val is IDictionary )
			{
				Type key_type = val.GetType().GetTypeInfo().GenericTypeArguments[ 0 ];
				Type value_type = val.GetType().GetTypeInfo().GenericTypeArguments[ 1 ];

				IDictionary dictionaryVal = ( IDictionary )val;
				WriteU32( ( uint )dictionaryVal.Count );
				IDictionaryEnumerator enumerator = dictionaryVal.GetEnumerator();
				while( enumerator.MoveNext() )
				{
					Write( key_type, enumerator.Key );
					Write( value_type, enumerator.Value );
				}
            }
			else if( val is ICollection )
			{
				Type element_type = val.GetType().GetTypeInfo().GenericTypeArguments[ 0 ];

				ICollection collectionVal = ( ICollection )val;
				WriteU32( ( uint )collectionVal.Count );
				foreach( object data in collectionVal )
				{
					Write( element_type, data );
				}
			}
			else if( val is IEnumerable )
			{
				Type element_type = val.GetType().GetTypeInfo().GenericTypeArguments[ 0 ];

				IEnumerable enumerableVal = ( IEnumerable )val;
				int count = 0;
				foreach( object data in enumerableVal )
				{
					++count;
				}
				WriteU32( ( uint )count );

				foreach( object data in enumerableVal )
				{
					Write( element_type, data );
				}
			}
			else
			{
				ISerializable serializable = val as ISerializable;
				if( serializable == null )
				{
					throw new ObjectSerializeException();
				}

				BinaryWriter refThis = this;
				serializable.Serialize( ref refThis );
			}
		}

		public void Write<T>( T val )
		{
			object temp = val;
			Write( typeof( T ), temp );
		}

		public void WriteBoolean( bool val )
		{
			Write( val );
		}

		public void WriteS8( sbyte val )
		{
			Write( val );
		}

		public void WriteU8( byte val )
		{
			Write( val );
		}

		public void WriteS16( short val )
		{
			Write( val );
		}

		public void WriteU16( ushort val )
		{
			Write( val );
		}

		public void WriteS32( int val )
		{
			Write( val );
		}

		public void WriteU32( uint val )
		{
			Write( val );
		}

		public void WriteS64( long val )
		{
			Write( val );
		}

		public void WriteU64( ulong val )
		{
			Write( val );
		}

		public void WriteF32( float val )
		{
			Write( val );
		}

		public void WriteF64( double val )
		{
			Write( val );
		}

		public void WriteString( String val )
		{
			Write( val );
		}
	}
}
