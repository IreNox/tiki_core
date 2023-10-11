#pragma once

namespace tiki
{
	template< class T >
	ArrayView<T>::ArrayView()
	{
		set( nullptr, 0u );
	}

	template< class T >
	ArrayView< T >::ArrayView( const T* data, uintsize length )
	{
		set( data, length );
	}

	template< class T >
	void ArrayView<T>::set( const T* data, uintsize length )
	{
		m_data		= data;
		m_length	= length;
	}

	template< class T >
	const T* ArrayView<T>::getBegin() const
	{
		return m_data;
	}

	template< class T >
	const T* ArrayView<T>::getEnd() const
	{
		return m_data + m_length;
	}

	template< class T >
	const T& ArrayView<T>::getFront() const
	{
		TIKI_ASSERT( m_length > 0u );
		return m_data[ 0u ];
	}

	template< class T >
	const T& ArrayView<T>::getBack() const
	{
		TIKI_ASSERT( m_length > 0u );
		return m_data[ m_length - 1u ];
	}

	template< class T >
	const T& ArrayView< T >::operator[]( uintsize index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ index ];
	}
}
