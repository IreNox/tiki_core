#pragma once

namespace tiki
{
	namespace ascii
	{
		inline bool	isAlphaNumeric( char c );
		inline bool	isLetter( char c );
		inline bool	isCapital( char c );
		inline bool	isMinuscule( char c );
		inline bool	isNumber( char c );
		inline bool	isSymbol( char c );

		inline bool	isWhitespace( char c );
		inline bool	isSpace( char c );
		inline bool	isTab( char c );
		inline bool	isNewLine( char c );

		inline char	toLower( char c );
		inline char	toUpper( char c );

		inline bool	isEqualsNoCase( char c1, char c2 );
	}
}

#include "tiki/../../src/tiki_ascii.inl"
