#pragma once

#include "tiki/tiki_number_limits.h"

namespace tiki
{
	template< typename T > inline T			min( T a, T b );
	template< typename T > inline T			max( T a, T b );
	template< typename T > inline T			clamp( T value, T min, T max );
	template< typename T > inline T			lerp( T min, T max, float t );

	inline bool								isBitSet32( uint32 bitMask, uint32 flag );
	inline bool								isBitSet64( uint64 bitMask, uint64 flag );

	template< typename T > inline bool		isPowerOfTwo( T x );
	template< typename T > inline T			getNextPowerOfTwo( T value );
	template< typename T > inline T			alignValue( T value, T alignment );
	template< typename T > inline bool		isValueAligned( T value, T alignment );

	template< typename T > inline T*		addPointer( T* pPtr, uintsize byteCountToAdd );
	template< typename T > inline const T*	addPointer( const T* pPtr, uintsize byteCountToAdd );
	template< typename T > inline T*		addPointerCast( void* pPtr, uintsize byteCountToAdd );
	template< typename T > inline const T*	addPointerCast( const void* pPtr, uintsize byteCountToAdd );
	template< typename T > inline T*		alignPointer( T* pPtr, uintsize alignment );
	template< typename T > inline const T*	alignPointer( const T* pPtr, uintsize alignment );
	inline bool								isPointerAligned( const void* value, uintsize alignment );

	inline uintsize							countPopulation32( uint32 value );
	inline uintsize							countPopulation64( uint64 value );
	inline uintsize							countLeadingZeros32( uint32 value );
	inline uintsize							countLeadingZeros64( uint64 value );

	template< typename T > inline uintsize	countPopulation( T value );
	template< typename T > inline uintsize	countLeadingZeros( T value );

	template< typename T > inline void		swap( T& value1, T& value2 );

	template< typename TTarget, typename TSource >
	inline bool		rangeCheckCast( TTarget& outValue, const TSource& value );
}

#include "tiki/../../src/tiki_functions.inl"
