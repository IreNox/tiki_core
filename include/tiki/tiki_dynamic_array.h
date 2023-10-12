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
								DynamicArray( const ArrayView< T >& rhs );
								DynamicArray( const std::initializer_list< T >& initList );
								~DynamicArray();

		inline uintsize			getCapacity() const;

		inline void				clear();
		inline void				reserve( uintsize capacity );
		inline void				setLengthValue( uintsize size, T value );
		inline void				setLengthUninitialized( uintsize size );

		inline T&				insert( uintsize index );
		inline void				insert( const T& value, uintsize index );

		inline T&				pushBack();
		inline T&				pushBack( const T& value );
		inline void				pushRange( const ArrayView< T >& arrayView );
		inline void				pushRange( const T* pData, uintsize length );

		inline void				popBack();

		inline void				eraseSorted( const T& value );
		inline void				eraseSorted( const T* pValue );
		inline void				eraseSortedByIndex( uintsize index );
		inline void				eraseUnsorted( const T& value );
		inline void				eraseUnsorted( const T* pValue );
		inline void				eraseUnsortedByIndex( uintsize index );

		inline DynamicArray&	operator=( const DynamicArray& rhs );

	protected:

		uintsize				m_capacity = 0u;

		void					checkCapacity( uintsize capacity );
	};
}

#include "tiki/../../src/tiki_dynamic_array.inl"
