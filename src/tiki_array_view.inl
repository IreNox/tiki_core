#pragma once

namespace tiki
{
	template< class T >
	ArrayView<T>::ArrayView()
	{
		set( nullptr, 0u );
	}

	template< class T >
	ArrayView< T >::ArrayView( const T* pData, uintsize length )
	{
		set( pData, length );
	}

	template< class T >
	void ArrayView<T>::set( const T* pData, uintsize length )
	{
		m_data		= pData;
		m_length	= length;
	}

	template< class T >
	const T* ArrayView<T>::getBegin() const
	{
		return m_pData;
	}

	template< class T >
	const T* ArrayView<T>::getEnd() const
	{
		return m_pData + m_length;
	}

	template< class T >
	const T& ArrayView<T>::getFront() const
	{
		TIKI_ASSERT( m_length > 0u );
		return m_pData[ 0u ];
	}

	template< class T >
	const T& ArrayView<T>::getBack() const
	{
		TIKI_ASSERT( m_length > 0u );
		return m_pData[ m_length - 1u ];
	}

	template< class T >
	const T& ArrayView< T >::operator[]( uintsize index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_pData[ index ];
	}
}
