#pragma once

#include "tiki/tiki_dynamic_array.h"

#include "tiki/tiki_hash.h"
#include "tiki/tiki_string_view.h"

namespace tiki
{
	class DynamicString : public DynamicArray< char >
	{
	public:

								DynamicString();
								DynamicString( const StringView& string );
								DynamicString( const DynamicString& string );
		explicit				DynamicString( const char* pString );
		explicit				DynamicString( const char* pString, uintsize stringLength );
								~DynamicString();

		void					assign( const char* string );
		void					assign( const char* string, size_t length );
		void					assign( const StringView& string );
		void					assign( const DynamicString& string );

		void					terminate( uintsize newLength );

		uintsize				indexOf( char c, uintsize index = 0u ) const;
		uintsize				indexOf( const StringView& str, uintsize index = 0u ) const;
		uintsize				lastIndexOf( char c, uintsize index = InvalidIndex ) const;
		uintsize				lastIndexOf( const StringView& str, uintsize index = InvalidIndex ) const;

		bool					contains( char c ) const;
		bool					contains( const StringView& str ) const;

		bool					startsWith( char c ) const;
		bool					startsWith( const StringView& str ) const;
		bool					startsWithNoCase( const StringView& str ) const;

		bool					endsWith( char c ) const;
		bool					endsWith( const StringView& str ) const;
		bool					endsWithNoCase( const StringView& str ) const;

		uintsize				countSubstring( const StringView& substr ) const;

		DynamicString			trim() const;
		DynamicString			toLower() const;
		DynamicString			toUpper() const;

		DynamicString			subString( uintsize startIndex ) const;
		DynamicString			subString( uintsize startIndex, uintsize length ) const;

		DynamicString			replace( char oldChar, char newChar ) const;
		DynamicString			replace( const DynamicString& oldString, const DynamicString& newString ) const;

		DynamicString			insert( char c, uintsize index ) const;
		DynamicString			erase( uintsize index ) const;

		DynamicString			popBack() const;
		DynamicString			pushBack( char c ) const;

		char*					beginWrite( uintsize minCapacity = 0u );
		void					endWrite( uintsize newLength = (uintsize)-1 );

		const char*				toConstCharPointer() const;

		DynamicString&			operator=( const char* rhs );
		DynamicString&			operator=( const StringView& rhs );
		DynamicString&			operator=( const DynamicString& rhs );

		bool					operator==( const char* pString ) const;
		bool					operator==( const StringView& rhs ) const;
		bool					operator==( const DynamicString& rhs ) const;
		bool					operator!=( const char* pString ) const;
		bool					operator!=( const StringView& rhs ) const;
		bool					operator!=( const DynamicString& rhs ) const;

		DynamicString&			operator+=( const char* pString );
		DynamicString&			operator+=( const StringView& rhs );
		DynamicString&			operator+=( const DynamicString& rhs );

		DynamicString			operator+( const char* pString ) const;
		DynamicString			operator+( const StringView& rhs ) const;
		DynamicString			operator+( const DynamicString& rhs ) const;

		operator				const char*() const;
		operator				StringView() const;

		static DynamicString	format( const char* format, ... );
		static DynamicString	formatArgs( const char* format, va_list args );
	};

	DynamicString				operator+( const char* lhs, const DynamicString& rhs );

	DynamicString operator ""_s( const char* pString, uintsize length );

	template<>
	TikiHash32 calculateValueHash( const DynamicString& value );
}
