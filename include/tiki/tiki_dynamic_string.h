#pragma once

#include "tiki/tiki_dynamic_array.h"

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
		explicit				DynamicString( const char* pString, uintreg stringLength );
								~DynamicString();

		void					assign( const char* string );
		void					assign( const char* string, size_t length );
		void					assign( const StringView& string );
		void					assign( const DynamicString& string );

		void					terminate( uintreg newLength );

		uintreg					indexOf( char c, uintreg index = 0u ) const;
		uintreg					indexOf( const StringView& str, uintreg index = 0u ) const;

		uintreg					lastIndexOf( char c, uintreg index = InvalidIndex ) const;
		uintreg					lastIndexOf( const StringView& str, uintreg index = InvalidIndex ) const;

		bool					contains( char c ) const;
		bool					contains( const StringView& str ) const;

		bool					startsWith( char c ) const;
		bool					startsWith( const StringView& str ) const;
		bool					startsWithNoCase( const StringView& str ) const;

		bool					endsWith( char c ) const;
		bool					endsWith( const StringView& str ) const;
		bool					endsWithNoCase( const StringView& str ) const;

		uintreg					countSubstring( const StringView& substr ) const;

		DynamicString			trim() const;
		DynamicString			toLower() const;
		DynamicString			toUpper() const;

		DynamicString			subString( uintreg startIndex ) const;
		DynamicString			subString( uintreg startIndex, uintreg length ) const;

		DynamicString			replace( char oldChar, char newChar ) const;
		DynamicString			replace( const DynamicString& oldString, const DynamicString& newString ) const;

		DynamicString			insert( char c, uintreg index ) const;
		DynamicString			erase( uintreg index ) const;

		DynamicString			popBack() const;
		DynamicString			pushBack( char c ) const;

		char*					beginWrite();
		void					endWrite( uintreg newLength = (uintreg)-1 );

		const char*				toConstCharPointer() const;

		char*					getBegin();
		const char*				getBegin() const;
		char*					getEnd();
		const char*				getEnd() const;

		char&					operator[]( uintreg index );
		const char&				operator[]( uintreg index ) const;

		DynamicString&			operator=( const char* rhs );
		DynamicString&			operator=( const StringView& rhs );
		DynamicString&			operator=( const DynamicString& rhs );

		bool					operator==( const char* pString ) const;
		bool					operator==( const DynamicString& rhs ) const;
		bool					operator!=( const char* pString ) const;
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

	DynamicString operator ""_s( const char* pString, uintreg length );
}
