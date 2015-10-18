//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

namespace Useless.IO
{
	interface ISerializable
	{
        void Serialize( ref BinaryReader br );
		//void Deserialize( ref BinaryWriter bw );
	}
}
