#pragma once

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

	template< uintsize TLen >
	inline StringView::StringView( const char( &string )[ TLen ] )
		: ArrayView( string, TLen - 1u )
	{
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

		return strcmp( m_data, rhs ) == 0;
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

		return strcmp( m_data, rhs.m_data ) == 0;
	}

	inline bool StringView::operator!=( const char* rhs ) const
	{
		if( m_data == nullptr || rhs == nullptr )
		{
			return m_length != 0u && m_data != rhs;
		}

		return strcmp( m_data, rhs ) != 0;
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

		return strcmp( m_data, rhs.getData() ) != 0;
	}

	inline StringView::operator const char*() const
	{
		return m_data;
	}
}
