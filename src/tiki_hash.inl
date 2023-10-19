#pragma once

#include "tiki/tiki_hash.h"

namespace tiki
{
	template< typename T > inline TikiHash32 calculateValueHash( const T& value )
	{
		return calculateHash( &value, sizeof( value ), 0u );
	}

	template< typename T >
	inline TikiHash32 calculateValueHash( const T* ptr )
	{
		const uintsize ptrInt = (uintsize)ptr;
#if TIKI_ENABLED( TIKI_POINTER_16 )
		return  TikiHash32( ptrInt >> 1u );
#elif TIKI_ENABLED( TIKI_POINTER_32 )
		return  TikiHash32( ptrInt >> 2u );
#elif TIKI_ENABLED( TIKI_POINTER_64 )
		return  TikiHash32( ptrInt >> 3u );
#else
		return  TikiHash32( ptrInt );
#endif
	}

	inline TikiHash32 calculateHash( const void* data, uintsize dataSize, TikiHash32 seed )
	{
		// Murmur3
		uint32 hash = seed;
		uint32_t dataPart;
		const uint8* bytes = (const uint8*)data;
		for( size_t i = dataSize >> 2; i; --i )
		{
			dataPart = *(uint32*)bytes;
			bytes += sizeof( uint32 );

			uint32 scramble = dataPart * 0xcc9e2d51;
			scramble = (scramble << 15) | (scramble >> 17);
			scramble *= 0x1b873593;

			hash ^= scramble;
			hash = (hash << 13) | (hash >> 19);
			hash = hash * 5 + 0xe6546b64;
		}

		dataPart = 0;
		for( size_t i = dataSize & 3; i; --i )
		{
			dataPart <<= 8;
			dataPart |= bytes[ i - 1 ];
		}

		uint32 scramble = dataPart * 0xcc9e2d51;
		scramble = (scramble << 15) | (scramble >> 17);
		scramble *= 0x1b873593;

		hash ^= scramble;
		hash ^= dataSize;
		hash ^= hash >> 16u;
		hash *= 0x85ebca6b;
		hash ^= hash >> 13u;
		hash *= 0xc2b2ae35;
		hash ^= hash >> 16u;

		return hash;
	}
}