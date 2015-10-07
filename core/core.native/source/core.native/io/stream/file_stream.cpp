//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#include "file_stream.h"

namespace useless
{
	file_stream::file_stream( const char* filename, int openmode )
		: m_file( nullptr )
		, m_must_be_closed( false )
		, m_can_be_read( false )
		, m_can_be_write( false )
	{
		if( !open<char>( filename, openmode ) )
		{
			init( nullptr, false );
		}
	}

	file_stream::file_stream( const string_ansi& filename, int openmode )
		: m_file( nullptr )
		, m_must_be_closed( false )
		, m_can_be_read( false )
		, m_can_be_write( false )
	{
		if( !open<char>( filename.buffer(), openmode ) )
		{
			init( nullptr, false );
		}
	}

	file_stream::file_stream( const wchar_t* filename, int openmode )
		: m_file( nullptr )
		, m_must_be_closed( false )
		, m_can_be_read( false )
		, m_can_be_write( false )
	{
		if( !open<wchar_t>( filename, openmode ) )
		{
			init( nullptr, false );
		}
	}

	file_stream::file_stream( const string_wide& filename, int openmode )
		: m_file( nullptr )
		, m_must_be_closed( false )
		, m_can_be_read( false )
		, m_can_be_write( false )
	{
		if( !open<wchar_t>( filename.buffer(), openmode ) )
		{
			init( nullptr, false );
		}
	}

	file_stream::~file_stream()
	{
		if( m_must_be_closed )
		{
			close();
		}
	}

	bool file_stream::open( const char* filename, int openmode )
	{
		return open<char>( filename, openmode );
	}

	bool file_stream::open( const string_ansi& filename, int openmode )
	{
		return open<char>( filename.buffer(), openmode );
	}

	bool file_stream::open( const wchar_t* filename, int openmode )
	{
		return open<wchar_t>( filename, openmode );
	}

	bool file_stream::open( const string_wide& filename, int openmode )
	{
		return open<wchar_t>( filename.buffer(), openmode );
	}

	void file_stream::close()
	{
		if( m_file != nullptr )
		{
			if( can_be_write() )
			{
				flush();
			}

			::fclose( m_file );
		}

		init( nullptr, false );
	}

	bool file_stream::is_open() const
	{
		return ( m_file != nullptr );
	}

	size_t file_stream::size() const
	{
		fpos_t pos;
		::fgetpos( m_file, &pos );
#ifdef _FSEEK_OFF
		_FSEEK_OFF( m_file, 0, SEEK_END );
#else
		::fseek( m_file, 0, SEEK_END );
#endif
		fpos_t size;
		::fgetpos( m_file, &size );
		::fsetpos( m_file, &pos );
		return static_cast< size_t >( size );
	}

	bool file_stream::can_be_read() const
	{
		return m_can_be_read;
	}

	bool file_stream::can_be_write() const
	{
		return m_can_be_write;
	}

	const void* file_stream::raw_data() const
	{
		return m_file;
	}

	size_t file_stream::read( void* buffer, size_t count )
	{
		if( !can_be_read() )
		{
			return 0;
		}

		return ::fread( buffer, 1, count, m_file );
	}

	size_t file_stream::write( const void* buffer, size_t count )
	{
		if( !can_be_write() )
		{
			return 0;
		}

		return ::fwrite( buffer, 1, count, m_file );
	}

	streamoff file_stream::setpos( seekdir::type way, streamoff off )
	{
		if( m_file == nullptr )
		{
			return -1;
		}

		if( ( off != 0 || way != seekdir::cur ) &&
#ifdef _FSEEK_OFF
			_FSEEK_OFF( m_file, off, way )
#else
			::fseek( m_file, off, way )
#endif
			!= 0 )
		{
			return -1;
		}

		fpos_t fpos;
		::fgetpos( m_file, &fpos );
		return static_cast< streamoff >( fpos );
	}

	streamoff file_stream::getpos() const
	{
		if( m_file == nullptr )
		{
			return -1;
		}

		fpos_t fpos;
		::fgetpos( m_file, &fpos );
		return static_cast< streamoff >( fpos );
	}

	int file_stream::flush()
	{
		if( m_file == nullptr )
		{
			return 0;
		}

		return ::fflush( m_file );
	}

	void file_stream::init( FILE*file, bool open )
	{
		m_must_be_closed = !open;
		m_file = file;
	}

	bool file_stream::xfsopen( FILE*& file, const char* filename, int mode )
	{
		static const char* const mods[] =
		{
			"r", "w", "w", "a",
			"rb", "wb", "wb", "ab",
			"r+", "w+", "a+",
			"r+b", "w+b", "a+b",
			0
		};

		return ( ::fopen_s( &file, filename, mods[ mode ] ) == 0 );
	}

	bool file_stream::xfsopen( FILE*& file, const wchar_t* filename, int mode )
	{
#ifdef _MSC_VER
		static const wchar_t* const mods[] =
		{
			L"r", L"w", L"w", L"a",
			L"rb", L"wb", L"wb", L"ab",
			L"r+", L"w+", L"a+",
			L"r+b", L"w+b", L"a+b",
			0
		};

		return ( ::_wfopen_s( &file, filename, mods[ mode ] ) == 0 );
#endif
	}
}