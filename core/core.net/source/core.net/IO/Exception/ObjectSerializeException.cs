//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

using System;

namespace Useless.IO
{
	/// <summary>
	/// ISerializable을 상속받지 않은 오브젝트를 Serialize하려고 할 때 발생하는 예외입니다.
	/// </summary>
	public class ObjectSerializeException : Exception
	{
	}
}
