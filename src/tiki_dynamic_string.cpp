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
		const uintreg stringLength = strlen( pString );
		checkCapacity( stringLength );
		memcpy( m_string, pString, stringLength );
		terminate( stringLength );
	}

	DynamicString::DynamicString( const char* pString, uintreg stringLength )
	{
		TIKI_ASSERT( strlen( pString ) >= stringLength );

		checkCapacity( stringLength );
		memcpy( m_string, pString, stringLength );
		terminate( stringLength );
	}

	DynamicString::~DynamicString()
	{
		delete[] m_string;
	}

	void DynamicString::assign( const char* string )
	{
		const uintsize length = strlen( string );
		assign( string, length );
	}

	void DynamicString::assign( const char* string, size_t length )
	{
		checkCapacity( length );
		memcpy( m_string, string, length );
		terminate( length );
	}

	void DynamicString::assign( const StringView& string )
	{
		checkCapacity( string.getLength() );
		memcpy( m_string, string.getData(), string.getLength() );
		terminate( string.getLength() );
	}

	void DynamicString::assign( const DynamicString& string )
	{
		checkCapacity( string.m_length );
		memcpy( m_string, string.m_string, string.m_length );
		terminate( string.m_length );
	}

	void DynamicString::clear()
	{
		if( m_capacity > 0u )
		{
			m_string[ 0u ] = 0u;
		}

		m_length = 0u;
	}

	void DynamicString::reserve( uintreg size )
	{
		checkCapacity( size );
	}

	void DynamicString::terminate( uintreg newLength )
	{
		TIKI_ASSERT( newLength < m_capacity );
		m_length = newLength;
		m_string[ m_length ] = '\0';
	}

	uintreg DynamicString::indexOf( char c, uintreg index /*= 0u*/ ) const
	{
		TIKI_ASSERT( index < m_length );

		uintreg i = index;
		while( i < m_length )
		{
			if( m_string[ i ] == c )
			{
				return i;
			}
			i++;
		}

		return InvalidIndex;
	}

	uintreg DynamicString::indexOf( const DynamicString& str, uintreg index /*= 0u*/ ) const
	{
		if( str.m_length > m_length ) return InvalidIndex;

		uintreg i = index;
		uintreg c = m_length - str.m_length;

		do
		{
			uintreg b = 0;
			bool found = true;
			while( b < str.m_length )
			{
				if( m_string[ i + b ] != str.m_string[ b ] )
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

	uintreg DynamicString::lastIndexOf( char c, uintreg index /*= InvalidIndex*/ ) const
	{
		index = TIKI_MIN( index, m_length - 1u );
		while( index < m_length )
		{
			if( m_string[ index ] == c )
			{
				return index;
			}

			index--;
		}

		return InvalidIndex;
	}

	uintreg DynamicString::lastIndexOf( const DynamicString& str, uintreg index /*= InvalidIndex*/ ) const
	{
		index = TIKI_MIN( index, m_length - 1u );
		while( index < m_length )
		{
			uintreg b = 0;
			bool found = true;
			while( b < str.m_length )
			{
				if( m_string[ index + b ] != str.m_string[ b ] )
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

	bool DynamicString::contains( const DynamicString& str ) const
	{
		return indexOf( str ) != InvalidIndex;
	}

	bool DynamicString::startsWith( char c ) const
	{
		if( m_length < 1 ) return false;

		return m_string[ 0 ] == c;
	}

	bool DynamicString::startsWith( const DynamicString& str ) const
	{
		if( m_length < str.m_length ) return false;

		uintreg i = 0;
		while( i < str.m_length )
		{
			if( m_string[ i ] != str.m_string[ i ] ) return false;
			i++;
		}

		return true;
	}

	bool DynamicString::endsWith( char c ) const
	{
		if( m_length < 1 ) return false;

		return m_string[ m_length - 1 ] == c;
	}

	bool DynamicString::endsWith( const DynamicString& str ) const
	{
		if( m_length < str.m_length ) return false;

		uintreg b = 0;
		uintreg i = m_length - str.m_length;
		while( i < m_length )
		{
			if( m_string[ i ] != str.m_string[ b ] ) return false;
			i++;
			b++;
		}

		return true;
	}

	uintreg DynamicString::countSubstring( const DynamicString& substr ) const
	{
		if( substr.m_length > m_length )
			return 0u;

		uintreg index = 0;
		uintreg count = 0;
		while( index < m_length )
		{
			uintreg b = 0;
			bool found = true;
			while( b < substr.m_length )
			{
				if( m_string[ index + b ] != substr.m_string[ b ] )
				{
					found = false;
					break;
				}
				b++;
			}

			if( found )
			{
				count++;
				index += substr.m_length;
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
		uintreg startIndex = 0u;
		while( ascii::isWhitespace( m_string[ startIndex ] ) && startIndex < getLength() )
		{
			startIndex++;
		}

		uintreg endIndex = getLength();
		while( ascii::isWhitespace( m_string[ endIndex ] ) && endIndex > 0u )
		{
			endIndex--;
		}

		return subString( startIndex, endIndex - startIndex );
	}

	DynamicString DynamicString::toLower() const
	{
		DynamicString result = *this;
		for( uintreg i = 0u; i < result.getLength(); ++i )
		{
			result[ i ] = ascii::toLower( result[ i ] );
		}

		return result;
	}

	DynamicString DynamicString::toUpper() const
	{
		DynamicString result = *this;
		for( uintreg i = 0u; i < result.getLength(); ++i )
		{
			result[ i ] = ascii::toUpper( result[ i ] );
		}

		return result;
	}

	DynamicString DynamicString::subString( uintreg startIndex ) const
	{
		TIKI_ASSERT( startIndex <= m_length );
		return DynamicString( m_string + startIndex, m_length - startIndex );
	}

	DynamicString DynamicString::subString( uintreg startIndex, uintreg length ) const
	{
		TIKI_ASSERT( startIndex + length <= m_length );
		return DynamicString( m_string + startIndex, length );
	}

	DynamicString DynamicString::replace( char oldChar, char newChar ) const
	{
		DynamicString result = *this;
		for( uintreg i = 0u; i < m_length; ++i )
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
		const uintreg count = countSubstring( oldString );
		const uintreg length = m_length - ( count * oldString.m_length ) + ( count * newString.m_length );

		if( count == 0 )
		{
			return *this;
		}

		DynamicString result;
		result.checkCapacity( length );

		uintreg i = 0;
		uintreg offsetOld = 0;
		uintreg offsetNew = 0;
		while( i < count )
		{
			const uintreg index			= indexOf( oldString, offsetOld );
			const uintreg oldDifferent	= index - offsetOld;

			memcpy( result.m_string + offsetNew, m_string + offsetOld, index - offsetOld );
			offsetOld += oldDifferent;
			offsetNew += oldDifferent;

			memcpy( result.m_string + offsetNew, newString.m_string, newString.m_length );
			offsetOld += oldString.m_length;
			offsetNew += newString.m_length;

			i++;
		}

		memcpy( result.m_string + offsetNew, m_string + offsetOld, m_length - offsetOld );
		result.terminate( length );

		return result;
	}

	DynamicString DynamicString::insert( char c, uintreg index ) const
	{
		TIKI_ASSERT( index <= m_length );

		DynamicString result;
		result.checkCapacity( m_length + 1u );

		memcpy( result.m_string, m_string, index );
		result.m_string[ index ] = c;
		memcpy( result.m_string + index, m_string, m_length - index );
		result.terminate( m_length + 1u );

		return result;
	}

	DynamicString DynamicString::erase( uintreg index ) const
	{
		TIKI_ASSERT( index <= m_length );
		TIKI_ASSERT( m_length > 0u );

		DynamicString result;
		result.checkCapacity( m_length - 1u );
		memcpy( result.m_string, m_string, index );
		memcpy( result.m_string + index, m_string, m_length - index );
		result.terminate( m_length - 1u );

		return result;
	}

	DynamicString DynamicString::popBack() const
	{
		DynamicString result;
		result.checkCapacity( m_length - 1u );
		memcpy( result.m_string, m_string, m_length - 1u );
		result.terminate( m_length - 1u );

		return result;
	}

	DynamicString DynamicString::pushBack( char c ) const
	{
		DynamicString result;
		result.checkCapacity( m_length + 1u );
		memcpy( result.m_string, m_string, m_length );
		result.m_string[ m_length ] = c;
		result.terminate( m_length + 1u );

		return result;
	}

	char* DynamicString::beginWrite()
	{
		return m_string;
	}

	void DynamicString::endWrite( uintreg newLength /*= (uintreg)-1 */ )
	{
		if( newLength == (uintreg)-1 )
		{
			newLength = strlen( m_string );
		}

		m_length = newLength;
	}

	const char* DynamicString::toConstCharPointer() const
	{
		return m_string;
	}

	char* DynamicString::getBegin()
	{
		return m_string;
	}

	const char* DynamicString::getBegin() const
	{
		return m_string;
	}

	char* DynamicString::getEnd()
	{
		return m_string + m_length;
	}

	const char* DynamicString::getEnd() const
	{
		return m_string + m_length;
	}

	char& DynamicString::operator[]( uintreg index )
	{
		TIKI_ASSERT( index < m_length );
		return m_string[ index ];
	}

	const char& DynamicString::operator[]( uintreg index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_string[ index ];
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
		const uintreg stringLength = strlen( pString );

		checkCapacity( m_length + stringLength );
		memcpy( m_string + m_length, pString, stringLength );
		terminate( m_length + stringLength );

		return *this;
	}

	DynamicString& DynamicString::operator+=( const StringView& rhs )
	{
		checkCapacity( m_length + rhs.getLength() );
		memcpy( m_string + m_length, rhs.getData(), rhs.getLength() );
		terminate( m_length + rhs.getLength() );

		return *this;
	}

	DynamicString& DynamicString::operator+=( const DynamicString& rhs )
	{
		checkCapacity( m_length + rhs.m_length );
		memcpy( m_string + m_length, rhs.m_string, rhs.m_length );
		terminate( m_length + rhs.m_length );

		return *this;
	}

	DynamicString DynamicString::operator+( const char* pString ) const
	{
		const uintreg stringLength = strlen( pString );

		DynamicString result;
		result.checkCapacity( m_length + stringLength );
		memcpy( result.m_string, m_string, m_length );
		memcpy( result.m_string + m_length, pString, stringLength );
		result.terminate( m_length + stringLength );

		return result;
	}

	DynamicString DynamicString::operator+( const StringView& rhs ) const
	{
		DynamicString result;
		result.checkCapacity( m_length + rhs.getLength() );
		memcpy( result.m_string, m_string, m_length );
		memcpy( result.m_string + m_length, rhs.getData(), rhs.getLength() );
		result.terminate( m_length + rhs.getLength() );

		return result;
	}

	DynamicString DynamicString::operator+( const DynamicString& rhs ) const
	{
		DynamicString result;
		result.checkCapacity( m_length + rhs.m_length );
		memcpy( result.m_string, m_string, m_length );
		memcpy( result.m_string + m_length, rhs.m_string, rhs.m_length );
		result.terminate( m_length + rhs.m_length );

		return result;
	}

	bool DynamicString::operator==( const DynamicString& rhs ) const
	{
		if( m_length != rhs.m_length )
		{
			return false;
		}

		return strcmp( m_string, rhs.m_string ) == 0;
	}

	bool DynamicString::operator==( const char* pString ) const
	{
		return strcmp( m_string, pString ) == 0;
	}

	bool DynamicString::operator!=( const DynamicString& rhs ) const
	{
		return strcmp( m_string, rhs.m_string ) != 0;
	}

	bool DynamicString::operator!=( const char* pString ) const
	{
		return strcmp( m_string, pString ) != 0;
	}

	DynamicString::operator const char*() const
	{
		return m_string;
	}

	DynamicString::operator StringView() const
	{
		return StringView( m_string, m_length );
	}

	void DynamicString::checkCapacity( uintreg size )
	{
		const uintreg nextCapacity = getNextPowerOfTwo( size + 1u );
		if( nextCapacity < m_capacity )
		{
			return;
		}

		char* pNewString = new char[ nextCapacity ];
		TIKI_ASSERT( pNewString != nullptr );

		memcpy( pNewString, m_string, m_length );

		delete[] m_string;
		m_string = pNewString;
		m_capacity = nextCapacity;

		terminate( m_length );
	}

	DynamicString operator ""_s( const char* pString, uintreg length )
	{
		return DynamicString( pString, length );
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

		length = vsnprintf( result.m_string, result.m_capacity, format, args );
		if( length < 0 )
		{
			return DynamicString();
		}

		result.terminate( length );
		return result;
	}
}