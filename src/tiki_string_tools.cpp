#include "tiki/tiki_string_tools.h"

#include "tiki/tiki_functions.h"

#include <stdio.h>
#include <cstdlib>
#include <math.h>

namespace tiki
{
	DynamicString string_tools::toString( sint8 value )
	{
		char buffer[ 64u ];
		snprintf( buffer, sizeof(buffer ), "%i", value );
		return DynamicString( buffer );
	}

	DynamicString string_tools::toString( sint16 value )
	{
		char buffer[ 64u ];
		snprintf( buffer, sizeof(buffer ), "%i", value );
		return DynamicString( buffer );
	}

	DynamicString string_tools::toString( sint32 value )
	{
		char buffer[ 64u ];
		snprintf( buffer, sizeof(buffer ), "%i", value );
		return DynamicString( buffer );
	}

	DynamicString string_tools::toString( sint64 value )
	{
		char buffer[ 64u ];
#	if TIKI_ENABLED( TIKI_POINTER_64 ) && TIKI_ENABLED( TIKI_PLATFORM_POSIX )
		snprintf( buffer, sizeof(buffer ), "%li", value );
#	elif TIKI_ENABLED( TIKI_POINTER_32 )
		snprintf( buffer, sizeof(buffer ), "%lli", value );
#	endif
		return DynamicString( buffer );
	}

	DynamicString string_tools::toString( uint8 value )
	{
		char buffer[ 64u ];
		snprintf( buffer, sizeof(buffer ), "%u", value );
		return DynamicString( buffer );
	}

	DynamicString string_tools::toString( uint16 value )
	{
		char buffer[ 64u ];
		snprintf( buffer, sizeof(buffer ), "%u", value );
		return DynamicString( buffer );
	}

	DynamicString string_tools::toString( uint32 value )
	{
		char buffer[ 64u ];
		const int length = snprintf( buffer, sizeof(buffer ), "%u", value );
		return DynamicString( buffer, (uintsize)length );
	}

	DynamicString string_tools::toString( uint64 value )
	{
		char buffer[ 64u ];
#if TIKI_ENABLED( TIKI_POINTER_32 ) || TIKI_ENABLED( TIKI_PLATFORM_WINDOWS )
		const int length = snprintf( buffer, sizeof(buffer ), "%llu", value );
#elif TIKI_ENABLED( TIKI_POINTER_64 )
		const int length = snprintf( buffer, sizeof(buffer ), "%lu", value );
#endif
		return DynamicString( buffer, (uintsize)length );
	}

	DynamicString string_tools::toString( float value )
	{
		char buffer[ 64u ];
		const int length = snprintf( buffer, sizeof(buffer ), "%f", value );

		uintreg index = (uintsize)length - 1;
		while( index > 0 )
		{
			if( buffer[ index - 1u ] == '.' || buffer[ index ] != '0' )
			{
				break;
			}
			else if( buffer[ index ] == '0' )
			{
				buffer[ index ] = '\0';
			}

			index--;
		}

		return DynamicString( buffer );
	}

	DynamicString string_tools::toString( double value )
	{
		char buffer[ 64u ];
		const int length = snprintf( buffer, sizeof(buffer ), "%f", value );

		uintreg index = (uintsize)length - 1u;
		while( index > 0 )
		{
			if( buffer[ index - 1u ] == '.' || buffer[ index ] != '0' )
			{
				break;
			}
			else if( buffer[ index ] == '0' )
			{
				buffer[ index ] = '\0';
			}

			index--;
		}

		return DynamicString( buffer );
	}

	DynamicString string_tools::toHexString( sint8 value )
	{
		char buffer[ 64u ];
		snprintf( buffer, sizeof(buffer ), "%02x", value );
		return DynamicString( buffer );
	}

	DynamicString string_tools::toHexString( sint16 value )
	{
		char buffer[ 64u ];
		snprintf( buffer, sizeof(buffer ), "%04x", value );
		return DynamicString( buffer );
	}

	DynamicString string_tools::toHexString( sint32 value )
	{
		char buffer[ 64u ];
		snprintf( buffer, sizeof(buffer ), "%08x", value );
		return DynamicString( buffer );
	}

	DynamicString string_tools::toHexString( sint64 value )
	{
		char buffer[ 64u ];
#	if TIKI_ENABLED( TIKI_POINTER_64 ) && TIKI_ENABLED( TIKI_PLATFORM_POSIX )
		snprintf( buffer, sizeof(buffer ), "%016lx", value );
#	elif TIKI_ENABLED( TIKI_POINTER_32 )
		snprintf( buffer, sizeof(buffer ), "%016llx", value );
#	endif
		return DynamicString( buffer );
	}

	DynamicString string_tools::toHexString( uint8 value )
	{
		char buffer[ 64u ];
		snprintf( buffer, sizeof(buffer ), "%02x", value );
		return DynamicString( buffer );
	}

	DynamicString string_tools::toHexString( uint16 value )
	{
		char buffer[ 64u ];
		snprintf( buffer, sizeof(buffer ), "%04x", value );
		return DynamicString( buffer );
	}

	DynamicString string_tools::toHexString( uint32 value )
	{
		char buffer[ 64u ];
		snprintf( buffer, sizeof(buffer ), "%08x", value );
		return DynamicString( buffer );
	}

	DynamicString string_tools::toHexString( uint64 value )
	{
		char buffer[ 64u ];
#	if TIKI_ENABLED( TIKI_POINTER_64 ) && TIKI_ENABLED( TIKI_PLATFORM_POSIX )
		snprintf( buffer, sizeof(buffer ), "%016lx", value );
#	elif TIKI_ENABLED( TIKI_POINTER_32 )
		snprintf( buffer, sizeof(buffer ), "%016llx", value );
#	endif
		return DynamicString( buffer );
	}

	DynamicString string_tools::toHexString( float value )
	{
		char buffer[ 64u ];
		snprintf( buffer, sizeof(buffer ), "%08x", *(uint32*)&value );
		return DynamicString( buffer );
	}

	DynamicString string_tools::toHexString( double value )
	{
		char buffer[ 64u ];
#	if TIKI_ENABLED( TIKI_POINTER_64 ) && TIKI_ENABLED( TIKI_PLATFORM_POSIX )
		snprintf( buffer, sizeof(buffer ), "%016lx", *(uint64*)&value );
#	elif TIKI_ENABLED( TIKI_POINTER_32 )
		snprintf( buffer, sizeof(buffer ), "%016llx", *(uint64*)&value );
#	endif
		return DynamicString( buffer );
	}

	sint8 string_tools::parseSInt8( const StringView& string )
	{
		return (sint8)atoi( string.getData() );
	}

	sint16 string_tools::parseSInt16( const StringView& string )
	{
		return (sint16)atoi( string.getData() );
	}

	sint32 string_tools::parseSInt32( const StringView& string )
	{
		return (sint32)atoi( string.getData() );
	}

	sint64 string_tools::parseSInt64( const StringView& string )
	{
		return (sint64)atoll( string.getData() );
	}

	uint8 string_tools::parseUInt8( const StringView& string )
	{
		return (uint8)atoi( string.getData() );
	}

	uint16 string_tools::parseUInt16( const StringView& string )
	{
		return (uint16)atoi( string.getData() );
	}

	uint32 string_tools::parseUInt32( const StringView& string )
	{
		return (uint32)atoi( string.getData() );
	}

	uint64 string_tools::parseUInt64( const StringView& string )
	{
		return (uint64)atoll( string.getData() );
	}

	uint8 string_tools::parseUInt8Hex( const StringView& string )
	{
		return (uint8)strtoll( string.getData(), nullptr, 16 );
	}

	uint16 string_tools::parseUInt16Hex( const StringView& string )
	{
		return (uint16)strtoll( string.getData(), nullptr, 16 );
	}

	uint32 string_tools::parseUInt32Hex( const StringView& string )
	{
		return (uint32)strtoll( string.getData(), nullptr, 16 );
	}

	uint64 string_tools::parseUInt64Hex( const StringView& string )
	{
		return (uint64)strtoll( string.getData(), nullptr, 16 );
	}

	float string_tools::parseFloat( const StringView& string )
	{
		return (float)atof( string.getData() );
	}

	double string_tools::parseDouble( const StringView& string )
	{
		return atof( string.getData() );
	}

	bool string_tools::tryParseSInt8( sint8& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const sint64 result = strtoll( string.getData(), &pEnd, 10 );
		if( pEnd == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseSInt16( sint16& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const sint64 result = strtoll( string.getData(), &pEnd, 10 );
		if( pEnd == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseSInt32( sint32& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const sint64 result = strtoll( string.getData(), &pEnd, 10 );
		if( pEnd == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseSInt64( sint64& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const sint64 result = strtoll( string.getData(), &pEnd, 10 );
		if( pEnd == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseUInt8( uint8& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const uint64 result = (uint64)strtoll( string.getData(), &pEnd, 10 );
		if( pEnd == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseUInt16( uint16& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const uint64 result = (uint64)strtoll( string.getData(), &pEnd, 10 );
		if( pEnd == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseUInt32( uint32& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const uint64 result = (uint64)strtoll( string.getData(), &pEnd, 10 );
		if( pEnd == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseUInt64( uint64& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const uint64 result = (uint64)strtoll( string.getData(), &pEnd, 10 );
		if( pEnd == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseUInt8Hex( uint8& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const uint64 result = (uint64)strtoll( string.getData(), &pEnd, 16 );
		if( pEnd == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseUInt16Hex( uint16& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const uint64 result = (uint64)strtoll( string.getData(), &pEnd, 16 );
		if( pEnd == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseUInt32Hex( uint32& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const uint64 result = (uint64)strtoll( string.getData(), &pEnd, 16 );
		if( pEnd == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseUInt64Hex( uint64& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const uint64 result = (uint64)strtoll( string.getData(), &pEnd, 16 );
		if( pEnd == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseFloat( float& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const double result = strtof( string.getData(), &pEnd );
		if( pEnd == string.getData() || pEnd == string.getData() )
		{
			return false;
		}

		target = (float)result;
		return true;
	}

	bool string_tools::tryParseDouble( double& target, const StringView& string )
	{
		char* pEnd = nullptr;
		const double result = strtof( string.getData(), &pEnd );
		if( pEnd == string.getData() || pEnd == string.getData() )
		{
			return false;
		}

		target = result;
		return true;
	}
}
