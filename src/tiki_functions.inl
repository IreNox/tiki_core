#pragma once

#include "tiki/tiki_number_limits.h"

#if TIKI_ENABLED( TIKI_COMPILER_MSVC ) && TIKI_ENABLED( TIKI_REGISTER_64 )
#	include <intrin.h>
#endif

namespace tiki
{
	template< typename T >
	inline T min( T a, T b )
	{
		return a < b ? a : b;
	}

	template< typename T >
	inline T max( T a, T b )
	{
		return a > b ? a : b;
	}

	template< typename T >
	inline T clamp( T value, T min, T max )
	{
		return value < min ? min : value > max ? max : value;
	}

	template< typename T >
	inline T lerp( T min, T max, float t )
	{
		const T diff = max - min;
		return min + T( t * diff );
	}


	inline bool isBitSet32( uint32 bitMask, uint32 flag )
	{
		return (bitMask & flag) == flag;
	}

	inline bool isBitSet64( uint64 bitMask, uint64 flag )
	{
		return (bitMask & flag) == flag;
	}

	template< typename T >
	inline bool isPowerOfTwo( T x )
	{
		return (x & (x - 1)) == 0;
	}

	template< typename T >
	inline T getNextPowerOfTwo( T value )
	{
		const T shift = (T)(64u - countLeadingZeros64( value - 1 ));
		return T( 1 ) << shift;
	}

	template< typename T >
	inline T alignValue( T value, T alignment )
	{
		TIKI_ASSERT( alignment > 0 );
		TIKI_ASSERT( isPowerOfTwo( alignment ) );
		return (value + alignment - 1) & (0 - alignment);
	}

	template< typename T >
	inline bool isValueAligned( T value, T alignment )
	{
		return (value % alignment) == 0;
	}

	template< typename T >
	inline T* addPointer( T* pPtr, uintsize byteCountToAdd )
	{
		return static_cast<T*>((void*)((uint8*)pPtr + byteCountToAdd));
	}

	template< typename T >
	inline const T* addPointer( const T* pPtr, uintsize byteCountToAdd )
	{
		return static_cast<const T*>((const void*)((const uint8*)pPtr + byteCountToAdd));
	}

	template< typename T >
	inline T* addPointerCast( void* pPtr, uintsize byteCountToAdd )
	{
		return static_cast<T*>(static_cast<void*>(static_cast<uint8*>(pPtr) + byteCountToAdd));
	}

	template< typename T >
	inline const T* addPointerCast( const void* pPtr, uintsize byteCountToAdd )
	{
		return static_cast<const T*>(static_cast<const void*>(static_cast<const uint8*>(pPtr) + byteCountToAdd));
	}

	template< typename T >
	inline T* alignPointer( T* pPtr, uintsize alignment )
	{
		return ( T* )alignValue< uintsize >( uintptr( pPtr ), alignment );
	}

	template< typename T >
	inline const T* alignPointer( const T* pPtr, uintsize alignment )
	{
		return ( const T* )alignValue< uintsize >( uintptr( pPtr ), alignment );
	}

	inline bool isPointerAligned( const void* value, uintsize alignment )
	{
		return (uintptr( value ) % alignment) == 0;
	}

	inline uintsize countPopulation32( uint32 value )
	{
#if TIKI_ENABLED( TIKI_COMPILER_GCC ) || TIKI_ENABLED( TIKI_COMPILER_CLANG )
		return (uintsize)__builtin_popcount( value )
#elif TIKI_ENABLED( TIKI_COMPILER_MSVC )
		return __popcnt( value );
#else
		uint32 i = value - ((value >> 1) & 0x55555555);
		i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
		i = (i + (i >> 4)) & 0x0f0f0f0f;
		i *= 0x01010101;
		return  i >> 24;
#endif
	}

	inline uintsize countPopulation64( uint64 value )
	{
#if TIKI_ENABLED( TIKI_COMPILER_GCC ) || TIKI_ENABLED( TIKI_COMPILER_CLANG )
		return (uintsize)__builtin_popcountll( value )
#elif TIKI_ENABLED( TIKI_COMPILER_MSVC )
		return __popcnt64( value );
#else
		uint64 w1 = (value & 0x2222222222222222) + ((value + value) & 0x2222222222222222);
		uint64 w2 = (value >> 1 & 0x2222222222222222) + (value >> 2 & 0x2222222222222222);
		w1 = (w1 + (w1 >> 4)) & 0x0f0f0f0f0f0f0f0f;
		w2 = (w2 + (w2 >> 4)) & 0x0f0f0f0f0f0f0f0f;
		return (w1 + w2) * 0x0101010101010101 >> 57;
#endif
	}

	inline uintsize countLeadingZeros32( uint32 value )
	{
#if TIKI_ENABLED( TIKI_COMPILER_GCC ) || TIKI_ENABLED( TIKI_COMPILER_CLANG )
		return __builtin_clz( value );
#elif TIKI_ENABLED( TIKI_COMPILER_MSVC )
		unsigned long result = 0u;
		if( _BitScanReverse( &result, value ) )
		{
			return 31u - result;
		}
		else
		{
			return 32u;
		}
#else
		uint32 x = value;
		x |= (x >> 1);
		x |= (x >> 2);
		x |= (x >> 4);
		x |= (x >> 8);
		x |= (x >> 16);
		return 32u - countPopulation32( x );
#endif
	}

	inline uintsize countLeadingZeros64( uint64 value )
	{
#if TIKI_ENABLED( TIKI_COMPILER_GCC ) || TIKI_ENABLED( TIKI_COMPILER_CLANG )
		return __builtin_clzll( value );
#elif TIKI_ENABLED( TIKI_COMPILER_MSVC ) && TIKI_ENABLED( TIKI_REGISTER_64 )
		unsigned long result = 0u;
		if( _BitScanReverse64( &result, value ) )
		{
			return 63u - result;
		}
		else
		{
			return 64u;
		}
#else
		uint64 x = value;
		x |= ( x >> 1 );
		x |= ( x >> 2 );
		x |= ( x >> 4 );
		x |= ( x >> 8 );
		x |= ( x >> 16 );
		x |= ( x >> 32 );
		return 64u - countPopulation64( x );
#endif
	}

	template<>
	inline uintsize	countPopulation( uint8 value )
	{
		return countPopulation32( value );
	}

	template<>
	inline uintsize	countPopulation( uint16 value )
	{
		return countPopulation32( value );
	}

	template<>
	inline uintsize	countPopulation( uint32 value )
	{
		return countPopulation32( value );
	}

	template<>
	inline uintsize	countPopulation( uint64 value )
	{
		return countPopulation64( value );
	}

	template<>
	inline uintsize countLeadingZeros( uint32 value )
	{
		return countLeadingZeros32( value );
	}

	template<>
	inline uintsize countLeadingZeros( uint64 value )
	{
		return countLeadingZeros64( value );
	}

	template< typename T >
	inline void swap( T& value1, T& value2 )
	{
		T backup = value1;
		value1 = value2;
		value2 = backup;
	}

	template<typename TTarget, typename TSource>
	inline bool rangeCheckCast( TTarget& outValue, const TSource& value )
	{
		if( NumberLimits< TSource >::isSigned() && !NumberLimits< TTarget >::isSigned() && value < 0 )
		{
			return false;
		}

		if( value < ( TSource )NumberLimits< TTarget >::lowest() )
		{
			return false;
		}
		else if( value > ( TSource )NumberLimits< TTarget >::max() )
		{
			return false;
		}

		outValue = ( TTarget )value;
		return true;
	}
}
