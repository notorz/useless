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
				else if( typeof( T ) == typeof( String ) )
				{
					uint count = br.ReadU32();
					byte[] buffer = new byte[ count ];
					br.Read( buffer, ( int )count );
					Encoding.UTF8.GetString( buffer );
					String temp = val as String;
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
