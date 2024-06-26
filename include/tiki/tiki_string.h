#pragma once

#include "tiki/tiki_types.h"

namespace tiki
{
	static const uintreg InvalidStringIndex = (uintreg)-1;

	enum class StringCompareResult : sint8
	{
		Lower	= -1,
		Equals	= 0,
		Greater	= 1
	};

	inline uintreg				getStringSize( const char* pSource );		///< returns the string size in bytes
	inline uintreg				getStringLength( const char* pSource );		///< returns the string length in chars(for UTF8)

	inline uintreg				copyString( char* pTargetBuffer, uintreg bufferSize, const char* pSource );
	inline uintreg				appendString( char* pTargetbuffer, uintreg bufferSize, const char* pSource );

	inline bool					isStringEmpty( const char* pString );
	inline bool					isStringEquals( const char* pString1, const char* pString2 );

	inline StringCompareResult	compareStrings( const char* pString1, const char* pString2 );

	inline bool					doesStringStartWith( const char* pString, const char* pValue );
	inline bool					doesStringEndWith( const char* pString, const char* pValue );

	inline void					stringReplace( char* pString, char oldChar, char newChar );

	inline uintreg				stringIndexOf( const char* pString, char c, uintreg index = 0 );
	inline uintreg				stringIndexOf( const char* pString, const char* pSearch, uintreg index = 0 );
	inline uintreg				stringLastIndexOf( const char* pString, char c, uintreg index = InvalidStringIndex );
	inline uintreg				stringLastIndexOf( const char* pString, const char* pSearch, uintreg index = InvalidStringIndex );
}

#include "../../src/tiki_string.inl"
