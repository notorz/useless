//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_FILE_STREAM_INCLUDED
#define USELESS_CORE_NATIVE_IO_FILE_STREAM_INCLUDED

#include "core.native/string.h"
#include "core.native/io/useless_api.h"
#include "streambase.h"

namespace useless
{
	namespace openmode
	{
		enum type
		{
			in = 0x01,
			out = 0x02,
			ate = 0x04,
			app = 0x08,
			trunc = 0x10,
			binary = 0x20,
			nocreate = 0x40,
			noreplace = 0x80
		};
	}

	namespace prot
	{
		enum type
		{
			
		};
	}

	class Core_API file_stream : public streambase
	{
	public:
		file_stream( const char* filename, int openmode );
		file_stream( const string_ansi& filename, int openmode );
		file_stream( const wchar_t* filename, int openmode );
		file_stream( const string_wide& filename, int openmode );
		virtual ~file_stream();

		bool open( const char* filename, int openmode );
		bool open( const string_ansi& filename, int openmode );
		bool open( const wchar_t* filename, int openmode );
		bool open( const string_wide& filename, int openmode );
		void close();

		bool is_open() const;

		virtual size_t size() const;
		virtual bool can_be_read() const;
		virtual bool can_be_write() const;
		virtual const void* raw_data() const;
		virtual size_t read( void* buffer, size_t count );
		virtual size_t write( const void* buffer, size_t count );
		virtual streamoff setpos( seekdir::type way, streamoff off );
		virtual streamoff getpos() const;

		int flush();

	protected:
		void init( FILE*file, bool open );

		bool xfsopen( FILE*& file, const char* filename, int mode );
		bool xfsopen( FILE*& file, const wchar_t* filename, int mode );

		template<typename CharT>
		bool open( const CharT* filename, int openmode )
		{
			static const int valid[] =
			{
				openmode::in,
				openmode::out,
				openmode::out | openmode::trunc,
				openmode::out | openmode::app,
				openmode::in | openmode::binary,
				openmode::out | openmode::binary,
				openmode::out | openmode::trunc | openmode::binary,
				openmode::out | openmode::app | openmode::binary,
				openmode::in | openmode::out,
				openmode::in | openmode::out | openmode::trunc,
				openmode::in | openmode::out | openmode::app,
				openmode::in | openmode::out | openmode::binary,
				openmode::in | openmode::out | openmode::trunc | openmode::binary,
				openmode::in | openmode::out | openmode::app | openmode::binary,
				0
			};

			if( m_file != nullptr )
			{
				return false;
			}

			int atendflag = openmode & openmode::ate;
			int norepflag = openmode & openmode::noreplace;

			if( openmode & openmode::nocreate )
			{
				openmode |= openmode::in;
			}

			if( openmode & openmode::app )
			{
				openmode |= openmode::out;
			}

			openmode &= ~( openmode::ate | openmode::nocreate | openmode::noreplace );

			int n = 0;
			while( valid[ n ] != 0 && valid[ n ] != openmode )
			{
				++n;
			}

			if( valid[ n ] == 0 )
			{
				return false;
			}

			FILE* file = nullptr;
			if( norepflag && 
				( openmode & ( openmode::out | openmode::app ) ) && 
				xfsopen( file, filename, 0 ) )
			{
				::fclose( file );
				return false;
			}

			if( file != nullptr && ::fclose( file ) != 0 )
			{
				return false;
			}

			if( !xfsopen( file, filename, n ) )
			{
				return false;
			}

			if( atendflag )
			{
				if( ::fseek( file, 0, SEEK_END ) != 0 )
				{
					::fclose( file );
					return false;
				}
			}

			init( file, true );

			if( openmode & openmode::in )
			{
				m_can_be_read = true;
			}

			if( openmode & openmode::out )
			{
				m_can_be_write = true;
			}

			return true;
		}

	private:
		FILE* m_file;
		bool m_must_be_closed;
		bool m_can_be_read;
		bool m_can_be_write;
	};
}

#endif USELESS_CORE_NATIVE_IO_FILE_STREAM_INCLUDED