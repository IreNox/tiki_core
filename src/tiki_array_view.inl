#pragma once

namespace tiki
{
	template< class T >
	inline ArrayView< T >::ArrayView()
	{
		set( nullptr, 0u );
	}

	template< class T >
	inline ArrayView< T >::ArrayView( T* data, uintsize length )
	{
		set( data, length );
	}

	template< class T >
	inline ArrayView< T >::ArrayView( const std::initializer_list< T >& initList )
	{
		set( initList.begin(), initList.size() );
	}

	template< class T >
	inline void ArrayView< T >::set( T* data, uintsize length )
	{
		m_data		= data;
		m_length	= length;
	}

	template< class T >
	inline T& ArrayView< T >::getFront()
	{
		TIKI_ASSERT( m_length > 0u );
		return m_data[ 0u ];
	}

	template< class T >
	inline const T& ArrayView< T >::getFront() const
	{
		TIKI_ASSERT( m_length > 0u );
		return m_data[ 0u ];
	}

	template< class T >
	inline T& ArrayView< T >::getBack()
	{
		TIKI_ASSERT( m_length > 0u );
		return m_data[ m_length - 1u ];
	}

	template< class T >
	inline const T& ArrayView< T >::getBack() const
	{
		TIKI_ASSERT( m_length > 0u );
		return m_data[ m_length - 1u ];
	}

	template< class T >
	T& ArrayView< T >::getElement( uintsize index )
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ index ];
	}

	template< class T >
	const T& ArrayView< T >::getElement( uintsize index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ index ];
	}

	template< class T >
	T& ArrayView< T >::getReverseElement( uintsize index )
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ (m_length - 1u) - index ];
	}

	template< class T >
	const T& ArrayView< T >::getReverseElement( uintsize index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ (m_length - 1u) - index ];
	}

	template< class T >
	ArrayView< T > ArrayView< T >::getRange( uintsize start ) const
	{
		if( start >= m_length )
		{
			return ArrayView< T >();
		}

		return ArrayView< T >( m_data + start, m_length - start );
	}

	template< class T >
	ArrayView< T > ArrayView< T >::getRange( uintsize start, uintsize length ) const
	{
		if( start >= m_length )
		{
			return ArrayView< T >();
		}

		return ArrayView< T >( m_data + start, min( length, m_length - start ) );
	}

	template< class T >
	template< typename T2 >
	inline ArrayView< T2 > ArrayView< T >::cast()
	{
		TIKI_ASSERT( isValueAligned( getSizeInBytes(), sizeof( T2 ) ) );
		return ArrayView< T2 >( (T2*)m_data, getSizeInBytes() / sizeof( T2 ) );
	}

	template< class T >
	template< typename T2 >
	inline ArrayView< const T2 > ArrayView< T >::cast() const
	{
		TIKI_ASSERT( isValueAligned( getSizeInBytes(), sizeof( T2 ) ) );
		return ConstArrayView< T2 >( (T2*)m_data, getSizeInBytes() / sizeof( T2 ) );
	}

	template< class T >
	inline ArrayView< T >::operator ArrayView< const T >() const
	{
		return ArrayView< const T >( m_data, m_length );
	}

	template< class T >
	inline T& ArrayView< T >::operator[]( uintsize index )
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ index ];
	}

	template< class T >
	inline const T& ArrayView< T >::operator[]( uintsize index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ index ];
	}
}
