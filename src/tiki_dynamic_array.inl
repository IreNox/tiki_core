#pragma once

namespace tiki
{
	template< class T >
	DynamicArray< T >::DynamicArray()
		: m_capacity( 0u )
	{
	}

	template< class T >
	DynamicArray< T >::DynamicArray( const DynamicArray& rhs )
		: Array< T >()
		, m_capacity( 0u )
	{
		*this = rhs;
	}

	template< class T >
	DynamicArray< T >::DynamicArray( const std::initializer_list< T >& initList )
		: m_capacity( 0u )
	{
		pushRange( initList.begin(), initList.size() );
	}

	template< class T >
	DynamicArray< T >::~DynamicArray()
	{
		delete[] this->m_data;
	}

	template< class T >
	uintsize DynamicArray< T >::getCapacity() const
	{
		return m_capacity;
	}

	template< class T >
	void DynamicArray< T >::clear()
	{
		this->m_length = 0u;
	}

	template< class T >
	void DynamicArray< T >::reserve( uintsize capacity )
	{
		checkCapacity( capacity );
	}

	template< class T >
	void DynamicArray< T >::setLengthValue( uintsize size, T value )
	{
		checkCapacity( size );

		for( uintsize i = this->m_length; i < size; ++i )
		{
			this->m_data[ i ] = value;
		}

		this->m_length = size;
	}

	template< class T >
	void DynamicArray<T>::setLengthUninitialized( uintsize size )
	{
		checkCapacity( size );
		this->m_length = size;
	}

	template< class T >
	T& DynamicArray< T >::insert( uintsize index )
	{
		TIKI_ASSERT( index <= this->m_length );
		checkCapacity( this->m_length + 1u );

		if( index < this->m_length )
		{
			for( uintsize i = this->m_length; i > index; --i )
			{
				this->m_pData[ i ] = this->m_pData[ i - 1u ];
			}
		}

		this->m_length++;

		return this->m_pData[ index ];
	}

	template< class T >
	void DynamicArray< T >::insert( const T& value, uintsize index )
	{
		T& target = insert( index );
		target = value;
	}

	template< class T >
	T& DynamicArray< T >::pushBack()
	{
		checkCapacity( this->m_length + 1u );
		return this->m_data[ this->m_length++ ];
	}

	template< class T >
	void DynamicArray< T >::pushBack( const T& value )
	{
		checkCapacity( this->m_length + 1u );
		this->m_data[ this->m_length++ ] = value;
	}

	template< class T >
	void DynamicArray< T >::pushRange( const DynamicArray< T >& vector )
	{
		pushRange( vector.getData(), vector.getLength() );
	}

	template< class T >
	void DynamicArray< T >::pushRange( const ArrayView< T >& arrayView )
	{
		pushRange( arrayView.getData(), arrayView.getLength() );
	}

	template< class T >
	void DynamicArray< T >::pushRange( const T* pData, uintsize length )
	{
		checkCapacity( this->m_length + length );
		for( uintsize i = 0u; i < length; ++i )
		{
			this->m_data[ this->m_length++ ] = pData[ i ];
		}
	}

	template< class T >
	void DynamicArray< T >::popBack()
	{
		TIKI_ASSERT( this->m_length > 0u );
		this->m_length--;
	}

	template< class T >
	void DynamicArray< T >::eraseSorted( const T& value )
	{
		eraseSorted( &value );
	}

	template< class T >
	void DynamicArray< T >::eraseSorted( const T* pValue )
	{
		TIKI_ASSERT( pValue >= this->m_pData && pValue < this->m_pData + this->m_length );
		eraseSortedByIndex( pValue - this->m_pData );
	}

	template< class T >
	void DynamicArray< T >::eraseSortedByIndex( uintsize index )
	{
		this->m_length--;
		for( uintsize i = index; i < this->m_length; ++i )
		{
			this->m_pData[ i ] = this->m_pData[ i + 1u ];
		}
	}

	template< class T >
	void DynamicArray< T >::eraseUnsorted( const T& value )
	{
		eraseUnsorted( &value );
	}

	template< class T >
	void DynamicArray< T >::eraseUnsorted( const T* pValue )
	{
		TIKI_ASSERT( pValue >= this->m_pData && pValue < this->m_pData + this->m_length );
		eraseUnsortedByIndex( pValue - this->m_pData );
	}

	template< class T >
	void DynamicArray< T >::eraseUnsortedByIndex( uintsize index )
	{
		this->m_length--;
		if( index != this->m_length )
		{
			this->m_pData[ index ] = this->m_pData[ this->m_length ];
		}
	}

	template< class T >
	DynamicArray< T >& DynamicArray< T >::operator=( const DynamicArray& rhs )
	{
		clear();
		pushRange( rhs.getData(), rhs.getLength() );
		return *this;
	}

	template< class T >
	void DynamicArray< T >::checkCapacity( uintsize capacity )
	{
		const uintsize nextCapacity = getNextPowerOfTwo( capacity );
		if( nextCapacity <= m_capacity )
		{
			return;
		}

		T* pNewData = new T[ nextCapacity ];
		TIKI_ASSERT( pNewData != nullptr );

		for( uintsize i = 0u; i < this->m_length; ++i )
		{
			pNewData[ i ] = this->m_data[ i ];
		}

		delete[] this->m_data;
		this->m_data = pNewData;
		m_capacity = nextCapacity;
	}
}
