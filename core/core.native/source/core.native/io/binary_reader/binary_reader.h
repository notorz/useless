//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_READER_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_READER_INCLUDED

#include <stdint.h>
#include <type_traits>
#include <vector>
#include <boost/mpl/eval_if.hpp>
#include "core.native/string.h"
#include "core.native/io/stream/streambase.h"

namespace useless
{
	namespace binary_read_helper
	{
		template<typename Archive, typename T>
		void read( Archive& br, T& val )
		{
			val.serialize( br, 0 );
		}
	}

	template<typename Allocator>
	class basic_binary_reader
	{
	private:
		struct read_pointer_type
		{
			template<typename TPtr>
			static void invoke( basic_binary_reader& br, TPtr& val )
			{
				if( val != nullptr )
				{
					br.read( *val );
				}
			}
		};

		struct read_enum_type
		{
			template<typename T>
			static void invoke( basic_binary_reader& br, T& val )
			{
				int temp;
				br.read( &temp, sizeof( int ) );
				val = static_cast<T>( temp );
			}
		};

		struct read_array_type
		{
			template<typename T>
			static void read_member( basic_binary_reader& br, T* val, unsigned long count, std::true_type )
			{
				br.read( &val[ 0 ], sizeof( T ) * count );
			}

			template<typename T>
			static void read_member( basic_binary_reader& br, T* val, unsigned long count, std::false_type )
			{
				for( unsigned long i = 0; i < count; ++i )
				{
					br.read( val[ i ] );
				}
			}

			template<typename T>
			static void read_member( basic_binary_reader& br, T* val, unsigned long count )
			{
				if( count > 0 )
				{
					typedef typename std::is_arithmetic<typename std::remove_const<T>::type> use_optimized;
					read_member( br, val, count, use_optimized() );
				}
			}

			template<typename T>
			static void drop_member( basic_binary_reader& br, T*, unsigned long count )
			{
				if( count > 0 )
				{
					std::vector<T> temp;
					temp.resize( count );

					typedef typename std::is_arithmetic<typename std::remove_const<T>::type> use_optimized;
					read_member( br, &temp[ 0 ], count, use_optimized() );
				}
			}

			template<typename T>
			static void invoke( basic_binary_reader& br, T& val )
			{
				unsigned long dest_count = static_cast< unsigned long >( sizeof( val ) /
					( static_cast<const char*>( static_cast<const void*>( &val[ 1 ] ) )
						- static_cast<const char*>( static_cast<const void*>( &val[ 0 ] ) ) ) );

				unsigned long count;
				br.read( &count, sizeof( unsigned long ) );
				
				if( count > dest_count )
				{
					read_member( br, &val[ 0 ], dest_count );
					drop_member( br, &val[ 0 ], count - dest_count );
				}
				else
				{
					read_member( br, &val[ 0 ], count );
				}
			}
		};

		struct read_non_pointer_type
		{
			struct read_primitive_type
			{
				template<typename T>
				static void invoke( basic_binary_reader& br, T& val )
				{
					br.read( &val, sizeof( T ) );
				}
			};

			struct read_object_class_type
			{
				template<typename T>
				static void invoke( basic_binary_reader& br, T& val )
				{
					binary_read_helper::invoke( br, val );
				}
			};

			template<typename T>
			static void invoke( basic_binary_reader& br, T& val )
			{
				typename boost::mpl::eval_if<std::is_fundamental<T>,
					read_primitive_type,	// true
					read_object_class_type	// false
				>::Invoke( br, val );
			}
		};

		struct read_helper
		{
			template<typename T>
			static void invoke( basic_binary_reader& br, T& val )
			{
				typename boost::mpl::eval_if<std::is_pointer<T>,
					read_pointer_type,
					//else
					typename boost::mpl::eval_if<std::is_enum<T>,
					read_enum_type,
					//else
					typename boost::mpl::eval_if<std::is_array<T>,
					read_array_type,
					//else
					read_non_pointer_type
					>
					>
				>::invoke( br, val );
			}
		};

	public:
		basic_binary_reader()
			: m_stream( nullptr )
			, m_must_be_deleted( false )
		{

		}

		basic_binary_reader( streambase& stream )
			: m_stream( nullptr )
			, m_must_be_deleted( false )
		{
			if( stream.can_be_read() )
			{
				m_stream = &stream;
			}
		}

		basic_binary_reader( void* address, size_t size )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
		{
			m_stream = new memory_stream( address, size );
		}

		basic_binary_reader( const char* filename, int openmode )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
		{
			if( openmode & openmode::in )
			{
				m_stream = new file_stream( filename, openmode );
			}
		}

		basic_binary_reader( const string_ansi& filename, int openmode )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
		{
			if( openmode & openmode::in )
			{
				m_stream = new file_stream( filename, openmode );
			}
		}

		basic_binary_reader( const wchar_t* filename, int openmode )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
		{
			if( openmode & openmode::in )
			{
				m_stream = new file_stream( filename, openmode );
			}
		}

		basic_binary_reader( const string_wide& filename, int openmode )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
		{
			if( openmode & openmode::in )
			{
				m_stream = new file_stream( filename, openmode );
			}
		}

		virtual ~basic_binary_reader()
		{
			if( m_must_be_deleted )
			{
				delete m_stream;
			}
		}

		bool stream( streambase& stream )
		{
			if( !stream.can_be_read() )
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

		void read( void* buffer, size_t size )
		{
			if( m_stream != nullptr )
			{
				m_stream->read( buffer, size );
			}
		}

		unsigned char read_u8()
		{
			unsigned char val;
			read<unsigned char>( val );
			return val;
		}

		char read_s8()
		{
			char val;
			read<char>( val );
			return val;
		}

		unsigned short read_u16()
		{
			unsigned short val;
			read<unsigned short>( val );
			return val;
		}

		short read_s16()
		{
			short val;
			read<short>( val );
			return val;
		}

		unsigned long read_u32()
		{
			unsigned long val;
			read<unsigned long>( val );
			return val;
		}

		long read_s32()
		{
			long val;
			read<long>( val );
			return val;
		}

		uint64_t read_u64()
		{
			uint64_t val;
			read<uint64_t>( val );
			return val;
		}

		int64_t read_s64()
		{
			int64_t val;
			read<int64_t>( val );
			return val;
		}

		float read_f32()
		{
			float val;
			read<float>( val );
			return val;
		}

		double read_f64()
		{
			double val;
			read<double>( val );
			return val;
		}

		bool read_bool()
		{
			bool val;
			read<bool>( val );
			return val;
		}

		string_ansi read_string_ansi()
		{
			string_ansi val;
			read<string_ansi>( val );
			return val;
		}

		string_wide read_string_wide()
		{
			string_wide val;
			read<string_wide>( val );
			return val;
		}

#ifdef UNICODE
		string read_string()
		{
			return read_string_wide();
		}
#else
		string read_string()
		{
			return read_string_ansi();
		}
#endif

		template<typename T>
		void read( T& val )
		{
			read_helper::invoke( *this, val );
		}

		template<typename T>
		basic_binary_reader& operator >> ( T& val )
		{
			read<T>( val );
			return *this;
		}

		template<class T>
		basic_binary_reader& operator & ( T& val )
		{
			return *this >> val;
		};

	private:
		streambase* m_stream;
		bool m_must_be_deleted;
	};
}

#endif USELESS_CORE_NATIVE_IO_BINARY_READER_INCLUDED