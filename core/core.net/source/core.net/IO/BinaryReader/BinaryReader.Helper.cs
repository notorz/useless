//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Useless.IO
{
    public partial class BinaryReader
	{
		class ReadHelper<T>
		{
			private static byte[] m_internalBuffer = new byte[ 8 ];
			
            public static void Invoke( ref BinaryReader br, ref T val )
			{
				if( TypeTraits.IsFundamental<T>.value )
				{
                    br.Read( m_internalBuffer, Marshal.SizeOf<T>() );
					val = Utility.BitConverter.To<T>( m_internalBuffer );
				}
				else if( TypeTraits.IsString<T>.value )
				{
					uint countUnsigned = br.ReadU32();
					if( countUnsigned > int.MaxValue )
					{
						throw new NotSupportedException( "count" );
					}

					int count = ( int )countUnsigned;
                    byte[] buffer = new byte[ count ];
					br.Read( buffer, count );
					val = ( T )( object )( Encoding.UTF8.GetString( buffer ) );
				}
				else
				{
					ISerializable serializable = val as ISerializable;
					if( serializable == null )
					{
						throw new ObjectSerializeException();
					}

					serializable.Serialize( ref br );
                }
            }
		}
	}
}
