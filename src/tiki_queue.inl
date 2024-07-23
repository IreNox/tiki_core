#pragma once

#include "tiki/tiki_functions.h"

namespace tiki
{
	template< class T >
	Queue< T >::Queue()
		: m_data( nullptr ), m_top( 0u ), m_bottom( 0u ), m_length( 0u ), m_capacity( 0u )
	{
	}

	template< class T >
	Queue< T >::Queue( const Queue& rhs )
		: m_data( nullptr ), m_top( 0u ), m_bottom( 0u ), m_length( 0u ), m_capacity( 0u )
	{
		*this = rhs;
	}

	template< class T >
	Queue< T >::Queue( const std::initializer_list< T >& initList )
		: m_data( nullptr ), m_top( 0u ), m_bottom( 0u ), m_length( 0u ), m_capacity( 0u )
	{
		pushRange( initList.begin(), initList.size() );
	}

	template< class T >
	Queue< T >::~Queue()
	{
		delete[] m_data;
	}

	template< class T >
	bool Queue< T >::isEmpty() const
	{
		return m_length == 0u;
	}

	template< class T >
	uintsize Queue< T >::getLength() const
	{
		return m_length;
	}

	template< class T >
	uintsize Queue< T >::getCapacity() const
	{
		return m_capacity;
	}

	template< class T >
	void Queue<T>::clear()
	{
		m_top		= 0u;
		m_bottom	= 0u;
		m_length	= 0u;
	}

	template< class T >
	void Queue< T >::reserve( uintsize size )
	{
		checkCapacity( size );
	}

	template< class T >
	T& Queue< T >::pushBack()
	{
		checkCapacity( m_length + 1u );

		const uintsize index = m_bottom;
		m_bottom = ( m_bottom + 1u ) % m_capacity;
		m_length++;
		return m_data[ index ];
	}

	template< class T >
	void Queue< T >::pushBack( const T& value )
	{
		checkCapacity( m_length + 1u );

		const uintsize index = m_bottom;
		m_bottom = ( m_bottom + 1u ) % m_capacity;
		m_length++;
		m_data[ index ] = value;
	}

	template< class T >
	void Queue<T>::pushRange( const Queue< T >& vector )
	{
		pushRange( vector.getData(), vector.getLength() );
	}

	template< class T >
	void Queue<T>::pushRange( const ArrayView< T >& arrayView )
	{
		pushRange( arrayView.getData(), arrayView.getLength() );
	}

	template< class T >
	void Queue<T>::pushRange( const T* pData, uintsize length )
	{
		checkCapacity( m_length + length );
		for( uintsize i = 0u; i < length; ++i )
		{
			const uintsize index = m_bottom;
			m_bottom = ( m_bottom + 1u ) % m_capacity;
			m_data[ index ] = pData[ i ];
		}
		m_length += length;
	}

	template< class T >
	void Queue< T >::popFront()
	{
		TIKI_ASSERT( m_length > 0u );
		m_top = ( m_top + 1u ) % m_capacity;
		m_length--;
	}

	template< class T >
	bool Queue<T>::tryPopFront( T& target )
	{
		if( isEmpty() )
		{
			return false;
		}

		target = m_data[ m_top ];
		m_top = ( m_top + 1u ) % m_capacity;
		m_length--;
		return true;
	}

	template< class T >
	T& Queue<T>::getFront()
	{
		TIKI_ASSERT( m_length > 0u );
		return m_data[ m_top ];
	}

	template< class T >
	const T& Queue<T>::getFront() const
	{
		TIKI_ASSERT( m_length > 0u );
		return m_data[ m_top ];
	}

	template< class T >
	T& Queue<T>::operator[]( uintsize index )
	{
		const uintsize queueIndex = (m_top + index) % m_capacity;
		return m_data[ queueIndex ];
	}

	template< class T >
	const T& Queue<T>::operator[]( uintsize index ) const
	{
		const uintsize queueIndex = (m_top + index) % m_capacity;
		return m_data[ queueIndex ];
	}

	template< class T >
	Queue< T >& Queue< T >::operator=( const Queue& rhs )
	{
		clear();
		checkCapacity( rhs.m_length );

		for( uintsize i = 0u; i < rhs.m_length; ++i )
		{
			m_data[ i ] = rhs[ i ];
		}

		m_top		= 0u;
		m_bottom	= rhs.m_length;
		m_length	= rhs.m_length;

		return *this;
	}

	template< class T >
	void Queue< T >::checkCapacity( uintsize capacity )
	{
		const uintsize nextCapacity = getNextPowerOfTwo( capacity );
		if( nextCapacity <= m_capacity )
		{
			return;
		}

		T* pNewData = new T[ nextCapacity ];
		TIKI_ASSERT( pNewData != nullptr );

		for( uintsize i = 0u; i < m_length; ++i )
		{
			pNewData[ i ] = (*this)[ i ];
		}

		delete[] m_data;
		m_data = pNewData;
		m_top = 0u;
		m_bottom = m_length;
		m_capacity = nextCapacity;
	}
}
