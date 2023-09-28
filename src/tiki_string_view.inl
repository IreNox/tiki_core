#pragma once

#include <cstring>

namespace tiki
{
	TIKI_FORCE_INLINE StringView::StringView()
		: ArrayView()
	{
	}

	TIKI_FORCE_INLINE StringView::StringView( const char* cstring )
		: ArrayView( cstring, strlen( cstring ) )
	{
	}

	TIKI_FORCE_INLINE StringView::StringView( const char* string, uintsize length )
		: ArrayView( string, length )
	{
	}

	template< uintsize TLen >
	TIKI_FORCE_INLINE StringView::StringView( const char( &string )[ TLen ] )
		: ArrayView( string, TLen )
	{
	}
}
