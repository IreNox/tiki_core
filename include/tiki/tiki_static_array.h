#pragma once

#include "tiki/tiki_array_view.h"

#include <initializer_list>

namespace tiki
{
	template< class T, uintsize TSize >
	class StaticArray
	{
	public:

		inline						StaticArray();
		inline						StaticArray( const std::initializer_list< T >& initList );

		inline uintsize				getLength() const;

		inline T*					getData();
		inline const T*				getData() const;

		inline T*					getBegin();
		inline const T*				getBegin() const;
		inline T*					getEnd();
		inline const T*				getEnd() const;

		inline T&					getFront();
		inline const T&				getFront() const;
		inline T&					getBack();
		inline const T&				getBack() const;

		inline T&					getElement( uintsize index );
		inline const T&				getElement( uintsize index ) const;
		inline T&					getReverseElement( uintsize index );
		inline const T&				getReverseElement( uintsize index ) const;

		inline ArrayView< T >		toView();
		inline ConstArrayView< T >	toView() const;

		inline operator				ArrayView< T >();
		inline operator				ConstArrayView< T >() const;

		inline T&					operator[]( uintsize index );
		inline const T&				operator[]( uintsize index ) const;

	private:

		T							m_data[ TSize ];
	};

	template< class T, uintsize TSize > inline T* begin( StaticArray< T, TSize >& arr ) { return arr.getBegin(); }
	template< class T, uintsize TSize > inline T* end( StaticArray< T, TSize >& arr ) { return arr.getEnd(); }
	template< class T, uintsize TSize > inline const T* begin( const StaticArray< T, TSize >& arr ) { return arr.getBegin(); }
	template< class T, uintsize TSize > inline const T* end( const StaticArray< T, TSize >& arr ) { return arr.getEnd(); }
}

#include "tiki/../../src/tiki_static_array.inl"
