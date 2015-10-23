//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

namespace Useless.IO
{
	interface ISerializable
	{
		void Serialize( ref BinaryWriter bw );
		void Deserialize( ref BinaryReader br );
	}
}
