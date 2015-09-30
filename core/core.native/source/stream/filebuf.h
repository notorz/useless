//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STREAM_FILEBUF_INCLUDED
#define USELESS_CORE_NATIVE_STREAM_FILEBUF_INCLUDED

#include <stdio.h>
#include "streambuf.h"
#include "../string.h"

namespace useless
{
	class filebuf : public streambuf
	{
	public:
		filebuf( const char* filename, std::ios_base::openmode mode, int prot = _SH_DENYNO )
			: m_can_be_read( false )
			, m_can_be_write( false )
		{
			if( !open<char>( filename, mode, prot ) )
			{
				init( NULL, false );
			}
		}

		filebuf( const std::string& filename, std::ios_base::openmode mode, int prot = _SH_DENYNO )
			: m_can_be_read( false )
			, m_can_be_write( false )
		{
			if( !open<char>( filename.c_str(), mode, prot ) )
			{
				init( NULL, false );
			}
		}

		filebuf( const string_ansi& filename, std::ios_base::openmode mode, int prot = _SH_DENYNO )
			: m_can_be_read( false )
			, m_can_be_write( false )
		{
			if( !open<char>( filename.buffer(), mode, prot ) )
			{
				init( NULL, false );
			}
		}

		filebuf( const wchar_t* filename, std::ios_base::openmode mode, int prot = _SH_DENYNO )
			: m_can_be_read( false )
			, m_can_be_write( false )
		{
			if( !open<wchar_t>( filename, mode, prot ) )
			{
				init( NULL, false );
			}
		}

		filebuf( const std::wstring& filename, std::ios_base::openmode mode, int prot = _SH_DENYNO )
			: m_can_be_read( false )
			, m_can_be_write( false )
		{
			if( !open<wchar_t>( filename.c_str(), mode, prot ) )
			{
				init( NULL, false );
			}
		}

		filebuf( const string_wide& filename, std::ios_base::openmode mode, int prot = _SH_DENYNO )
			: m_can_be_read( false )
			, m_can_be_write( false )
		{
			if( !open<wchar_t>( filename.buffer(), mode, prot ) )
			{
				init( NULL, false );
			}
		}

		virtual ~filebuf()
		{
			if( m_must_be_closed )
			{
				close();
			}
		}

		bool open( const char* filename, std::ios_base::openmode mode, int prot = _SH_DENYNO )
		{
			return open<char>( filename, mode, prot );
		}

		bool open( const std::string& filename, std::ios_base::openmode mode, int prot = _SH_DENYNO )
		{
			return open<char>( filename.c_str(), mode, prot );
		}

		bool open( const string_ansi& filename, std::ios_base::openmode mode, int prot = _SH_DENYNO )
		{
			return open<char>( filename.buffer(), mode, prot );
		}

		bool open( const wchar_t* filename, std::ios_base::openmode mode, int prot = _SH_DENYNO )
		{
			return open<wchar_t>( filename, mode, prot );
		}

		bool open( const std::wstring& filename, std::ios_base::openmode mode, int prot = _SH_DENYNO )
		{
			return open<wchar_t>( filename.c_str(), mode, prot );
		}

		bool open( const string_wide& filename, std::ios_base::openmode mode, int prot = _SH_DENYNO )
		{
			return open<wchar_t>( filename.buffer(), mode, prot );
		}

		void close()
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

		bool is_open() const
		{
			return ( m_file != NULL );
		}

		int flush()
		{
			if( m_file == NULL )
			{
				return 0;
			}

			return ::fflush( m_file );
		}

		virtual size_t size() const
		{
			fpos_t pos;
			::fgetpos( m_file, &pos );
			::fseek( m_file, 0, SEEK_END );
			size_t size = ::ftell( m_file );
			::fsetpos( m_file, &pos );
			return size;
		}

		virtual bool can_be_read() const
		{
			return m_can_be_read;
		}

		virtual bool can_be_write() const
		{
			return m_can_be_write;
		}

		virtual const void* raw_data() const
		{
			return m_file;
		}

		virtual int read( void* buffer, int count )
		{
			if( !can_be_read() )
			{
				return 0;
			}

			int read = static_cast<int>( ::fread( buffer, 1, static_cast<size_t>( count ), m_file ) );
			gbump( read );

			return read;
		}

		virtual int write( const void* buffer, int count )
		{
			if( !can_be_write() )
			{
				return 0;
			}

			int write = static_cast< int >( ::fwrite( buffer, 1, static_cast< size_t >( count ), m_file ) );
			pbump( write );

			return write;
		}

	protected:
		void init( FILE*file, bool open )
		{
			static traits_type::state_type state;
			m_state = state;

			m_must_be_closed = !open;

			if( file != NULL )
			{
				char** base = NULL;
				char** pointer = NULL;
				int* count = NULL;
				::_get_stream_buffer_pointers( file, &base, &pointer, &count );
				
				_Init( base, pointer, count, base, pointer, count );
			}
			else
			{
				_Init();
			}

			m_file = file;
		}

		FILE* xfsopen( const char* filename, int mode, int prot )
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

		FILE* xfsopen( const wchar_t* filename, int mode, int prot )
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

		template<typename CharT>
		bool open( const CharT* filename, std::ios_base::openmode mode, int prot = _SH_DENYNO )
		{
			static const int valid[] =
			{
				std::ios_base::in,
				std::ios_base::out,
				std::ios_base::out | std::ios_base::trunc,
				std::ios_base::out | std::ios_base::app,
				std::ios_base::in | std::ios_base::binary,
				std::ios_base::out | std::ios_base::binary,
				std::ios_base::out | std::ios_base::trunc | std::ios_base::binary,
				std::ios_base::out | std::ios_base::app | std::ios_base::binary,
				std::ios_base::in | std::ios_base::out,
				std::ios_base::in | std::ios_base::out | std::ios_base::trunc,
				std::ios_base::in | std::ios_base::out | std::ios_base::app,
				std::ios_base::in | std::ios_base::out | std::ios_base::binary,
				std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary,
				std::ios_base::in | std::ios_base::out | std::ios_base::app | std::ios_base::binary,
				0
			};

			if( m_file != NULL )
			{
				return false;
			}

			std::ios_base::openmode atendflag = mode & std::ios_base::ate;
			std::ios_base::openmode norepflag = mode & std::ios_base::_Noreplace;

			if( mode & std::ios_base::_Nocreate )
			{
				mode |= std::ios_base::in;
			}

			if( mode & std::ios_base::app )
			{
				mode |= std::ios_base::out;
			}

			mode &= ~( std::ios_base::ate | std::ios_base::_Nocreate | std::ios_base::_Noreplace );

			int n = 0;
			while( valid[ n ] != 0 && valid[ n ] != mode )
			{
				++n;
			}

			if( valid[ n ] == 0 )
			{
				return false;
			}

			FILE* file;
			if( norepflag && ( mode & ( std::ios_base::out | std::ios_base::app ) ) &&
				( file = xfsopen( filename, 0, prot ) ) != NULL )
			{
				::fclose( file );
				return false;
			}

			if( file != NULL && ::fclose( file ) != 0 )
			{
				return false;
			}

			if( ( file = xfsopen( filename, n, prot ) ) == NULL )
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

			if( mode & std::ios_base::in )
			{
				m_can_be_read = true;
			}

			if( mode & std::ios_base::out )
			{
				m_can_be_write = true;
			}

			return true;
		}

		virtual int_type overflow( int_type meta = traits_type::eof() )
		{
			if( traits_type::eq_int_type( traits_type::eof(), meta ) )
			{
				return traits_type::not_eof( meta );
			}

			if( pptr() != NULL && pptr() < epptr() )
			{
				*_Pninc() = traits_type::to_char_type( meta );
				return meta;
			}

			if( m_file == NULL )
			{
				return traits_type::eof();
			}

			const char c = traits_type::to_char_type( meta );
			return ( ::fputc( c, m_file ) != EOF ) ? meta : traits_type::eof();
		}

		virtual int_type pbackfail( int_type meta = traits_type::eof() )
		{
			if( gptr() != NULL && eback() < gptr() && 
				( traits_type::eq_int_type( traits_type::eof(), meta ) || 
				  traits_type::eq_int_type( traits_type::to_int_type( gptr()[ -1 ] ), meta ) ) )
			{
				_Gndec();
				return traits_type::not_eof( meta );
			}

			if( m_file == NULL || traits_type::eq_int_type( traits_type::eof(), meta ) )
			{
				return traits_type::eof();
			}

			if( ::ungetc( traits_type::to_char_type( meta ), m_file ) != EOF )
			{
				return meta;
			}

			return traits_type::eof();
		}

		virtual int_type underflow()
		{
			int_type meta;
			if( gptr() != NULL && gptr() < egptr() )
			{
				return traits_type::to_int_type( *gptr() );
			}
			
			if( traits_type::eq_int_type( traits_type::eof(), meta = uflow() ) )
			{
				return meta;
			}

			pbackfail( meta );
			return meta;
		}

		virtual int_type uflow()
		{
			if( gptr() != NULL && gptr() < egptr() )
			{
				return traits_type::to_int_type( *_Gninc() );
			}

			if( m_file == NULL )
			{
				return traits_type::eof();
			}

			int meta;
			if( ( meta = ::fgetc( m_file ) ) == EOF )
			{
				return traits_type::eof();
			}

			return traits_type::to_int_type( static_cast< char >( meta ) );
		}

		virtual pos_type seekoff( off_type off, 
			std::ios_base::seekdir way,
			std::ios_base::openmode =
			( std::ios_base::openmode )( std::ios_base::in | std::ios_base::out ) )
		{
			fpos_t fileposition;

			if( m_file == NULL ||
				( ( off != 0 || way != std::ios_base::cur ) && _FSEEK_OFF( m_file, off, way ) != 0 ) ||
				::fgetpos( m_file, &fileposition ) != 0 )
			{
				return pos_type( std::_BADOFF );
			}

			return pos_type( m_state, fileposition );
		}

		virtual pos_type __CLR_OR_THIS_CALL seekpos( pos_type pos,
			std::ios_base::openmode =
			( std::ios_base::openmode )( std::ios_base::in | std::ios_base::out ) )
		{
			fpos_t fileposition = pos.seekpos();
			off_type off = static_cast< off_type >( pos ) - static_cast< off_type >( _FPOSOFF( fileposition ) );

			if( m_file == NULL ||
				::fsetpos( m_file, &fileposition ) != 0 ||
				( off != 0 && _FSEEK_OFF( m_file, off, SEEK_CUR ) != 0 ) ||
				::fgetpos( m_file, &fileposition ) != 0 )
			{
				return pos_type( std::_BADOFF );
			}

			return pos_type( m_state, fileposition );
		}

		virtual int sync()
		{
			return ( ( m_file == NULL || 
				traits_type::eq_int_type( traits_type::eof(), overflow() ) ||
				0 <= ::fflush( m_file ) ) ? 0 : -1 );
		}

	private:
		FILE* m_file;
		bool m_must_be_closed;
		bool m_can_be_read;
		bool m_can_be_write;
		traits_type::state_type m_state;
	};
}

#endif USELESS_CORE_NATIVE_STREAM_FILEBUF_INCLUDED