#pragma once

#include "tiki/tiki_types.h"
#include "tiki/tiki_array.h"

namespace tiki
{
	template< typename T >
	using SortIsLessFunc = bool (*)( const T& lhs, const T& rhs );

	namespace sort
	{
		template< typename T >
		void quickSort( T* data, uintsize length );

		template< typename T >
		void quickSort( T* data, uintsize length, SortIsLessFunc< T > isLessFunc );

		template< typename T >
		void quickSort( Array< T >& data );

		template< typename T >
		void quickSort( Array< T >& data, SortIsLessFunc< T > isLessFunc );
	}
}

#include "tiki/../../src/tiki_sort.inl"
