#pragma once

#include "tiki/tiki_functions.h"

namespace tiki
{
	template< class TKey, class TValue >
	inline SortedMap< TKey, TValue >::SortedMap()
	{
	}

	template< class TKey, class TValue >
	inline SortedMap< TKey, TValue >::SortedMap( const SortedMap& rhs )
	{
		*this = rhs;
	}

	template< class TKey, class TValue >
	inline SortedMap< TKey, TValue >::SortedMap( const std::initializer_list< Pair >& initList )
	{
		for( const PairType& pair : initList )
		{
			insert( pair.key, pair.value );
		}
	}

	template< class TKey, class TValue >
	inline SortedMap< TKey, TValue >::~SortedMap()
	{
		delete[] m_data;
	}

	template< class TKey, class TValue >
	inline void SortedMap< TKey, TValue >::clear()
	{
		m_length = 0u;
	}

	template< class TKey, class TValue >
	inline void SortedMap< TKey, TValue >::reserve( uintsize size )
	{
		checkCapacity( size );
	}

	template< class TKey, class TValue >
	inline bool SortedMap<TKey, TValue>::hasKey( const TKey& key ) const
	{
		return findIndex( key ) != InvalidIndex;
	}

	template< class TKey, class TValue >
	inline TValue* SortedMap<TKey, TValue>::find( const TKey& key )
	{
		const uintsize index = findIndex( key );
		if( index == InvalidIndex )
		{
			return nullptr;
		}

		return &m_data[ index ].value;
	}

	template< class TKey, class TValue >
	inline const TValue* SortedMap<TKey, TValue>::find( const TKey& key ) const
	{
		const uintsize index = findIndex( key );
		if( index == InvalidIndex )
		{
			return nullptr;
		}

		return &m_data[ index ].value;
	}

	template< class TKey, class TValue >
	inline bool SortedMap<TKey, TValue>::findAndCopy( TValue& target, const TKey& key ) const
	{
		const uintsize index = findIndex( key );
		if( index == ( uintsize )-1 )
		{
			return false;
		}

		target = m_data[ index ].value;
		return true;
	}

	template< typename TKey, typename TValue >
	inline TValue& SortedMap< TKey, TValue >::insertKey( const TKey& key, bool& isNew )
	{
		const uintsize pos = findPositionIndex( key );

		Pair& pair1 = m_data[ pos ];
		if( pos < m_length && pair1.key == key )
		{
			isNew = false;
			return pair1.value;
		}

		checkCapacity( m_length + 1 );

		for( uintsize i = m_length; i > pos; --i )
		{
			m_data[ i ] = m_data[ i - 1 ];
		}

		Pair& pair2 = m_data[ pos ];
		pair2.key	= key;
		pair2.value	= TValue();
		m_length++;

		isNew = true;
		return pair2.value;
	}

	template< class TKey, class TValue >
	inline void SortedMap<TKey, TValue>::insert( const TKey& key, const TValue& value )
	{
		bool isNew;
		insertKey( key, isNew ) = value;
	}

	template< class TKey, class TValue >
	inline bool SortedMap< TKey, TValue >::remove( const TKey& key )
	{
		const uintsize index = findIndex( key );
		if( index == InvalidIndex )
		{
			return false;
		}

		m_length--;
		for( uintsize i = index; i < m_length; ++i )
		{
			m_data[ i ] = m_data[ i + 1u ];
		}

		return true;
	}

	template< class TKey, class TValue >
	inline typename SortedMap< TKey, TValue >::Pair* SortedMap< TKey, TValue >::getData()
	{
		return m_data;
	}

	template< class TKey, class TValue >
	inline const typename SortedMap< TKey, TValue >::Pair* SortedMap< TKey, TValue >::getData() const
	{
		return m_data;
	}

	template< class TKey, class TValue >
	inline typename SortedMap< TKey, TValue >::Pair* SortedMap< TKey, TValue >::getBegin()
	{
		return m_data;
	}

	template< class TKey, class TValue >
	inline const typename SortedMap< TKey, TValue >::Pair* SortedMap< TKey, TValue >::getBegin() const
	{
		return m_data;
	}

	template< class TKey, class TValue >
	inline typename SortedMap< TKey, TValue >::Pair* SortedMap< TKey, TValue >::getEnd()
	{
		return m_data + m_length;
	}

	template< class TKey, class TValue >
	inline const typename SortedMap< TKey, TValue >::Pair* SortedMap< TKey, TValue >::getEnd() const
	{
		return m_data + m_length;
	}

	template< class TKey, class TValue >
	inline SortedMap< TKey, TValue >& SortedMap< TKey, TValue >::operator=( const SortedMap& rhs )
	{
		clear();
		checkCapacity( rhs.m_length );
		m_length = rhs.m_length;
		for( uintsize i = 0u; i < m_length; ++i )
		{
			m_data[ i ] = rhs.m_data[ i ];
		}
		return *this;
	}

	template< class TKey, class TValue >
	inline TValue& SortedMap< TKey, TValue >::operator[]( const TKey& key )
	{
		bool isNew;
		return insertKey( key, isNew );
	}

	template< class TKey, class TValue >
	inline const TValue* SortedMap< TKey, TValue >::operator[]( const TKey& key ) const
	{
		const uintsize index = findIndex( key );
		if( index == InvalidIndex )
		{
			return nullptr;
		}

		return m_data[ index ].value;
	}

	template< typename TKey, typename TValue >
	inline uintsize SortedMap< TKey, TValue >::findIndex( const TKey& key ) const
	{
		if( m_length == 0u )
		{
			return InvalidIndex;
		}

		int imin = 0u;
		int imax = int( m_length );
		while( imax >= imin )
		{
			const int imid =  (imax + imin) / 2u;
			if( imid < 0 || imid >= (int)m_length )
			{
				return InvalidIndex;
			}

			if( m_data[ imid ].key == key )
			{
				return imid;
			}
			else if( m_data[ imid ].key < key )
			{
				imin = imid + 1;
			}
			else
			{
				imax = imid - 1;
			}
		}

		return InvalidIndex;
	}

	template< typename TKey, typename TValue >
	uintsize SortedMap< TKey, TValue >::findPositionIndex( const TKey& key ) const
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
			const PairType& kvp = m_data[ rangeMid ];

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

	template< typename TKey, typename TValue >
	void SortedMap< TKey, TValue >::checkCapacity( uintsize neededCapacity )
	{
		if( m_capacity >= neededCapacity )
		{
			return;
		}

		const uintsize capacity = getNextPowerOfTwo( neededCapacity );
		Pair* newData = new Pair[ capacity ];

		for( uintsize i = 0u; i < m_length; ++i )
		{
			newData[ i ] = m_data[ i ];
		}

		if( m_data != nullptr )
		{
			delete[] m_data;
		}

		m_data		= newData;
		m_capacity	= capacity;
	}
}
