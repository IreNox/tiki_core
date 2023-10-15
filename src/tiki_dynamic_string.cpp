#include "tiki/tiki_dynamic_string.h"

#include "tiki/tiki_ascii.h"
#include "tiki/tiki_functions.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>

namespace tiki
{
	DynamicString::DynamicString()
	{
	}

	DynamicString::DynamicString( const StringView& string )
	{
		assign( string );
	}

	DynamicString::DynamicString( const DynamicString& string )
	{
		assign( string );
	}

	DynamicString::DynamicString( const char* pString )
	{
		const uintsize stringLength = strlen( pString );
		checkCapacity( stringLength + 1u );
		memcpy( m_data, pString, stringLength );
		terminate( stringLength );
	}

	DynamicString::DynamicString( const char* pString, uintsize stringLength )
	{
		TIKI_ASSERT( strlen( pString ) >= stringLength );

		checkCapacity( stringLength + 1u );
		memcpy( m_data, pString, stringLength );
		terminate( stringLength );
	}

	DynamicString::~DynamicString()
	{
	}

	void DynamicString::assign( const char* string )
	{
		const uintsize length = strlen( string );
		assign( string, length );
	}

	void DynamicString::assign( const char* string, size_t length )
	{
		if( length == 0u )
		{
			m_length = 0u;
			return;
		}

		checkCapacity( length + 1u );
		memcpy( m_data, string, length );
		terminate( length );
	}

	void DynamicString::assign( const StringView& string )
	{
		assign( string.getData(), string.getLength() );
	}

	void DynamicString::assign( const DynamicString& string )
	{
		assign( string.m_data, string.m_length );
	}

	void DynamicString::terminate( uintsize newLength )
	{
		TIKI_ASSERT( newLength < m_capacity );
		m_length = newLength;
		m_data[ m_length ] = '\0';
	}

	uintsize DynamicString::indexOf( char c, uintsize index /*= 0u*/ ) const
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

	uintsize DynamicString::indexOf( const StringView& str, uintsize index /*= 0u*/ ) const
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
		} while( i <= c );

		return InvalidIndex;
	}

	uintsize DynamicString::lastIndexOf( char c, uintsize index /*= InvalidIndex*/ ) const
	{
		index = TIKI_MIN( index, m_length - 1u );
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

	uintsize DynamicString::lastIndexOf( const StringView& str, uintsize index /*= InvalidIndex*/ ) const
	{
		index = TIKI_MIN( index, m_length - 1u );
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

	bool DynamicString::contains( char c ) const
	{
		return indexOf( c ) != InvalidIndex;
	}

	bool DynamicString::contains( const StringView& str ) const
	{
		return indexOf( str ) != InvalidIndex;
	}

	bool DynamicString::startsWith( char c ) const
	{
		if( m_length < 1 )
		{
			return false;
		}

		return m_data[ 0 ] == c;
	}

	bool DynamicString::startsWith( const StringView& str ) const
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

	bool DynamicString::startsWithNoCase( const StringView& str ) const
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

	bool DynamicString::endsWith( char c ) const
	{
		if( m_length < 1 )
		{
			return false;
		}

		return m_data[ m_length - 1 ] == c;
	}

	bool DynamicString::endsWith( const StringView& str ) const
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

	bool DynamicString::endsWithNoCase( const StringView& str ) const
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

	uintsize DynamicString::countSubstring( const StringView& substr ) const
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

	DynamicString DynamicString::trim() const
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

	DynamicString DynamicString::toLower() const
	{
		DynamicString result = *this;
		for( uintsize i = 0u; i < result.getLength(); ++i )
		{
			result[ i ] = ascii::toLower( result[ i ] );
		}

		return result;
	}

	DynamicString DynamicString::toUpper() const
	{
		DynamicString result = *this;
		for( uintsize i = 0u; i < result.getLength(); ++i )
		{
			result[ i ] = ascii::toUpper( result[ i ] );
		}

		return result;
	}

	DynamicString DynamicString::subString( uintsize startIndex ) const
	{
		if( startIndex >= m_length )
		{
			return DynamicString();
		}

		return DynamicString( m_data + startIndex, m_length - startIndex );
	}

	DynamicString DynamicString::subString( uintsize startIndex, uintsize length ) const
	{
		if( startIndex + length >= m_length )
		{
			return DynamicString();
		}

		return DynamicString( m_data + startIndex, length );
	}

	DynamicString DynamicString::replace( char oldChar, char newChar ) const
	{
		DynamicString result = *this;
		for( uintsize i = 0u; i < m_length; ++i )
		{
			if( result[ i ] == oldChar )
			{
				result[ i ] = newChar;
			}
		}

		return result;
	}

	DynamicString DynamicString::replace( const DynamicString& oldString, const DynamicString& newString ) const
	{
		const uintsize count = countSubstring( oldString );
		const uintsize length = m_length - ( count * oldString.m_length ) + ( count * newString.m_length );

		if( count == 0 )
		{
			return *this;
		}

		DynamicString result;
		result.checkCapacity( length + 1u );

		uintsize i = 0;
		uintsize offsetOld = 0;
		uintsize offsetNew = 0;
		while( i < count )
		{
			const uintsize index			= indexOf( oldString, offsetOld );
			const uintsize oldDifferent	= index - offsetOld;

			memcpy( result.m_data + offsetNew, m_data + offsetOld, index - offsetOld );
			offsetOld += oldDifferent;
			offsetNew += oldDifferent;

			memcpy( result.m_data + offsetNew, newString.m_data, newString.m_length );
			offsetOld += oldString.m_length;
			offsetNew += newString.m_length;

			i++;
		}

		memcpy( result.m_data + offsetNew, m_data + offsetOld, m_length - offsetOld );
		result.terminate( length );

		return result;
	}

	DynamicString DynamicString::insert( char c, uintsize index ) const
	{
		TIKI_ASSERT( index <= m_length );

		DynamicString result;
		result.checkCapacity( m_length + 1u );

		memcpy( result.m_data, m_data, index );
		result.m_data[ index ] = c;
		memcpy( result.m_data + index, m_data, m_length - index );
		result.terminate( m_length + 1u );

		return result;
	}

	DynamicString DynamicString::erase( uintsize index ) const
	{
		TIKI_ASSERT( index <= m_length );
		TIKI_ASSERT( m_length > 0u );

		DynamicString result;
		result.checkCapacity( m_length );
		memcpy( result.m_data, m_data, index );
		memcpy( result.m_data + index, m_data, m_length - index );
		result.terminate( m_length - 1u );

		return result;
	}

	DynamicString DynamicString::popBack() const
	{
		DynamicString result;
		result.checkCapacity( m_length );
		memcpy( result.m_data, m_data, m_length - 1u );
		result.terminate( m_length - 1u );

		return result;
	}

	DynamicString DynamicString::pushBack( char c ) const
	{
		DynamicString result;
		result.checkCapacity( m_length + 2u );
		memcpy( result.m_data, m_data, m_length );
		result.m_data[ m_length ] = c;
		result.terminate( m_length + 1u );

		return result;
	}

	char* DynamicString::beginWrite()
	{
		return m_data;
	}

	void DynamicString::endWrite( uintsize newLength /*= (uintsize)-1 */ )
	{
		if( newLength == (uintsize)-1 )
		{
			newLength = strlen( m_data );
		}

		m_length = newLength;
	}

	const char* DynamicString::toConstCharPointer() const
	{
		if( m_length == 0u )
		{
			return "";
		}

		return m_data;
	}

	char* DynamicString::getBegin()
	{
		return m_data;
	}

	const char* DynamicString::getBegin() const
	{
		return m_data;
	}

	char* DynamicString::getEnd()
	{
		return m_data + m_length;
	}

	const char* DynamicString::getEnd() const
	{
		return m_data + m_length;
	}

	char& DynamicString::operator[]( uintsize index )
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ index ];
	}

	const char& DynamicString::operator[]( uintsize index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ index ];
	}

	DynamicString& DynamicString::operator=( const char* rhs )
	{
		assign( rhs );
		return *this;
	}

	DynamicString& DynamicString::operator=( const StringView& rhs )
	{
		assign( rhs );
		return *this;
	}

	DynamicString& DynamicString::operator=( const DynamicString& rhs )
	{
		assign( rhs );
		return *this;
	}

	DynamicString& DynamicString::operator+=( const char* pString )
	{
		const uintsize stringLength = strlen( pString );

		checkCapacity( m_length + stringLength + 1u );
		memcpy( m_data + m_length, pString, stringLength );
		terminate( m_length + stringLength );

		return *this;
	}

	DynamicString& DynamicString::operator+=( const StringView& rhs )
	{
		checkCapacity( m_length + rhs.getLength() + 1u );
		memcpy( m_data + m_length, rhs.getData(), rhs.getLength() );
		terminate( m_length + rhs.getLength() );

		return *this;
	}

	DynamicString& DynamicString::operator+=( const DynamicString& rhs )
	{
		checkCapacity( m_length + rhs.m_length + 1u );
		memcpy( m_data + m_length, rhs.m_data, rhs.m_length );
		terminate( m_length + rhs.m_length );

		return *this;
	}

	DynamicString DynamicString::operator+( const char* pString ) const
	{
		const uintsize stringLength = strlen( pString );

		DynamicString result;
		result.checkCapacity( m_length + stringLength + 1u );
		memcpy( result.m_data, m_data, m_length );
		memcpy( result.m_data + m_length, pString, stringLength );
		result.terminate( m_length + stringLength );

		return result;
	}

	DynamicString DynamicString::operator+( const StringView& rhs ) const
	{
		DynamicString result;
		result.checkCapacity( m_length + rhs.getLength() + 1u );
		memcpy( result.m_data, m_data, m_length );
		memcpy( result.m_data + m_length, rhs.getData(), rhs.getLength() );
		result.terminate( m_length + rhs.getLength() );

		return result;
	}

	DynamicString DynamicString::operator+( const DynamicString& rhs ) const
	{
		DynamicString result;
		result.checkCapacity( m_length + rhs.m_length + 1u );
		memcpy( result.m_data, m_data, m_length );
		memcpy( result.m_data + m_length, rhs.m_data, rhs.m_length );
		result.terminate( m_length + rhs.m_length );

		return result;
	}

	bool DynamicString::operator==( const char* rhs ) const
	{
		if( rhs == nullptr )
		{
			return m_length == 0u;
		}
		else if( m_data == nullptr )
		{
			return *rhs == '\0';
		}

		return strcmp( m_data, rhs ) == 0;
	}

	bool DynamicString::operator==( const StringView& rhs ) const
	{
		if( m_length != rhs.getLength() )
		{
			return false;
		}
		else if( m_data == nullptr || rhs.getData() == nullptr )
		{
			return m_length == 0u;
		}

		return strcmp( m_data, rhs.getData() ) == 0;
	}

	bool DynamicString::operator==( const DynamicString& rhs ) const
	{
		if( m_length != rhs.m_length )
		{
			return false;
		}
		else if( m_data == nullptr || rhs.getData() == nullptr )
		{
			return m_length == 0u;
		}

		return strcmp( m_data, rhs.m_data ) == 0;
	}

	bool DynamicString::operator!=( const char* rhs ) const
	{
		if( m_data == nullptr || rhs == nullptr )
		{
			return m_length != 0u && m_data != rhs;
		}

		return strcmp( m_data, rhs ) != 0;
	}

	bool DynamicString::operator!=( const StringView& rhs ) const
	{
		if( m_length != rhs.getLength() )
		{
			return true;
		}
		else if( m_data == nullptr || rhs.getData() == nullptr )
		{
			return m_length != 0u && m_data != rhs.getData();
		}

		return strcmp( m_data, rhs.getData() ) != 0;
	}

	bool DynamicString::operator!=( const DynamicString& rhs ) const
	{
		if( m_length != rhs.m_length )
		{
			return true;
		}
		else if( m_data == nullptr || rhs.getData() == nullptr )
		{
			return m_length != 0u && m_data != rhs.getData();
		}

		return strcmp( m_data, rhs.m_data ) != 0;
	}

	DynamicString::operator const char*() const
	{
		return m_data;
	}

	DynamicString::operator StringView() const
	{
		return StringView( m_data, m_length );
	}

	DynamicString operator+( const char* lhs, const DynamicString& rhs )
	{
		DynamicString string( lhs );
		string += rhs;
		return string;
	}

	DynamicString operator ""_s( const char* string, uintsize length )
	{
		return DynamicString( string, length );
	}

	DynamicString DynamicString::format( const char* format, ... )
	{
		va_list args;
		va_start( args, format );
		const DynamicString result = formatArgs( format, args );
		va_end( args );

		return result;
	}

	DynamicString DynamicString::formatArgs( const char* format, va_list args )
	{
		char buffer[ 256u ];

		int length = vsnprintf( buffer, sizeof( buffer ), format, args );
		if( length < 0 )
		{
			return DynamicString();
		}
		else if( length < sizeof( buffer ) )
		{
			DynamicString result;
			result.assign( buffer, length );

			return result;
		}

		DynamicString result;
		result.reserve( length + 1u );

		length = vsnprintf( result.m_data, result.m_capacity, format, args );
		if( length < 0 )
		{
			return DynamicString();
		}

		result.terminate( length );
		return result;
	}

	template<>
	TikiHash32 calculateValueHash( const DynamicString& value )
	{
		return calculateHash( value.getData(), value.getLength(), 0u );
	}
}