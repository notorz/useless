//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_WITER_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_WITER_INCLUDED

#include <type_traits>
#include <boost/cstdint.hpp>
#include <boost/mpl/eval_if.hpp>
#include "core.native/string.h"
#include "core.native/io/stream/streambase.h"
#include "core.native/encoding.h"

namespace useless
{
	namespace binary_write_helper
	{
		template<typename Archive, typename T>
		void invoke( Archive& bw, const T& val )
		{
			const_cast<T&>( val ).serialize( bw, 0 );
		}
	}

	template<typename Allocator>
	class basic_binary_writer
	{
	private:
		struct write_pointer_type
		{
			template<typename TPtr>
			static void invoke( basic_binary_writer& bw, const TPtr& val )
			{
				if( val != nullptr )
				{
					bw.write( *val );
				}
			}
		};

		struct write_enum_type
		{
			template<typename T>
			static void invoke( basic_binary_writer& bw, const T& val )
			{
				const int i = static_cast<int>( val );
				bw.write( &i, sizeof( int ) );
			}
		};

		struct write_array_type
		{
			template<typename T>
			static void write_member( basic_binary_writer& bw, const T* val, unsigned long count, std::true_type )
			{
				bw.write( &val[ 0 ], sizeof( T ) * count );
			}

			template<typename T>
			static void write_member( basic_binary_writer& bw, const T* val, unsigned long count, std::false_type )
			{
				for( unsigned long i = 0; i < count; ++i )
				{
					bw.write( val[ i ] );
				}
			}

			template<typename T>
			static void write_member( basic_binary_writer& bw, const T* val, unsigned long count )
			{
				if( count > 0 )
				{
					typedef typename std::is_arithmetic<typename std::remove_const<T>::type> use_optimized;
					write_member( bw, val, count, use_optimized() );
				}
			}

			template<typename T>
			static void invoke( basic_binary_writer& bw, const T& val )
			{
				unsigned long count = static_cast< unsigned long >( sizeof( val ) /
					( static_cast< const char* >( static_cast< const void* >( &val[ 1 ] ) )
						- static_cast< const char* >( static_cast< const void* >( &val[ 0 ] ) ) ) );

				bw.write( &count, sizeof( unsigned long ) );
				write_member( bw, &val[ 0 ], count );
			}

			static void invoke( basic_binary_writer& bw, const char val[] )
			{
				bw.write( std::string( val ) );
			}

			static void invoke( basic_binary_writer& bw, const wchar_t val[] )
			{
				bw.write( std::wstring( val ) );
			}
		};

		struct write_non_pointer_type
		{
			struct write_primitive_type
			{
				template<typename T>
				static void invoke( basic_binary_writer& bw, const T& val )
				{
					bw.write( &val, sizeof( T ) );
				}
			};

			struct write_object_class_type
			{
				template<typename T>
				static void invoke( basic_binary_writer& bw, const T& val )
				{
					binary_write_helper::invoke( bw, val );
				}
			};

			template<typename T>
			static void invoke( basic_binary_writer& bw, const T& val )
			{
				typename boost::mpl::eval_if<std::is_fundamental<T>,
					write_primitive_type,	// true
					write_object_class_type	// false
				>::invoke( bw, val );
			}
		};

		struct write_helper
		{
			template<typename T>
			static void invoke( basic_binary_writer& bw, const T& val )
			{
				typename boost::mpl::eval_if<std::is_pointer<T>,
					write_pointer_type,
					//else
					typename boost::mpl::eval_if<std::is_enum<T>,
					write_enum_type,
					//else
					typename boost::mpl::eval_if<std::is_array<T>,
					write_array_type,
					//else
					write_non_pointer_type
					>
					>
				>::invoke( bw, val );
			}
		};

	public:
		basic_binary_writer()
			: m_stream( nullptr )
			, m_must_be_deleted( false )
			, m_encoding( encoding::get() )
		{

		}

		basic_binary_writer( streambase& stream )
			: m_stream( nullptr )
			, m_must_be_deleted( false )
			, m_encoding( encoding::get() )
		{
			if( stream.can_be_write() )
			{
				m_stream = &stream;
			}
		}

		basic_binary_writer( size_t size, bool growable = true )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
			, m_encoding( encoding::get() )
		{
			if( growable )
			{
				m_stream = new basic_dynamic_stream<Allocator>( size );
			}
			else
			{
				m_stream = new basic_fixed_stream<Allocator>( size );
			}
		}

		basic_binary_writer( void* address, size_t size )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
			, m_encoding( encoding::get() )
		{
			m_stream = new memory_stream( address, size );
		}

		basic_binary_writer( const char* filename, int openmode )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
			, m_encoding( encoding::get() )
		{
			if( openmode & openmode::out )
			{
				m_stream = new file_stream( filename, openmode );
			}
		}

		basic_binary_writer( const string_ansi& filename, int openmode )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
			, m_encoding( encoding::get() )
		{
			if( openmode & openmode::out )
			{
				m_stream = new file_stream( filename, openmode );
			}
		}

		basic_binary_writer( const wchar_t* filename, int openmode )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
			, m_encoding( encoding::get() )
		{
			if( openmode & openmode::out )
			{
				m_stream = new file_stream( filename, openmode );
			}
		}

		basic_binary_writer( const string_wide& filename, int openmode )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
			, m_encoding( encoding::get() )
		{
			if( openmode & openmode::out )
			{
				m_stream = new file_stream( filename, openmode );
			}
		}

		virtual ~basic_binary_writer()
		{
			if( m_must_be_deleted )
			{
				delete m_stream;
			}
		}

	private:
		basic_binary_writer( const basic_binary_writer& );
		basic_binary_writer& operator=( const basic_binary_writer& );

	public:
		bool stream( streambase& stream )
		{
			if( !stream.can_be_write() )
			{
				return false;
			}

			if( m_must_be_deleted )
			{
				delete m_stream;
			}

			m_stream = &stream;
			m_must_be_deleted = false;
		}

		streambase* stream()
		{
			return m_stream;
		}

		const streambase* stream() const
		{
			return m_stream;
		}

		bool encoding( const encoding& encoding )
		{
			m_encoding = encoding;
		}

		const useless::encoding& encoding() const
		{
			return m_encoding;
		}

		void write( const void* buffer, size_t count )
		{
			if( m_stream != nullptr )
			{
				m_stream->write( buffer, count );
			}
		}

		void write_u8( unsigned char val )
		{
			write<unsigned char>( val );
		}

		void write_s8( char val )
		{
			write<char>( val );
		}

		void write_u16( unsigned short val )
		{
			write<unsigned short>( val );
		}

		void write_s16( short val )
		{
			write<short>( val );
		}

		void write_u32( unsigned long val )
		{
			write<unsigned long>( val );
		}

		void write_s32( long val )
		{
			write<long>( val );
		}

		void write_u64( uint64_t val )
		{
			write<uint64_t>( val );
		}

		void write_s64( int64_t val )
		{
			write<int64_t>( val );
		}

		void write_f32( float val )
		{
			write<float>( val );
		}

		void write_f64( double val )
		{
			write<double>( val );
		}

		void write_bool( bool val )
		{
			write<bool>( val );
		}

		void write_string( const string_ansi& val )
		{
			write<string_ansi>( val );
		}

		void write_string( const string_wide& val )
		{
			write<string_wide>( val );
		}

		template<typename T>
		void write( const T& val )
		{
			write_helper::invoke( *this, val );
		}

		template<typename T>
		basic_binary_writer& operator << ( const T& val )
		{
			write<T>( val );
			return *this;
		}

		template<class T>
		basic_binary_writer& operator & ( const T& val )
		{
			return *this << val;
		};

	private:
		streambase* m_stream;
		bool m_must_be_deleted;

		const useless::encoding& m_encoding;
	};
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_WITER_INCLUDED