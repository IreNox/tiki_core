#pragma once

#include "tiki/tiki_functions.h"

namespace tiki
{
	namespace sort
	{
		template< typename T >
		static uintsize	partition( T* data, uintsize left, uintsize right, SortIsLessFunc< T > isLessFunc );

		template<typename T>
		static void		quickSortRange( T* pData, uintsize left, uintsize right, SortIsLessFunc< T > isLessFunc );
	}


	template< typename T >
	void sort::quickSort( T* data, uintsize length )
	{
		quickSortRange( data, 0u, length - 1u, []( const T& lhs, const T& rhs ){ return lhs < rhs; } );
	}

	template< typename T >
	void sort::quickSort( T* data, uintsize length, SortIsLessFunc< T > isLessFunc )
	{
		quickSortRange( data, 0u, length - 1u, isLessFunc );
	}

	template< typename T >
	void sort::quickSort( Array< T >& data )
	{
		quickSortRange( data.getData(), 0u, data.getLength() - 1u, []( const T& lhs, const T& rhs ){ return lhs < rhs; } );
	}

	template< typename T >
	void sort::quickSort( Array< T >& data, SortIsLessFunc< T > isLessFunc )
	{
		quickSortRange( data.getData(), 0u, data.getLength() - 1u, isLessFunc );
	}

	template< typename T >
	static uintsize	sort::partition( T* data, uintsize left, uintsize right, SortIsLessFunc< T > isLessFunc )
	{
		const T pivot = data[ right ];

		uintsize i = left - 1u;
		for( uintsize j = left; j <= right; ++j )
		{
			if( !isLessFunc( data[ j ], pivot ) )
			{
				continue;
			}

			i++;
			swap( data[ i ], data[ j ] );
		}

		swap( data[ i + 1u ], data[ right ] );
		return i + 1u;
	}

	template< typename T >
	static void sort::quickSortRange( T* data, uintsize left, uintsize right, SortIsLessFunc< T > isLessFunc )
	{
		if( left >= right )
		{
			return;
		}

		const uintsize partitionIndex = partition( data, left, right, isLessFunc );

		quickSortRange( data, left, partitionIndex - 1u, isLessFunc );
		quickSortRange( data, partitionIndex + 1u, right, isLessFunc );
	}
}
