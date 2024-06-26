#pragma once

#include "tiki_functions.h"

namespace tiki
{
	inline uintreg getStringSize( const char* pSource )
	{
		if( pSource == nullptr )
		{
			return 0u;
		}

		uintreg length = 0u;
		while ( pSource[ ++length ] != '\0' );

		return length;
	}

	inline uintreg getStringLength( const char* pSource )
	{
		if( pSource == nullptr )
		{
			return 0u;
		}

		uintreg index = 0;
		uintreg length = 0;
		while ( pSource[ index ] != '\0' )
		{
			length += !(pSource[ index ] & 0x80); // wrong!
			index++;
		}

		return length;
	}

	inline uintreg copyString( char* pTargetBuffer, uintreg bufferSize, const char* pSourceBuffer )
	{
		TIKI_ASSERT( pTargetBuffer != nullptr );

		uintreg length = 0u;
		if ( pSourceBuffer != nullptr )
		{
			const uintreg sourceLength = min( bufferSize - 1u, getStringSize( pSourceBuffer ) );

			uint64* pTarget64 = reinterpret_cast< uint64* >( pTargetBuffer );
			const uint64* pSource64 = reinterpret_cast< const uint64* >( pSourceBuffer );

			while ( length < sourceLength )
			{
				if ( ( sourceLength -  length ) >= sizeof( uint64 ) )
				{
					const uintreg lengthOver = length / sizeof( uint64 );
					pTarget64[ lengthOver ] = pSource64[ lengthOver ];

					length += sizeof( uint64 );
				}
				else
				{
					pTargetBuffer[ length ] = pSourceBuffer[ length ];
					++length;
				}
			}
		}
		pTargetBuffer[ length ] = '\0';

		return length;
	}

	inline uintreg appendString( char* pTargetbuffer, uintreg bufferSize, const char* pSource )
	{
		const uintreg index = getStringSize( pTargetbuffer );
		return copyString( pTargetbuffer + index, bufferSize - index, pSource );
	}

	inline bool isStringEmpty( const char* pString )
	{
		return pString == nullptr || pString[ 0u ] == '\0';
	}

	inline bool isStringEquals( const char* pString1, const char* pString2 )
	{
		if( pString1 == pString2 )
		{
			return true;
		}
		else if( pString1 == nullptr && pString2 == nullptr )
		{
			return true;
		}
		else if( pString1 == nullptr )
		{
			return isStringEmpty( pString2 );
		}
		else if( pString2 == nullptr )
		{
			return isStringEmpty( pString1 );
		}

		uintreg index = 0u;
		while ( pString1[ index ] != '\0' && pString2[ index ] != '\0' )
		{
			if ( pString1[ index ] != pString2[ index ] )
			{
				return false;
			}

			index++;
		}

		return pString1[ index ] == '\0' && pString2[ index ] == '\0';
	}

	inline StringCompareResult compareStrings( const char* pString1, const char* pString2 )
	{
		while( *pString1 != '\0' && *pString2 != '\0' )
		{
			if( *pString1 < *pString2 )
			{
				return StringCompareResult::Lower;
			}
			else if( *pString1 > *pString2 )
			{
				return StringCompareResult::Greater;
			}

			pString1++;
			pString2++;
		}

		if( *pString1 == '\0' && *pString2 == '\0' )
		{
			return StringCompareResult::Equals;
		}

		return *pString1 == '\0' ? StringCompareResult::Lower : StringCompareResult::Greater;
	}

	inline bool doesStringStartWith( const char* pString, const char* pValue )
	{
		if( pString == nullptr || pValue == nullptr )
		{
			return false;
		}
		else if( pString == pValue )
		{
			return true;
		}

		const uintreg stringLength = getStringLength( pString );
		const uintreg valueLength = getStringLength( pValue );
		if( stringLength < valueLength )
		{
			return false;
		}

		for( uintreg i = 0u; i < valueLength; ++i )
		{
			if( pString[ i ] != pValue[ i ] )
			{
				return false;
			}
		}

		return true;
	}

	inline bool doesStringEndWith( const char* pString, const char* pValue )
	{
		if( pString == nullptr || pValue == nullptr )
		{
			return false;
		}
		else if( pString == pValue )
		{
			return true;
		}

		const uintreg stringLength = getStringLength( pString );
		const uintreg valueLength = getStringLength( pValue );
		if( stringLength < valueLength )
		{
			return false;
		}

		for( uintreg i = stringLength - valueLength; i < stringLength; ++i )
		{
			if( pString[ i ] != pValue[ i ] )
			{
				return false;
			}
		}

		return true;
	}

	inline void stringReplace( char* pString, char oldChar, char newChar )
	{
		const uintreg stringSize = getStringSize( pString );
		for( uintreg i = 0u; i < stringSize; ++i )
		{
			if( pString[ i ] == oldChar )
			{
				pString[ i ] = newChar;
			}
		}
	}

	inline uintreg stringIndexOf( const char* pString, char c, uintreg index /* = 0 */ )
	{
		uintreg i = index;
		while ( pString[ i ] != '\0' )
		{
			if ( pString[ i ] == c )
			{
				return i;
			}

			i++;
		}

		return InvalidStringIndex;
	}

	inline uintreg stringIndexOf( const char* pString, const char* pSearch, uintreg index /*= 0*/ )
	{
		const uintreg stringLength = getStringSize( pString );
		const uintreg searchLength = getStringSize( pSearch );

		if ( searchLength > stringLength )
		{
			return InvalidStringIndex;
		}

		uintreg stringFoundIndex = 0u;
		uintreg stringIndex = index;
		uintreg searchIndex = 0u;
		while ( pString[ stringIndex ] != '\0' )
		{
			if ( pString[ stringIndex ] == pSearch[ searchIndex ] )
			{
				if ( searchIndex == 0u )
				{
					stringFoundIndex = stringIndex;
				}

				searchIndex++;

				if ( searchIndex == searchLength )
				{
					return stringFoundIndex;
				}
			}
			else
			{
				if ( searchIndex > 0 )
				{
					stringIndex = stringFoundIndex + 1u;
				}

				searchIndex = 0u;
			}

			stringIndex++;
		}

		return InvalidStringIndex;
	}

	inline uintreg stringLastIndexOf( const char* pString, char c, uintreg index /*= CONCT_SIZE_T_MAX*/ )
	{
		const uintreg stringLength = getStringSize( pString );

		index = min( index, stringLength - 1 );
		while (index < stringLength)
		{
			if ( pString[ index ] == c )
			{
				return index;
			}

			index--;
		}

		return InvalidStringIndex;
	}

	inline uintreg stringLastIndexOf( const char* pString, const char* pSearch, uintreg index /*= CONCT_SIZE_T_MAX*/ )
	{
		const uintreg stringLength = getStringSize( pString );
		const uintreg searchLength = getStringSize( pSearch );

		const uintreg maxSearchIndex = searchLength - 1u;

		if ( searchLength > stringLength )
		{
			return InvalidStringIndex;
		}

		uintreg stringFoundIndex = 0u;
		uintreg stringIndex = min( index, stringLength - 1 );
		uintreg searchIndex = 0u;
		while ( index < stringLength )
		{
			if ( pString[ stringIndex ] == pSearch[ searchIndex ] )
			{
				if ( searchIndex == maxSearchIndex )
				{
					stringFoundIndex = stringIndex;
				}

				searchIndex--;

				if ( searchIndex == 0u )
				{
					return stringFoundIndex;
				}
			}
			else
			{
				if ( searchIndex < maxSearchIndex )
				{
					stringIndex = stringFoundIndex - 1u;
				}

				searchIndex = maxSearchIndex;
			}

			stringIndex--;
		}

		return InvalidStringIndex;
	}
}
