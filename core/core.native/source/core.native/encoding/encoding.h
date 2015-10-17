//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_ENCODING_ENCODING_INCLUDED
#define USELESS_CORE_NATIVE_ENCODING_ENCODING_INCLUDED

#include "core.native/string.h"
#include "definitions.h"

namespace useless
{
	class CORE_ENCODING_DECL encoding
	{
	private:
		template<size_t _Size>
		class unicode_helper
		{
		public:
			static char* unicode_name()
			{
				return "utf-16le";
			}

			static char* unicode_big_endian_name()
			{
				return "utf-16be";
			}
		};

		template<>
		class unicode_helper<4>
		{
		public:
			static char* unicode_name()
			{
				return "utf-32le";
			}

			static char* unicode_big_endian_name()
			{
				return "utf-32be";
			}
		};

	public:
		static const encoding& get( const string_ansi& charset );

		static const encoding& default();
		static const encoding& ascii();
		static const encoding& utf8();
		static const encoding& utf16();
		static const encoding& utf16_big_endian();
		static const encoding& utf32();
		static const encoding& utf32_big_endian();

		static const encoding& unicode()
		{
			return encoding::get( unicode_helper<sizeof( wchar_t )>::unicode_name() );
		}

		static const encoding& unicode_big_endian()
		{
			return encoding::get( unicode_helper<sizeof( wchar_t )>::unicode_big_endian_name() );
		}

		// mbs -> mbs
		static void convert( const encoding& src, const encoding& dst, const string_ansi& input, string_ansi& output );
		static string_ansi convert( const encoding& src, const encoding& dst, const string_ansi& input );

		// mbs -> wcs
		static void convert( const encoding& src, const string_ansi& input, string_wide& output );
		static string_wide convert( const encoding& src, const string_ansi& input );

		// wcs -> mbs
		static void convert( const encoding& dst, const string_wide& input, string_ansi& output );
		static string_ansi convert( const encoding& dst, const string_wide& input );

	private:
		encoding( const string_ansi& charset );
		encoding( const encoding& other );
		const encoding& operator=( const encoding& other );

	public:
		bool operator == ( const encoding& other ) const;
		bool operator != ( const encoding& other ) const;

		void from_wide( const string_wide& input, string_ansi& output ) const;
		string_ansi from_wide( const string_wide& input ) const;

		void to_wide( const string_ansi& input, string_wide& output ) const;
		string_wide to_wide( const string_ansi& input ) const;

		const char* name() const;

	private:
		// encoding 객체는 DLL에서 생성과 삭제를 모두 담당하며, m_loc는 내부에서만 사용하므로 C4251은 무시한다
#if defined( _MSC_VER )
#pragma warning( disable : 4251 )
#endif
		std::locale m_loc;
#if defined( _MSC_VER )
#pragma warning( default : 4251 )
#endif
	};
}

#endif USELESS_CORE_NATIVE_ENCODING_ENCODING_INCLUDED