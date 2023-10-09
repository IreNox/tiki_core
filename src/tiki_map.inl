#pragma once

#include "tiki/tiki_functions.h"

namespace tiki
{
	template< class TKey, class TValue >
	Map< TKey, TValue >::Map()
		: m_pData( nullptr ), m_length( 0u ), m_capacity( 0u )
	{
	}

	template< class TKey, class TValue >
	Map< TKey, TValue >::Map( const Map& rhs )
		: m_pData( nullptr ), m_length( 0u ), m_capacity( 0u )
	{
		*this = rhs;
	}

	template< class TKey, class TValue >
	Map< TKey, TValue >::Map( const std::initializer_list< Pair >& initList )
		: m_pData( nullptr ), m_length( 0u ), m_capacity( 0u )
	{
		for( const PairType& pair : initList )
		{
			insert( pair.key, pair.value );
		}
	}

	template< class TKey, class TValue >
	Map< TKey, TValue >::~Map()
	{
		delete[] m_pData;
	}

	template< class TKey, class TValue >
	bool Map< TKey, TValue >::isEmpty() const
	{
		return m_length == 0u;
	}

	template< class TKey, class TValue >
	uintsize Map< TKey, TValue >::getLength() const
	{
		return m_length;
	}

	template< class TKey, class TValue >
	uintsize Map< TKey, TValue >::getCapacity() const
	{
		return m_capacity;
	}

	template< class TKey, class TValue >
	void Map< TKey, TValue >::clear()
	{
		m_length = 0u;
	}

	template< class TKey, class TValue >
	void Map< TKey, TValue >::reserve( uintsize size )
	{
		checkCapacity( size );
	}

	template< class TKey, class TValue >
	bool Map<TKey, TValue>::hasKey( const TKey& key ) const
	{
		return findIndex( key ) != (uintsize)-1;
	}

	template< class TKey, class TValue >
	TValue* Map<TKey, TValue>::find( const TKey& key )
	{
		const uintsize index = findIndex( key );
		if( index == (uintsize)-1 )
		{
			return nullptr;
		}

		return &m_pData[ index ].value;
	}

	template< class TKey, class TValue >
	const TValue* Map<TKey, TValue>::find( const TKey& key ) const
	{
		const uintsize index = findIndex( key );
		if( index == (uintsize)-1 )
		{
			return nullptr;
		}

		return &m_pData[ index ].value;
	}

	template< class TKey, class TValue >
	bool Map<TKey, TValue>::findAndCopy( TValue& target, const TKey& key ) const
	{
		const uintsize index = findIndex( key );
		if( index == ( uintsize )-1 )
		{
			return false;
		}

		target = m_pData[ index ].value;
		return true;
	}

	template< typename TKey, typename TValue >
	typename Map< TKey, TValue >::InsertResult Map< TKey, TValue >::insertKey( const TKey& key )
	{
		const uintsize pos = findPositionIndex( key );

		PairType& pair1 = m_pData[ pos ];
		if( pos < m_length && pair1.key == key )
		{
			InsertResult result;
			result.isNew	= false;
			result.pValue	= &pair1.value;
			return result;
		}

		checkCapacity( m_length + 1 );

		for( uintsize i = m_length; i > pos; --i )
		{
			m_pData[ i ] = m_pData[ i - 1 ];
		}

		PairType& pair2 = m_pData[ pos ];
		pair2.key	= key;
		pair2.value	= TValue();
		m_length++;

		InsertResult result;
		result.isNew	= true;
		result.pValue	= &pair2.value;
		return result;
	}

	template< class TKey, class TValue >
	void Map<TKey, TValue>::insert( const TKey& key, const TValue& value )
	{
		const InsertResult result = insertKey( key );
		*result.pValue = value;
	}

	template< class TKey, class TValue >
	bool Map< TKey, TValue >::remove( const TKey& key )
	{
		const uintsize index = findIndex( key );
		if( index == ( uintsize )-1 )
		{
			return false;
		}

		m_length--;
		for( uintsize i = index; i < m_length; ++i )
		{
			m_pData[ i ] = m_pData[ i + 1u ];
		}

		return true;
	}

	template< class TKey, class TValue >
	typename Map< TKey, TValue >::Pair* Map< TKey, TValue >::getData()
	{
		return m_pData;
	}

	template< class TKey, class TValue >
	const typename Map< TKey, TValue >::Pair* Map< TKey, TValue >::getData() const
	{
		return m_pData;
	}

	template< class TKey, class TValue >
	typename Map< TKey, TValue >::Pair* Map< TKey, TValue >::getBegin()
	{
		return m_pData;
	}

	template< class TKey, class TValue >
	const typename Map< TKey, TValue >::Pair* Map< TKey, TValue >::getBegin() const
	{
		return m_pData;
	}

	template< class TKey, class TValue >
	typename Map< TKey, TValue >::Pair* Map< TKey, TValue >::getEnd()
	{
		return m_pData + m_length;
	}

	template< class TKey, class TValue >
	const typename Map< TKey, TValue >::Pair* Map< TKey, TValue >::getEnd() const
	{
		return m_pData + m_length;
	}


	template< class TKey, class TValue >
	Array< typename Map< TKey, TValue >::Pair > Map< TKey, TValue >::toArray() const
	{
		return Array< Pair >( m_pData, m_length );
	}

	template< class TKey, class TValue >
	ArrayView< typename Map< TKey, TValue >::Pair > Map< TKey, TValue >::toView() const
	{
		return ArrayView< Pair >( m_pData, m_length );
	}

	template< class TKey, class TValue >
	Map< TKey, TValue >& Map< TKey, TValue >::operator=( const Map& rhs )
	{
		clear();
		checkCapacity( rhs.m_length );
		m_length = rhs.m_length;
		for( uintsize i = 0u; i < m_length; ++i )
		{
			m_pData[ i ] = rhs.m_pData[ i ];
		}
		return *this;
	}

	template< class TKey, class TValue >
	TValue& Map< TKey, TValue >::operator[]( const TKey& key )
	{
		const InsertResult result = insertKey( key );
		return *result.pValue;
	}

	template< class TKey, class TValue >
	const TValue& Map< TKey, TValue >::operator[]( const TKey& key ) const
	{
		const uintsize index = findIndex( key );
		if( index == (uintsize)-1 )
		{
			static TValue emptyValue = TValue();
			return emptyValue;
		}

		return m_pData[ index ].value;
	}

	template<typename TKey, typename TValue>
	uintsize Map< TKey, TValue >::findIndex( const TKey& key ) const
	{
		if( m_length == 0u )
		{
			return (uintsize)-1;
		}

		int imin = 0u;
		int imax = int( m_length );
		while( imax >= imin )
		{
			const int imid =  (imax + imin) / 2u;
			if( imid < 0 || imid >= (int)m_length )
			{
				return (uintsize)-1;
			}

			if( m_pData[ imid ].key == key )
			{
				return imid;
			}
			else if( m_pData[ imid ].key < key )
			{
				imin = imid + 1;
			}
			else
			{
				imax = imid - 1;
			}
		}

		return (uintsize)-1;
	}

	template<typename TKey, typename TValue>
	uintsize Map< TKey, TValue >::findPositionIndex( const TKey& key ) const
	{
		if( m_length == 0u )
		{
			return m_length;
		}

		int rangeStart = 0;
		int rangeEnd = int( m_length );
		while( rangeEnd >= rangeStart && rangeStart < int( m_length ) )
		{
			const int rangeMid =  rangeStart + ((rangeEnd - rangeStart) / 2);
			const PairType& kvp = m_pData[ rangeMid ];

			if( kvp.key == key )
			{
				return rangeMid;
			}
			else if( key < kvp.key )
			{
				rangeEnd = rangeMid - 1;
			}
			else
			{
				rangeStart = rangeMid + 1;
			}
		}

		return uintsize( rangeStart );
	}

	template<typename TKey, typename TValue>
	uintsize Map< TKey, TValue >::getNextCapacity( uintsize neededCapacity )
	{
		uintsize capacity = TIKI_MAX( 2u, m_capacity );
		while( capacity <= neededCapacity )
		{
			capacity *= 2;
		}

		return capacity;
	}

	template<typename TKey, typename TValue>
	void Map< TKey, TValue >::checkCapacity( uintsize neededCapacity )
	{
		if( m_capacity >= neededCapacity )
		{
			return;
		}

		const uintsize capacity = getNextCapacity( neededCapacity );
		PairType* pNewData = new PairType[ capacity ];

		for( uintsize i = 0u; i < m_length; ++i )
		{
			pNewData[ i ] = m_pData[ i ];
		}

		if( m_pData != nullptr )
		{
			delete[] m_pData;
		}

		m_pData		= pNewData;
		m_capacity	= capacity;
	}
}
