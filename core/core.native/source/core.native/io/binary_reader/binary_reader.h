//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_READER_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_READER_INCLUDED

#include <type_traits>
#include <vector>
#include <boost/cstdint.hpp>
#include <boost/mpl/eval_if.hpp>
#include "core.native/string.h"
#include "core.native/io/stream/streambase.h"
#include "core.native/encoding.h"

namespace useless
{
    template<typename T>
	struct binary_read_helper
	{
		template<typename Archive>
		static void invoke( Archive& br, T& val )
		{
			val.serialize( br, 0 );
		}
    };

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
			static void read_member( basic_binary_reader& br, T* val, uint32_t count, std::true_type )
			{
				br.read( &val[ 0 ], sizeof( T ) * count );
			}

			template<typename T>
			static void read_member( basic_binary_reader& br, T* val, uint32_t count, std::false_type )
			{
				for( uint32_t i = 0; i < count; ++i )
				{
					br.read( val[ i ] );
				}
			}

			template<typename T>
			static void read_member( basic_binary_reader& br, T* val, uint32_t count )
			{
				if( count > 0 )
				{
					typedef typename std::is_arithmetic<typename std::remove_const<T>::type> use_optimized;
					read_member( br, val, count, use_optimized() );
				}
			}

			template<typename T>
			static void drop_member( basic_binary_reader& br, T*, uint32_t count )
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
			static void read( basic_binary_reader& br, T& val, size_t dest_count )
			{
				uint32_t count;
				br.read( &count, sizeof( uint32_t ) );

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

			static void read( basic_binary_reader& br, char val[], size_t dest_count )
			{
				std::string temp;
				br.read( temp );

				if( dest_count >= 1 )
				{
					size_t count = ( std::min )( dest_count, temp.size() );
#if ( _WIN32 || _WIN64 )
					::memcpy_s( val, count, temp.c_str(), count );
#else
                    ::memcpy( val, temp.c_str(), count );
#endif
					val[ dest_count - 1 ] = 0;
				}
			}

			static void read( basic_binary_reader& br, wchar_t val[], size_t dest_count )
			{
				std::wstring temp;
				br.read( temp );

				if( dest_count >= 1 )
				{
					size_t count = ( std::min )( dest_count, temp.size() ) * sizeof( wchar_t );
#if ( _WIN32 || _WIN64 )
					::memcpy_s( val, count, temp.c_str(), count );
#else
					::memcpy( val, temp.c_str(), count );
#endif
					val[ dest_count - 1 ] = 0;
				}
			}

			template<typename T>
			static void invoke( basic_binary_reader& br, T& val )
			{
				size_t dest_count = sizeof( val ) /
					( static_cast<const char*>( static_cast<const void*>( &val[ 1 ] ) )
						- static_cast<const char*>( static_cast<const void*>( &val[ 0 ] ) ) );

				read( br, val, dest_count );
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
					binary_read_helper<T>::invoke( br, val );
				}
			};

			template<typename T>
			static void invoke( basic_binary_reader& br, T& val )
			{
				typedef typename boost::mpl::eval_if<std::is_fundamental<T>,
					boost::mpl::identity<read_primitive_type>,      // true
					boost::mpl::identity<read_object_class_type>	// false
                >::type typex;
                typex::invoke( br, val );
			}
		};

		struct read_helper
		{
			template<typename T>
			static void invoke( basic_binary_reader& br, T& val )
			{
				typedef typename boost::mpl::eval_if<std::is_pointer<T>,
					boost::mpl::identity<read_pointer_type>,
					//else
					typename boost::mpl::eval_if<std::is_enum<T>,
					boost::mpl::identity<read_enum_type>,
					//else
					typename boost::mpl::eval_if<std::is_array<T>,
					boost::mpl::identity<read_array_type>,
					//else
					boost::mpl::identity<read_non_pointer_type>
					>
					>
                >::type typex;
                typex::invoke( br, val );
			}
		};

	public:
		basic_binary_reader()
			: m_stream( nullptr )
			, m_must_be_deleted( false )
			, m_encoding( encoding::get() )
		{

		}

		basic_binary_reader( streambase& stream )
			: m_stream( nullptr )
			, m_must_be_deleted( false )
			, m_encoding( encoding::get() )
		{
			if( stream.can_be_read() )
			{
				m_stream = &stream;
			}
		}

		basic_binary_reader( void* address, size_t size )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
			, m_encoding( encoding::get() )
		{
			m_stream = new memory_stream( address, size );
		}

		basic_binary_reader( const char* filename, int openmode )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
			, m_encoding( encoding::get() )
		{
			if( openmode & openmode::in )
			{
				m_stream = new file_stream( filename, openmode );
			}
		}

		basic_binary_reader( const string_ansi& filename, int openmode )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
			, m_encoding( encoding::get() )
		{
			if( openmode & openmode::in )
			{
				m_stream = new file_stream( filename, openmode );
			}
		}

		basic_binary_reader( const wchar_t* filename, int openmode )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
			, m_encoding( encoding::get() )
		{
			if( openmode & openmode::in )
			{
				m_stream = new file_stream( filename, openmode );
			}
		}

		basic_binary_reader( const string_wide& filename, int openmode )
			: m_stream( nullptr )
			, m_must_be_deleted( true )
			, m_encoding( encoding::get() )
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

	private:
		basic_binary_reader( const basic_binary_reader& );
		basic_binary_reader& operator=( const basic_binary_reader& );

	public:
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

		bool encoding( const encoding& encoding )
		{
			m_encoding = encoding;
		}

		const useless::encoding& encoding() const
		{
			return m_encoding;
		}

		void read( void* buffer, size_t count )
		{
			if( m_stream != nullptr )
			{
				m_stream->read( buffer, count );
			}
		}

		uint8_t read_u8()
		{
			uint8_t val;
			read<uint8_t>( val );
			return val;
		}

		int8_t read_s8()
		{
			int8_t val;
			read<int8_t>( val );
			return val;
		}

		uint16_t read_u16()
		{
			uint16_t val;
			read<uint16_t>( val );
			return val;
		}

		int16_t read_s16()
		{
			int16_t val;
			read<int16_t>( val );
			return val;
		}

		uint32_t read_u32()
		{
			uint32_t val;
			read<uint32_t>( val );
			return val;
		}

		int32_t read_s32()
		{
			int32_t val;
			read<int32_t>( val );
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

		useless::encoding m_encoding;
	};
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_READER_INCLUDED
