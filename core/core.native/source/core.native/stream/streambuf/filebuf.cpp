//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#include "filebuf.h"

namespace useless
{
	filebuf::filebuf( const char* filename, int openmode, int prot )
		: m_file( NULL )
		, m_must_be_closed( false )
		, m_can_be_read( false )
		, m_can_be_write( false )
	{
		if( !open<char>( filename, openmode, prot ) )
		{
			init( NULL, false );
		}
	}

	filebuf::filebuf( const string_ansi& filename, int openmode, int prot )
		: m_file( NULL )
		, m_must_be_closed( false )
		, m_can_be_read( false )
		, m_can_be_write( false )
	{
		if( !open<char>( filename.buffer(), openmode, prot ) )
		{
			init( NULL, false );
		}
	}

	filebuf::filebuf( const wchar_t* filename, int openmode, int prot )
		: m_file( NULL )
		, m_must_be_closed( false )
		, m_can_be_read( false )
		, m_can_be_write( false )
	{
		if( !open<wchar_t>( filename, openmode, prot ) )
		{
			init( NULL, false );
		}
	}

	filebuf::filebuf( const string_wide& filename, int openmode, int prot )
		: m_file( NULL )
		, m_must_be_closed( false )
		, m_can_be_read( false )
		, m_can_be_write( false )
	{
		if( !open<wchar_t>( filename.buffer(), openmode, prot ) )
		{
			init( NULL, false );
		}
	}

	filebuf::~filebuf()
	{
		if( m_must_be_closed )
		{
			close();
		}
	}

	bool filebuf::open( const char* filename, int openmode, int prot )
	{
		return open<char>( filename, openmode, prot );
	}

	bool filebuf::open( const string_ansi& filename, int openmode, int prot )
	{
		return open<char>( filename.buffer(), openmode, prot );
	}

	bool filebuf::open( const wchar_t* filename, int openmode, int prot )
	{
		return open<wchar_t>( filename, openmode, prot );
	}

	bool filebuf::open( const string_wide& filename, int openmode, int prot )
	{
		return open<wchar_t>( filename.buffer(), openmode, prot );
	}

	void filebuf::close()
	{
		if( m_file != NULL )
		{
			if( can_be_write() )
			{
				flush();
			}

			::fclose( m_file );
		}

		init( NULL, false );
	}

	bool filebuf::is_open() const
	{
		return ( m_file != NULL );
	}

	size_t filebuf::size() const
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

	bool filebuf::can_be_read() const
	{
		return m_can_be_read;
	}

	bool filebuf::can_be_write() const
	{
		return m_can_be_write;
	}

	const void* filebuf::raw_data() const
	{
		return m_file;
	}

	size_t filebuf::read( void* buffer, size_t count )
	{
		if( !can_be_read() )
		{
			return 0;
		}

		return ::fread( buffer, 1, count, m_file );
	}

	size_t filebuf::write( const void* buffer, size_t count )
	{
		if( !can_be_write() )
		{
			return 0;
		}

		return ::fwrite( buffer, 1, count, m_file );
	}

	streamoff filebuf::setpos( seekdir::type way, streamoff off )
	{
		if( m_file == NULL )
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

	streamoff filebuf::getpos() const
	{
		if( m_file == NULL )
		{
			return -1;
		}

		fpos_t fpos;
		::fgetpos( m_file, &fpos );
		return static_cast< streamoff >( fpos );
	}

	int filebuf::flush()
	{
		if( m_file == NULL )
		{
			return 0;
		}

		return ::fflush( m_file );
	}

	void filebuf::init( FILE*file, bool open )
	{
		m_must_be_closed = !open;
		m_file = file;
	}

	FILE* filebuf::xfsopen( const char* filename, int mode, int prot )
	{
		static const char* const mods[] =
		{
			"r", "w", "w", "a",
			"rb", "wb", "wb", "ab",
			"r+", "w+", "a+",
			"r+b", "w+b", "a+b",
			0
		};

		return ::_fsopen( filename, mods[ mode ], prot );
	}

	FILE* filebuf::xfsopen( const wchar_t* filename, int mode, int prot )
	{
		static const wchar_t* const mods[] =
		{
			L"r", L"w", L"w", L"a",
			L"rb", L"wb", L"wb", L"ab",
			L"r+", L"w+", L"a+",
			L"r+b", L"w+b", L"a+b",
			0
		};

		return ::_wfsopen( filename, mods[ mode ], prot );
	}
}