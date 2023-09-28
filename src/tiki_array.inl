#pragma once

namespace tiki
{
	template< class T >
	Array< T >::Array()
		: m_pData( nullptr )
		, m_length( 0u )
	{
	}

	template< class T >
	Array< T >::Array( T* pData, uintreg length )
		: m_pData( pData )
		, m_length( length )
	{
	}

	template< class T >
	T& Array< T >::getFront()
	{
		TIKI_ASSERT( m_length > 0u );
		return m_pData[ 0u ];
	}

	template< class T >
	const T& Array< T >::getFront() const
	{
		TIKI_ASSERT( m_length > 0u );
		return m_pData[ 0u ];
	}

	template< class T >
	T& Array< T >::getBack()
	{
		TIKI_ASSERT( m_length > 0u );
		return m_pData[ m_length - 1u ];
	}

	template< class T >
	const T& Array< T >::getBack() const
	{
		TIKI_ASSERT( m_length > 0u );
		return m_pData[ m_length - 1u ];
	}

	template< class T >
	ArrayView< T > Array< T >::toView() const
	{
		return ArrayView< T >( m_pData, m_length );
	}

	template< class T >
	T& Array< T >::getElement( uintreg index )
	{
		TIKI_ASSERT( index < m_length );
		return m_pData[ index ];
	}

	template< class T >
	const T& Array< T >::getElement( uintreg index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_pData[ index ];
	}

	template< class T >
	T& Array< T >::getReverseElement( uintreg index )
	{
		TIKI_ASSERT( index < m_length );
		return m_pData[ (m_length - 1u) - index ];
	}

	template< class T >
	const T& Array< T >::getReverseElement( uintreg index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_pData[ (m_length - 1u) - index ];
	}

	template< class T >
	T& Array< T >::operator[]( uintreg index )
	{
		TIKI_ASSERT( index < m_length );
		return m_pData[ index ];
	}

	template< class T >
	const T& Array< T >::operator[]( uintreg index ) const
	{
		TIKI_ASSERT( index < m_length );
		return m_pData[ index ];
	}
}
