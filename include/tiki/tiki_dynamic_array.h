#pragma once

#include "tiki_array.h"
#include "tiki_functions.h"

#include <initializer_list>

namespace tiki
{
	template< class T >
	class DynamicArray : public Array< T >
	{
	public:

						DynamicArray();
						DynamicArray( const DynamicArray& rhs );
						DynamicArray( const std::initializer_list< T >& initList );
						~DynamicArray();

		uintsize		getCapacity() const;

		void			clear();
		void			reserve( uintsize capacity );
		void			setLengthValue( uintsize size, T value );
		void			setLengthUninitialized( uintsize size );

		T&				insert( uintsize index );
		void			insert( const T& value, uintsize index );

		T&				pushBack();
		T&				pushBack( const T& value );
		void			pushRange( const DynamicArray< T >& vector );
		void			pushRange( const ArrayView< T >& arrayView );
		void			pushRange( const T* pData, uintsize length );

		void			popBack();

		void			eraseSorted( const T& value );
		void			eraseSorted( const T* pValue );
		void			eraseSortedByIndex( uintsize index );
		void			eraseUnsorted( const T& value );
		void			eraseUnsorted( const T* pValue );
		void			eraseUnsortedByIndex( uintsize index );

		DynamicArray&	operator=( const DynamicArray& rhs );

	protected:

		uintsize		m_capacity;

		void			checkCapacity( uintsize capacity );
	};
}

#include "tiki/../../src/tiki_dynamic_array.inl"
