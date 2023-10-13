#include "tiki/tiki_string_tools.h"

#include "tiki/tiki_functions.h"

#include <stdio.h>
#include <cstdlib>
#include <math.h>

namespace tiki
{
	namespace string_tools
	{
		static bool parseHexNibbleInternal( uint8& target, char c );
		static bool parseHexInternal( uint64& target, const StringView& string, uintsize maxLength );
	}

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

	static bool string_tools::parseHexNibbleInternal( uint8& target, char c )
	{
		if( c >= '0' && c <= '9' )
		{
			target = c - '0';
			return true;
		}
		else if( c >= 'a' && c <= 'f' )
		{
			target = (c - 'a') + 10u;
			return true;
		}
		else if( c >= 'A' && c <= 'F' )
		{
			target = (c - 'A') + 10u;
			return true;
		}

		return false;
	}

	static bool string_tools::parseHexInternal( uint64& target, const StringView& string, uintsize maxLength )
	{
		target = 0u;

		uint8 nibble;
		const uintsize length = min( string.getLength(), maxLength );
		for( uintsize i = 0u; i < length; ++i )
		{
			if( !parseHexNibbleInternal( nibble, string[ i ] ) )
			{
				return false;
			}

			target <<= 4u;
			target += nibble;
		}

		return true;
	}

	uint8 string_tools::parseHexNibble( const StringView& string )
	{
		if( string.isEmpty() )
		{
			return 0u;
		}

		uint8 value = 0u;
		parseHexNibbleInternal( value, string[ 0u ] );
		return value;
	}

	uint8 string_tools::parseHexUInt8( const StringView& string )
	{
		uint64 value;
		parseHexInternal( value, string, 2u );
		return (uint8)value;
	}

	uint16 string_tools::parseHexUInt16( const StringView& string )
	{
		uint64 value;
		parseHexInternal( value, string, 4u );
		return (uint16)value;
	}

	uint32 string_tools::parseHexUInt32( const StringView& string )
	{
		uint64 value;
		parseHexInternal( value, string, 8u );
		return (uint32)value;
	}

	uint64 string_tools::parseHexUInt64( const StringView& string )
	{
		uint64 value;
		parseHexInternal( value, string, 16u );
		return value;
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
		char* end = nullptr;
		const sint64 result = strtoll( string.getData(), &end, 10 );
		if( end == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseSInt16( sint16& target, const StringView& string )
	{
		char* end = nullptr;
		const sint64 result = strtoll( string.getData(), &end, 10 );
		if( end == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseSInt32( sint32& target, const StringView& string )
	{
		char* end = nullptr;
		const sint64 result = strtoll( string.getData(), &end, 10 );
		if( end == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseSInt64( sint64& target, const StringView& string )
	{
		char* end = nullptr;
		const sint64 result = strtoll( string.getData(), &end, 10 );
		if( end == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseUInt8( uint8& target, const StringView& string )
	{
		char* end = nullptr;
		const uint64 result = (uint64)strtoll( string.getData(), &end, 10 );
		if( end == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseUInt16( uint16& target, const StringView& string )
	{
		char* end = nullptr;
		const uint64 result = (uint64)strtoll( string.getData(), &end, 10 );
		if( end == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseUInt32( uint32& target, const StringView& string )
	{
		char* end = nullptr;
		const uint64 result = (uint64)strtoll( string.getData(), &end, 10 );
		if( end == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseUInt64( uint64& target, const StringView& string )
	{
		char* end = nullptr;
		const uint64 result = (uint64)strtoll( string.getData(), &end, 10 );
		if( end == string.getData() || !rangeCheckCast( target, result ) )
		{
			return false;
		}

		return true;
	}

	bool string_tools::tryParseHexNibble( uint8& target, const StringView& string )
	{
		if( string.isEmpty() )
		{
			return false;
		}

		return parseHexNibbleInternal( target, string[ 0u ] );
	}

	bool string_tools::tryParseHexUInt8( uint8& target, const StringView& string )
	{
		uint64 result;
		if( !parseHexInternal( result, string, 2u ) )
		{
			return false;
		}

		target = (uint8)result;
		return true;
	}

	bool string_tools::tryParseHexUInt16( uint16& target, const StringView& string )
	{
		uint64 result;
		if( !parseHexInternal( result, string, 4u ) )
		{
			return false;
		}

		target = (uint16)result;
		return true;
	}

	bool string_tools::tryParseHexUInt32( uint32& target, const StringView& string )
	{
		uint64 result;
		if( !parseHexInternal( result, string, 8u ) )
		{
			return false;
		}

		target = (uint32)result;
		return true;
	}

	bool string_tools::tryParseHexUInt64( uint64& target, const StringView& string )
	{
		uint64 result;
		if( !parseHexInternal( result, string, 16u ) )
		{
			return false;
		}

		target = result;
		return true;
	}

	bool string_tools::tryParseFloat( float& target, const StringView& string )
	{
		char* end = nullptr;
		const double result = strtof( string.getData(), &end );
		if( end == string.getData() )
		{
			return false;
		}

		target = (float)result;
		return true;
	}

	bool string_tools::tryParseDouble( double& target, const StringView& string )
	{
		char* end = nullptr;
		const double result = strtof( string.getData(), &end );
		if( end == string.getData() )
		{
			return false;
		}

		target = result;
		return true;
	}
}
