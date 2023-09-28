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

		uintreg			getCapacity() const;

		void			clear();
		void			reserve( uintreg capacity );
		void			setLengthValue( uintreg size, T value );
		void			setLengthUninitialized( uintreg size );

		T&				insert( uintreg index );
		void			insert( const T& value, uintreg index );

		T&				pushBack();
		void			pushBack( const T& value );
		void			pushRange( const DynamicArray< T >& vector );
		void			pushRange( const ArrayView< T >& arrayView );
		void			pushRange( const T* pData, uintreg length );

		void			popBack();

		void			eraseSorted( const T& value );
		void			eraseSorted( const T* pValue );
		void			eraseSortedByIndex( uintreg index );
		void			eraseUnsorted( const T& value );
		void			eraseUnsorted( const T* pValue );
		void			eraseUnsortedByIndex( uintreg index );

		DynamicArray&	operator=( const DynamicArray& rhs );

	private:

		uintreg			m_capacity;

		void			checkCapacity( uintreg capacity );
	};
}

#include "tiki/../../src/tiki_dynamic_array.inl"