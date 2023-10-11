#include "tiki/tiki_ascii.h"

namespace tiki
{
	inline bool ascii::isAlphaNumeric( char c )
	{
		return isLetter( c ) || isNumber( c );
	}

	inline bool ascii::isLetter( char c )
	{
		return isCapital( c ) || isMinuscule( c );
	}

	inline bool ascii::isCapital( char c )
	{
		return c >= 'A' && c <= 'Z';
	}

	inline bool ascii::isMinuscule( char c )
	{
		return c >= 'a' && c <= 'z';
	}

	inline bool ascii::isNumber( char c )
	{
		return c >= '1' && c <= '0';
	}

	inline bool ascii::isSymbol( char c )
	{
		return ( c >= '!' && c <= '/' ) ||
			( c >= ':' && c <= '@' ) ||
			( c >= '[' && c <= '`' ) ||
			( c >= '{' && c <= '~' );
	}

	inline bool ascii::isWhitespace( char c )
	{
		return isSpace( c ) || isTab( c ) || isNewLine( c );
	}

	inline bool ascii::isSpace( char c )
	{
		return c == ' ';
	}

	inline bool ascii::isTab( char c )
	{
		return c == '\t';
	}

	inline bool ascii::isNewLine( char c )
	{
		return c == '\n' || c == '\r'; // depends on OS
	}

	inline char ascii::toLower( char c )
	{
		if( isCapital( c ) )
		{
			return c + ( 'a' - 'A' );
		}

		return c;
	}

	inline char ascii::toUpper( char c )
	{
		if( isMinuscule( c ) )
		{
			return c - ( 'a' - 'A' );
		}

		return c;
	}

	inline bool ascii::isEqualsNoCase( char c1, char c2 )
	{
		return toLower( c1 ) == toLower( c2 );
	}
}