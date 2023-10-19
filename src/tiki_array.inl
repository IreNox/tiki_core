#pragma once

namespace tiki
{
	template< class T >
	Array< T >::Array()
		: m_data( nullptr )
		, m_length( 0u )
	{
	}

	template< class T >
	Array< T >::Array( T* data, uintsize length )
		: m_data( data )
		, m_length( length )
	{
	}

	template< class T >
	T& Array< T >::getFront()
	{
		TIKI_ASSERT( m_length > 0u );
		return m_data[ 0u ];
	}

	template< class T >
	const T& Array< T >::getFront() const
	{
		TIKI_ASSERT( m_length > 0u );
		return m_data[ 0u ];
	}

	template< class T >
	T& Array< T >::getBack()
	{
		TIKI_ASSERT( m_length > 0u );
		return m_data[ m_length - 1u ];
	}

	template< class T >
	const T& Array< T >::getBack() const
	{
		TIKI_ASSERT( m_length > 0u );
		return m_data[ m_length - 1u ];
	}

	template< class T >
	T& Array< T >::getElement( uintsize index )
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ index ];
	}

	template< class T >
	const T& Array< T >::getElement( uintsize index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ index ];
	}

	template< class T >
	T& Array< T >::getReverseElement( uintsize index )
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ (m_length - 1u) - index ];
	}

	template< class T >
	const T& Array< T >::getReverseElement( uintsize index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ (m_length - 1u) - index ];
	}

	template< class T >
	Array< T > Array< T >::getRange( uintsize start )
	{
		if( start >= m_length )
		{
			return Array< T >();
		}

		return Array< T >( m_data + start, m_length - start );
	}

	template< class T >
	Array< T > Array< T >::getRange( uintsize start, uintsize length )
	{
		if( start >= m_length )
		{
			return Array< T >();
		}

		return Array< T >( m_data + start, min( length, m_length - start ) );
	}

	template< class T >
	ArrayView< T > Array< T >::getRangeView( uintsize start ) const
	{
		if( start >= m_length )
		{
			return ArrayView< T >();
		}

		return ArrayView< T >( m_data + start, m_length - start );
	}

	template< class T >
	ArrayView< T > Array< T >::getRangeView( uintsize start, uintsize length ) const
	{
		if( start >= m_length )
		{
			return ArrayView< T >();
		}

		return ArrayView< T >( m_data + start, min( length, m_length - start ) );
	}

	template< class T >
	template< typename T2 >
	inline Array< T2 > Array< T >::cast()
	{
		TIKI_ASSERT( isValueAligned( getSizeInBytes(), sizeof( T2 ) ) );
		return Array< T2 >( (T2*)m_data, getSizeInBytes() / sizeof( T2 ) );
	}

	template< class T >
	template< typename T2 >
	inline ArrayView< T2 > Array< T >::cast() const
	{
		return toView().cast< T2 >();
	}

	template< class T >
	ArrayView< T > Array< T >::toView() const
	{
		return ArrayView< T >( m_data, m_length );
	}

	template< class T >
	Array< T >::operator ArrayView< T >() const
	{
		return toView();
	}

	template< class T >
	T& Array< T >::operator[]( uintsize index )
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ index ];
	}

	template< class T >
	const T& Array< T >::operator[]( uintsize index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_data[ index ];
	}
}
