#pragma once

#include "tiki/tiki_array_view.h"

namespace tiki
{
	class StringView : public ArrayView< char >
	{
	public:

		inline 			StringView();
		inline explicit	StringView( const char* cstring );
		inline 			StringView( const char* string, uintsize length );
		template< uintsize TLen >
		inline 			StringView( const char (&string)[ TLen ] );

		inline bool		operator==( const char* rhs ) const;
		inline bool		operator==( const StringView& rhs ) const;
		inline bool		operator!=( const char* rhs ) const;
		inline bool		operator!=( const StringView& rhs ) const;

		inline operator	const char*() const;
	};
}

#include "tiki/../../src/tiki_string_view.inl"