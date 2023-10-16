#pragma once

#include "tiki/tiki_array_view.h"

namespace tiki
{
	class StringView : public ArrayView< char >
	{
	public:

		inline 				StringView();
		inline explicit		StringView( const char* cstring );
		inline 				StringView( const char* string, uintsize length );
		template< uintsize TLen >
		inline 				StringView( const char (&string)[ TLen ] );

		inline uintsize		indexOf( char c, uintsize index = 0u ) const;
		inline uintsize		indexOf( const StringView& str, uintsize index = 0u ) const;
		inline uintsize		lastIndexOf( char c, uintsize index = InvalidIndex ) const;
		inline uintsize		lastIndexOf( const StringView& str, uintsize index = InvalidIndex ) const;

		inline bool			contains( const StringView& str ) const;
		inline bool			startsWith( const StringView& str ) const;
		inline bool			startsWithNoCase( const StringView& str ) const;
		inline bool			endsWith( const StringView& str ) const;
		inline bool			endsWithNoCase( const StringView& str ) const;

		inline uintsize		countSubstring( const StringView& substr ) const;

		inline StringView	trim() const;

		inline StringView	subString( uintsize startIndex ) const;
		inline StringView	subString( uintsize startIndex, uintsize length ) const;

		const char*			toConstCharPointer() const;

		inline bool			operator==( const char* rhs ) const;
		inline bool			operator==( const StringView& rhs ) const;
		inline bool			operator!=( const char* rhs ) const;
		inline bool			operator!=( const StringView& rhs ) const;

		inline operator		const char*() const;
	};
}

#include "tiki/../../src/tiki_string_view.inl"