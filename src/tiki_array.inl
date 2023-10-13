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
