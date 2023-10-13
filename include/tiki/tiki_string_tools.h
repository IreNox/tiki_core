#pragma once

#include "tiki/tiki_types.h"
#include "tiki/tiki_dynamic_string.h"

namespace tiki
{
	namespace string_tools
	{
		DynamicString	toString( sint8 value );
		DynamicString	toString( sint16 value );
		DynamicString	toString( sint32 value );
		DynamicString	toString( sint64 value );
		DynamicString	toString( uint8 value );
		DynamicString	toString( uint16 value );
		DynamicString	toString( uint32 value );
		DynamicString	toString( uint64 value );
		DynamicString	toString( float value );
		DynamicString	toString( double value );

		DynamicString	toHexString( sint8 value );
		DynamicString	toHexString( sint16 value );
		DynamicString	toHexString( sint32 value );
		DynamicString	toHexString( sint64 value );
		DynamicString	toHexString( uint8 value );
		DynamicString	toHexString( uint16 value );
		DynamicString	toHexString( uint32 value );
		DynamicString	toHexString( uint64 value );
		DynamicString	toHexString( float value );
		DynamicString	toHexString( double value );

		sint8			parseSInt8( const StringView& string );
		sint16			parseSInt16( const StringView& string );
		sint32			parseSInt32( const StringView& string );
		sint64			parseSInt64( const StringView& string );

		uint8			parseUInt8( const StringView& string );
		uint16			parseUInt16( const StringView& string );
		uint32			parseUInt32( const StringView& string );
		uint64			parseUInt64( const StringView& string );

		uint8			parseHexNibble( const StringView& string );
		uint8			parseHexUInt8( const StringView& string );
		uint16			parseHexUInt16( const StringView& string );
		uint32			parseHexUInt32( const StringView& string );
		uint64			parseHexUInt64( const StringView& string );

		float			parseFloat( const StringView& string );
		double			parseDouble( const StringView& string );

		bool			tryParseSInt8( sint8& target, const StringView& string );
		bool			tryParseSInt16( sint16& target, const StringView& string );
		bool			tryParseSInt32( sint32& target, const StringView& string );
		bool			tryParseSInt64( sint64& target, const StringView& string );

		bool			tryParseUInt8( uint8& target, const StringView& string );
		bool			tryParseUInt16( uint16& target, const StringView& string );
		bool			tryParseUInt32( uint32& target, const StringView& string );
		bool			tryParseUInt64( uint64& target, const StringView& string );

		bool			tryParseHexNibble( uint8& target, const StringView& string );
		bool			tryParseHexUInt8( uint8& target, const StringView& string );
		bool			tryParseHexUInt16( uint16& target, const StringView& string );
		bool			tryParseHexUInt32( uint32& target, const StringView& string );
		bool			tryParseHexUInt64( uint64& target, const StringView& string );

		bool			tryParseFloat( float& target, const StringView& string );
		bool			tryParseDouble( double& target, const StringView& string );
	}
}
