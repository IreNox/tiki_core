#pragma once

namespace tiki
{
	template< class T, uintsize TSize >
	StaticArray< T, TSize >::StaticArray()
	{
		TIKI_STATIC_ASSERT( TSize > 0u );
	}

	template< class T, uintsize TSize >
	StaticArray< T, TSize >::StaticArray( const std::initializer_list< T >& initList )
	{
		TIKI_ASSERT( initList.size() <= TSize );

		const T* initValue = initList.begin();
		for( uintsize i = 0; i < initList.size(); ++i )
		{
			m_data[ i ] = initValue[ i ];
		}
	}

	template< class T, uintsize TSize >
	inline uintsize StaticArray< T, TSize >::getLength() const
	{
		return TSize;
	}

	template< class T, uintsize TSize >
	inline T* StaticArray< T, TSize >::getData()
	{
		return m_data;
	}

	template< class T, uintsize TSize >
	inline const T* StaticArray< T, TSize >::getData() const
	{
		return m_data;
	}

	template< class T, uintsize TSize >
	inline T* StaticArray< T, TSize >::getBegin()
	{
		return m_data;
	}

	template< class T, uintsize TSize >
	inline const T* StaticArray< T, TSize >::getBegin() const
	{
		return m_data;
	}

	template< class T, uintsize TSize >
	inline T* StaticArray< T, TSize >::getEnd()
	{
		return m_data + TSize;
	}

	template< class T, uintsize TSize >
	inline const T* StaticArray< T, TSize >::getEnd() const
	{
		return m_data + TSize;
	}

	template< class T, uintsize TSize >
	inline T& StaticArray< T, TSize >::getFront()
	{
		return m_data[ 0u ];
	}

	template< class T, uintsize TSize >
	inline const T& StaticArray< T, TSize >::getFront() const
	{
		return m_data[ 0u ];
	}

	template< class T, uintsize TSize >
	inline T& StaticArray< T, TSize >::getBack()
	{
		return m_data[ TSize - 1u ];
	}

	template< class T, uintsize TSize >
	inline const T& StaticArray< T, TSize >::getBack() const
	{
		return m_data[ TSize - 1u ];
	}

	template< class T, uintsize TSize >
	inline T& StaticArray<T, TSize>::getElement( uintsize index )
	{
		TIKI_ASSERT( index < TSize );
		return m_data[ index ];
	}

	template< class T, uintsize TSize >
	inline const T& StaticArray<T, TSize>::getElement( uintsize index ) const
	{
		TIKI_ASSERT( index < TSize );
		return m_data[ index ];
	}

	template< class T, uintsize TSize >
	inline T& StaticArray<T, TSize>::getReverseElement( uintsize index )
	{
		TIKI_ASSERT( index < m_length );
		return m_pData[ (m_length - 1u) - index ];
	}

	template< class T, uintsize TSize >
	inline const T& StaticArray<T, TSize>::getReverseElement( uintsize index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_pData[ (m_length - 1u) - index ];
	}

	template< class T, uintsize TSize >
	inline ArrayView< T > StaticArray< T, TSize >::toView() const
	{
		return ArrayView< T >( m_data, TSize );
	}

	template< class T, uintsize TSize >
	inline StaticArray< T, TSize >::operator ArrayView< T >() const
	{
		return toView();
	}

	template< class T, uintsize TSize >
	inline T& StaticArray< T, TSize >::operator[]( uintsize index )
	{
		TIKI_ASSERT( index < TSize);
		return m_data[ index ];
	}

	template< class T, uintsize TSize >
	inline const T& StaticArray< T, TSize >::operator[]( uintsize index ) const
	{
		TIKI_ASSERT( index < TSize);
		return m_data[ index ];
	}
}
