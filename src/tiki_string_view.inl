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

	inline bool StringView::operator==( const char* rhs ) const
	{
		return strcmp( m_data, rhs ) == 0;
	}

	inline bool StringView::operator==( const StringView& rhs ) const
	{
		if( m_length != rhs.m_length )
		{
			return false;
		}

		return strcmp( m_data, rhs.m_data ) == 0;
	}

	inline bool StringView::operator!=( const char* rhs ) const
	{
		return strcmp( m_data, rhs ) != 0;
	}

	inline bool StringView::operator!=( const StringView& rhs ) const
	{
		if( m_length != rhs.m_length )
		{
			return true;
		}

		return strcmp( m_data, rhs.m_data ) != 0;
	}

	inline StringView::operator const char*() const
	{
		return m_data;
	}
}
