//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

using System.Collections.Generic;

namespace Useless.IO
{
	public class ListSerialize<T> : ISerializable
	{
		private List<T> m_list;
		public ListSerialize( ref List<T> list )
		{
			m_list = list;
		}

		public void Serialize( ref BinaryReader br )
		{
			uint count = br.ReadU32();
			for( int i = 0; i < count; ++i )
			{
				T temp = default( T );
				br.Read<T>( ref temp );
				m_list.Add( temp );
			}
		}
	}
}
