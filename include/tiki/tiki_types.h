#pragma once

#include "tiki/tiki_defines.h"

#include <stdint.h>

namespace tiki
{
	typedef uint8_t		uint8;
	typedef int8_t		sint8;
	typedef uint16_t	uint16;
	typedef int16_t		sint16;
	typedef uint32_t	uint32;
	typedef int32_t		sint32;
	typedef uint64_t	uint64;
	typedef int64_t		sint64;

	TIKI_STATIC_ASSERT( sizeof( uint8 ) == 1u );
	TIKI_STATIC_ASSERT( sizeof( sint8 ) == 1u );
	TIKI_STATIC_ASSERT( sizeof( uint16 ) == 2u );
	TIKI_STATIC_ASSERT( sizeof( sint16 ) == 2u );
	TIKI_STATIC_ASSERT( sizeof( uint32 ) == 4u );
	TIKI_STATIC_ASSERT( sizeof( sint32 ) == 4u );
	TIKI_STATIC_ASSERT( sizeof( uint64 ) == 8u );
	TIKI_STATIC_ASSERT( sizeof( sint64 ) == 8u );

	typedef int			sint;
	typedef unsigned	uint;

	typedef uint8		byte;

#if TIKI_ENABLED( TIKI_POINTER_16 )
	typedef uint16		uintptr;
	TIKI_STATIC_ASSERT( sizeof( void* ) == 2u );
#elif TIKI_ENABLED( TIKI_POINTER_32 )
	typedef uint32		uintptr;
	TIKI_STATIC_ASSERT( sizeof( void* ) == 4u );
#elif TIKI_ENABLED( TIKI_POINTER_64 )
	typedef uint64		uintptr;
	TIKI_STATIC_ASSERT( sizeof( void* ) == 8u );
#else
#	error "No Pointer size"
#endif

#if TIKI_ENABLED( TIKI_REGISTER_8 )
	typedef uint8		uintreg;
	typedef uint8		uintsize;
	typedef sint8		sintsize;
#elif TIKI_ENABLED( TIKI_REGISTER_16 )
	typedef uint16		uintreg;
	typedef uint16		uintsize;
	typedef sint16		sintsize;
#elif TIKI_ENABLED( TIKI_REGISTER_32 )
	typedef uint32		uintreg;
	typedef uint32		uintsize;
	typedef sint32		sintsize;
#elif TIKI_ENABLED( TIKI_REGISTER_64 )
	typedef uint64		uintreg;
	typedef uint64		uintsize;
	typedef sint64		sintsize;
#else
#	error "No Register size"
#endif

	static const uintreg InvalidIndex = (uintreg)-1;
}
