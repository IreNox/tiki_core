#pragma once

#include <tiki/tiki_types.h>

namespace tiki
{
	template< typename T > inline TikiHash32	calculateValueHash( const T& value );
	template< typename T > inline TikiHash32	calculateValueHash( const T* ptr );

	inline TikiHash32							calculateHash( const void* data, uintsize dataSize, TikiHash32 seed );
}

#include "tiki/../../src/tiki_hash.inl"
