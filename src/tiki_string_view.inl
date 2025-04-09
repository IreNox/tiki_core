#pragma once

#include <tiki/tiki_ascii.h>

#include <cstring>

namespace tiki
{
	inline StringView::StringView()
	{
	}

	inline StringView::StringView( const char* cstring )
		: ArrayView( cstring, strlen( cstring ) )
	{
	}

	inline StringView::StringView( const char* string, uintsize length )
		: ArrayView( string, length )
	{
	}

	inline StringView::StringView( const char* start, const char* end )
		: ArrayView( start, end - start )
	{
	}

	template< uintsize TLen >
	inline StringView::StringView( const char( &string )[ TLen ] )
		: ArrayView( string, TLen - 1u )
	{
	}

	inline uintsize StringView::indexOf( char c, uintsize index /*= 0u*/ ) const
	{
		TIKI_ASSERT( index < m_length );

		uintsize i = index;
		while( i < m_length )
		{
			if( m_data[ i ] == c )
			{
				return i;
			}
			i++;
		}

		return InvalidIndex;
	}

	inline uintsize StringView::indexOf( const StringView& str, uintsize index /*= 0u*/ ) const
	{
		if( str.getLength() > m_length ) return InvalidIndex;

		uintsize i = index;
		uintsize c = m_length - str.getLength();

		do
		{
			uintsize b = 0;
			bool found = true;
			while( b < str.getLength() )
			{
				if( m_data[ i + b ] != str[ b ] )
				{
					found = false;
					break;
				}
				b++;
			}

			if( found )
			{
				return i;
			}

			i++;
		}
		while( i <= c );

		return InvalidIndex;
	}

	inline uintsize StringView::lastIndexOf( char c, uintsize index /*= InvalidIndex*/ ) const
	{
		index = min( index, m_length - 1u );
		while( index < m_length )
		{
			if( m_data[ index ] == c )
			{
				return index;
			}

			index--;
		}

		return InvalidIndex;
	}

	inline uintsize StringView::lastIndexOf( const StringView& str, uintsize index /*= InvalidIndex*/ ) const
	{
		index = min( index, m_length - 1u );
		while( index < m_length )
		{
			uintsize b = 0;
			bool found = true;
			while( b < str.getLength() )
			{
				if( m_data[ index + b ] != str[ b ] )
				{
					found = false;
					break;
				}

				b++;
			}

			if( found )
			{
				return index;
			}

			index--;
		}

		return InvalidIndex;
	}

	inline bool StringView::contains( const StringView& str ) const
	{
		return indexOf( str ) != InvalidIndex;
	}

	inline bool StringView::startsWith( const StringView& str ) const
	{
		if( m_length < str.getLength() )
		{
			return false;
		}

		uintsize i = 0;
		while( i < str.getLength() )
		{
			if( m_data[ i ] != str[ i ] )
			{
				return false;
			}
			i++;
		}

		return true;
	}

	inline bool StringView::startsWithNoCase( const StringView& str ) const
	{
		if( m_length < str.getLength() )
		{
			return false;
		}

		uintsize i = 0;
		while( i < str.getLength() )
		{
			if( !ascii::isEqualsNoCase( m_data[ i ], str[ i ] ) )
			{
				return false;
			}
			i++;
		}

		return true;
	}

	inline bool StringView::endsWith( const StringView& str ) const
	{
		if( m_length < str.getLength() )
		{
			return false;
		}

		uintsize b = 0;
		uintsize i = m_length - str.getLength();
		while( i < m_length )
		{
			if( m_data[ i ] != str[ b ] )
			{
				return false;
			}
			i++;
			b++;
		}

		return true;
	}

	inline bool StringView::endsWithNoCase( const StringView& str ) const
	{
		if( m_length < str.getLength() )
		{
			return false;
		}

		uintsize b = 0;
		uintsize i = m_length - str.getLength();
		while( i < m_length )
		{
			if( ascii::isEqualsNoCase( m_data[ i ], str[ b ] ) )
			{
				return false;
			}
			i++;
			b++;
		}

		return true;
	}

	inline uintsize StringView::countSubstring( const StringView& substr ) const
	{
		if( substr.getLength() > m_length )
		{
			return 0u;
		}

		uintsize index = 0;
		uintsize count = 0;
		while( index < m_length )
		{
			uintsize b = 0;
			bool found = true;
			while( b < substr.getLength() )
			{
				if( m_data[ index + b ] != substr[ b ] )
				{
					found = false;
					break;
				}
				b++;
			}

			if( found )
			{
				count++;
				index += substr.getLength();
			}
			else
			{
				index++;
			}
		}

		return count;
	}

	inline StringView StringView::trim() const
	{
		uintsize startIndex = 0u;
		while( ascii::isWhitespace( m_data[ startIndex ] ) && startIndex < getLength() )
		{
			startIndex++;
		}

		uintsize endIndex = getLength();
		while( ascii::isWhitespace( m_data[ endIndex ] ) && endIndex > 0u )
		{
			endIndex--;
		}

		return subString( startIndex, endIndex - startIndex );
	}

	inline StringView StringView::subString( uintsize startIndex ) const
	{
		if( startIndex >= m_length )
		{
			return StringView();
		}

		return StringView( m_data + startIndex, m_length - startIndex );
	}

	inline StringView StringView::subString( uintsize startIndex, uintsize length ) const
	{
		TIKI_ASSERT( length <= m_length - startIndex );

		if( startIndex >= m_length )
		{
			return StringView();
		}

		return StringView( m_data + startIndex, length );
	}

	inline const char* StringView::toConstCharPointer() const
	{
		return m_data;
	}

	inline bool StringView::operator==( const char* rhs ) const
	{
		if( rhs == nullptr )
		{
			return m_length == 0u;
		}
		else if( m_data == nullptr )
		{
			return *rhs == '\0';
		}

		return strncmp( m_data, rhs, m_length ) == 0;
	}

	inline bool StringView::operator==( const StringView& rhs ) const
	{
		if( m_length != rhs.m_length )
		{
			return false;
		}
		else if( m_data == nullptr || rhs.getData() == nullptr )
		{
			return m_length == 0u;
		}

		return strncmp( m_data, rhs.m_data, m_length ) == 0;
	}

	inline bool StringView::operator!=( const char* rhs ) const
	{
		if( m_data == nullptr || rhs == nullptr )
		{
			return (m_length != 0u || rhs != nullptr) && m_data != rhs;
		}

		return strncmp( m_data, rhs, m_length ) != 0;
	}

	inline bool StringView::operator!=( const StringView& rhs ) const
	{
		if( m_length != rhs.getLength() )
		{
			return true;
		}
		else if( m_data == nullptr || rhs.getData() == nullptr )
		{
			return m_length != 0u && m_data != rhs.getData();
		}

		return strncmp( m_data, rhs.getData(), m_length ) != 0;
	}


	template<>
	inline TikiHash32 calculateValueHash( const StringView& value )
	{
		return calculateHash( value.getData(), value.getLength(), 0u );
	}
}
