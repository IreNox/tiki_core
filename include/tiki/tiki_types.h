#pragma once

#include "tiki/tiki_defines.h"

#include <stdint.h>

namespace tiki
{
	using uint8		= uint8_t;
	using sint8		= int8_t;
	using uint16	= uint16_t;
	using sint16	= int16_t;
	using uint32	= uint32_t;
	using sint32	= int32_t;
	using uint64	= uint64_t;
	using sint64	= int64_t;

	TIKI_STATIC_ASSERT( sizeof( uint8 ) == 1u );
	TIKI_STATIC_ASSERT( sizeof( sint8 ) == 1u );
	TIKI_STATIC_ASSERT( sizeof( uint16 ) == 2u );
	TIKI_STATIC_ASSERT( sizeof( sint16 ) == 2u );
	TIKI_STATIC_ASSERT( sizeof( uint32 ) == 4u );
	TIKI_STATIC_ASSERT( sizeof( sint32 ) == 4u );
	TIKI_STATIC_ASSERT( sizeof( uint64 ) == 8u );
	TIKI_STATIC_ASSERT( sizeof( sint64 ) == 8u );

	using sint	= int;
	using uint	= unsigned;
	using byte	= uint8;

	using TikiHash32	= uint32;
	using TikiHash64	= uint64;

#if TIKI_ENABLED( TIKI_POINTER_16 )
	using uintptr	= uint16;
	TIKI_STATIC_ASSERT( sizeof( void* ) == 2u );
#elif TIKI_ENABLED( TIKI_POINTER_32 )
	using uintptr	= uint32;
	TIKI_STATIC_ASSERT( sizeof( void* ) == 4u );
#elif TIKI_ENABLED( TIKI_POINTER_64 )
	using uintptr	= uint64;
	TIKI_STATIC_ASSERT( sizeof( void* ) == 8u );
#else
#	error "No Pointer size"
#endif

#if TIKI_ENABLED( TIKI_REGISTER_8 )
	using uintreg	= uint8;
	using uintsize	= uint8;
	using sintsize	= sint8;
#elif TIKI_ENABLED( TIKI_REGISTER_16 )
	using uintreg	= uint16;
	using uintsize	= uint16;
	using sintsize	= sint16;
#elif TIKI_ENABLED( TIKI_REGISTER_32 )
	using uintreg	= uint32;
	using uintsize	= uint32;
	using sintsize	= sint32;
#elif TIKI_ENABLED( TIKI_REGISTER_64 )
	using uintreg	= uint64;
	using uintsize	= uint64;
	using sintsize	= sint64;
#else
#	error "No Register size"
#endif

	static const uintsize InvalidIndex = (uintsize)-1;
}
