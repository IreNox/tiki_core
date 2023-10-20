#pragma once

#include "tiki/tiki_hash.h"

namespace tiki
{
	template< class TKey, class TValue >
	HashMap< TKey, TValue >::HashMap()
	{
	}

	template< class TKey, class TValue >
	HashMap< TKey, TValue >::HashMap( const HashMap& rhs )
	{
		*this = rhs;
	}

	template< class TKey, class TValue >
	HashMap< TKey, TValue >::HashMap( const std::initializer_list< Pair >& initList )
	{
		for( const Pair& pair : initList )
		{
			insert( pair.key, pair.value );
		}
	}

	template< class TKey, class TValue >
	HashMap< TKey, TValue >::~HashMap()
	{
		delete[] m_inUseMasks;
		delete[] m_data;
	}

	template< class TKey, class TValue >
	void HashMap< TKey, TValue >::clear()
	{
		memset( m_inUseMasks, 0, sizeof( *m_inUseMasks ) * (m_capacity >> 6u) );
		m_length = 0u;
	}

	template< class TKey, class TValue >
	void HashMap< TKey, TValue >::reserve( uintsize size )
	{
		checkCapacity( size );
	}

	template< class TKey, class TValue >
	bool HashMap<TKey, TValue>::hasKey( const TKey& key ) const
	{
		return findIndex( key ) != InvalidIndex;
	}

	template< class TKey, class TValue >
	TValue* HashMap<TKey, TValue>::find( const TKey& key )
	{
		const uintsize index = findIndex( key );
		if( index == InvalidIndex )
		{
			return nullptr;
		}

		return &m_data[ index ].value;
	}

	template< class TKey, class TValue >
	const TValue* HashMap<TKey, TValue>::find( const TKey& key ) const
	{
		const uintsize index = findIndex( key );
		if( index == InvalidIndex )
		{
			return nullptr;
		}

		return &m_data[ index ].value;
	}

	template< class TKey, class TValue >
	bool HashMap<TKey, TValue>::findAndCopy( TValue& target, const TKey& key ) const
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
	TValue& HashMap< TKey, TValue >::insertKey( const TKey& key )
	{
		bool isNew;
		return insertKey( key, isNew );
	}

	template< typename TKey, typename TValue >
	TValue& HashMap< TKey, TValue >::insertKey( const TKey& key, bool& isNew )
	{
		if( m_capacity == 0u )
		{
			grow();
		}

		const TikiHash32 hash	= calculateValueHash( key );
		uint32 indexMask		= uint32( m_capacity - 1u );

		uint32 hashOffset = 0;
		while( true )
		{
			const uint32 index = (hash + hashOffset) & indexMask;

			Pair& mapEntry = m_data[ index ];

			uint64& inUseMask = m_inUseMasks[ index >> 6u ];
			const uint64 inUseEntryMask = 1ull << (index & 0x3fu);
			if( (inUseMask & inUseEntryMask) == 0u )
			{
				inUseMask |= inUseEntryMask;

				mapEntry.key	= key;
				mapEntry.value	= TValue();

				isNew = true;

				m_length++;

				return mapEntry.value;
			}

			if( mapEntry.key == key )
			{
				isNew = false;
				return mapEntry.value;
			}

			hashOffset++;

			const TikiHash32 mapHash = calculateValueHash( mapEntry.key );
			if( (mapHash & indexMask) != (hash & indexMask) )
			{
				grow();

				hashOffset = 0u;
				indexMask = uint32( m_capacity - 1u );
			}
		}

		return *(TValue*)nullptr;
	}

	template< class TKey, class TValue >
	void HashMap<TKey, TValue>::insert( const TKey& key, const TValue& value )
	{
		insertKey( key ) = value;
	}

	template< class TKey, class TValue >
	bool HashMap< TKey, TValue >::remove( const TKey& key )
	{
		const TikiHash32 hash	= calculateValueHash( key );
		const uint32 indexMask	= uint32( m_capacity - 1u );

		for( uint32 hashOffset = 0u; ; ++hashOffset )
		{
			const uint32 index = (hash + hashOffset) & indexMask;

			uint64* inUseMask = &m_inUseMasks[ index >> 6u ];
			uint64 indexInUseMask = 1ull << (index & 0x3fu);
			if( (*inUseMask & indexInUseMask) == 0u )
			{
				break;
			}

			Pair* mapEntry = &m_data[ index ];
			if( mapEntry->key == key )
			{
				const uint32 baseIndex = hash & indexMask;

				uint32 nextIndex = index;
				while( true )
				{
					nextIndex = (nextIndex + 1u) & indexMask;

					uint64* nextInUseMask = &m_inUseMasks[ nextIndex >> 6u ];
					const uint64 nextIndexInUseMask = 1ull << (nextIndex & 0x3fu);
					if( (*nextMapEntryInUse & nextIndexInUseMask) == 0u )
					{
						break;
					}

					Pair* nextMapEntry = &m_data[ nextIndex ];
					const ImUiHash nextHash = calculateValueHash( nextMapEntry->key );
					if( (nextHash & indexMask) != baseIndex )
					{
						break;
					}

					*mapEntry = *nextMapEntry;

					mapEntry = nextMapEntry;
					inUseMask = nextInUseMask;
					indexInUseMask = nextIndexInUseMask;
				}

				*inUseMask &= ~indexInUseMask;
				m_length--;

				mapEntry->key = TKey();

				return true;
			}
		}

		return false;
	}

	template< class TKey, class TValue >
	typename HashMap< TKey, TValue >::Iterator HashMap< TKey, TValue >::getBegin()
	{
		return Iterator( *this, findFirstIndex() );
	}

	template< class TKey, class TValue >
	typename HashMap< TKey, TValue >::ConstIterator HashMap< TKey, TValue >::getBegin() const
	{
		return ConstIterator( *this, findFirstIndex() );
	}

	template< class TKey, class TValue >
	typename HashMap< TKey, TValue >::Iterator HashMap< TKey, TValue >::getEnd()
	{
		return Iterator( *this, InvalidIndex );
	}

	template< class TKey, class TValue >
	typename HashMap< TKey, TValue >::ConstIterator HashMap< TKey, TValue >::getEnd() const
	{
		return ConstIterator( *this, InvalidIndex );
	}

	template< class TKey, class TValue >
	HashMap< TKey, TValue >& HashMap< TKey, TValue >::operator=( const HashMap& rhs )
	{
		clear();

		for( ConstIterator it : rhs )
		{
			insert( it.getKey(), it.getValue() );
		}

		return *this;
	}

	template< class TKey, class TValue >
	TValue& HashMap< TKey, TValue >::operator[]( const TKey& key )
	{
		return insertKey( key );
	}

	template< class TKey, class TValue >
	const TValue* HashMap< TKey, TValue >::operator[]( const TKey& key ) const
	{
		const uintsize index = findIndex( key );
		if( index == InvalidIndex )
		{
			return nullptr;
		}

		return &m_data[ index ].value;
	}

	template< typename TKey, typename TValue >
	uintsize HashMap< TKey, TValue >::findIndex( const TKey& key ) const
	{
		const ImUiHash hash		= calculateValueHash( key );
		const uint32 indexMask	= uint32( m_capacity - 1u );

		for( uint32 hashOffset = 0u; hashOffset < m_capacity; ++hashOffset )
		{
			const uintsize index = (hash + hashOffset) & indexMask;

			uint64* mapEntryInUse = &m_inUseMasks[ index >> 6u ];
			const uint64 mapEntryInUseMask = 1ull << (index & 0x3fu);
			if( (*mapEntryInUse & mapEntryInUseMask) == 0u )
			{
				break;
			}

			Pair& mapEntry = m_data[ index ];
			if( mapEntry.key == key )
			{
				return index;
			}

			const ImUiHash mapHash = calculateValueHash( mapEntry.key );
			if( (mapHash & indexMask) != (hash & indexMask) )
			{
				break;
			}
		}

		return InvalidIndex;
	}

	template< class TKey, class TValue >
	uintsize HashMap< TKey, TValue >::findFirstIndex() const
	{
		if( m_length == 0u )
		{
			return InvalidIndex;
		}

		const uint64* mapEntryInUse = m_inUseMasks;
		uint64 mapEntryInUseMask = 1u;
		for( uintsize mapIndex = 0u; mapIndex < m_capacity; ++mapIndex )
		{
			if( *mapEntryInUse & mapEntryInUseMask )
			{
				return mapIndex;
			}

			mapEntryInUseMask <<= 1u;
			if( mapEntryInUseMask == 0u )
			{
				mapEntryInUse++;
				mapEntryInUseMask = 1u;
			}
		}

		return InvalidIndex;
	}

	template< class TKey, class TValue >
	uintsize HashMap< TKey, TValue >::findNextIndex( uintsize index ) const
	{
		++index;

		const uint64* mapEntryInUse = &m_inUseMasks[ index >> 6u ];
		uint64 mapEntryInUseMask = 1ull << (index & 0x3fu);

		for( ; index < m_capacity; ++index )
		{
			if( *mapEntryInUse & mapEntryInUseMask )
			{
				return index;
			}

			mapEntryInUseMask <<= 1u;
			if( mapEntryInUseMask == 0u )
			{
				mapEntryInUse++;
				mapEntryInUseMask = 1u;
			}
		}

		return InvalidIndex;
	}

	template< typename TKey, typename TValue >
	void HashMap< TKey, TValue >::grow( uintsize minCapacity /* = 0u */ )
	{
		uint64* newEntriesInUse;
		Pair* newEntries;
		bool retry = true;
		uintsize nextCapacity = max( max< uintsize >( 64u, m_capacity << 1u ), getNextPowerOfTwo( minCapacity ) );
		while( retry )
		{
			retry = false;

			const uint32 nextIndexMask = uint32( nextCapacity - 1u );

			newEntriesInUse = new uint64[ nextCapacity >> 6u ];
			newEntries = new Pair[ nextCapacity ];
			if( !newEntriesInUse || !newEntries )
			{
				delete[] newEntriesInUse;
				delete[] newEntries;
				return;
			}

			memset( newEntriesInUse, 0, sizeof( *newEntriesInUse ) * (nextCapacity >> 6u) );

			for( uintsize mapIndex = 0; mapIndex < m_capacity; ++mapIndex )
			{
				const uint64& mapEntryInUse = m_inUseMasks[ mapIndex >> 6u ];
				const uint64 mapEntryInUseMask = 1ull << (mapIndex & 0x3fu);
				if( (mapEntryInUse & mapEntryInUseMask) == 0u )
				{
					continue;
				}

				const Pair& mapEntry = m_data[ mapIndex ];
				const ImUiHash hash = calculateValueHash( mapEntry.key );

				for( uint32 hashOffset = 0; ; ++hashOffset )
				{
					const uint32 newIndex = (hash + hashOffset) & nextIndexMask;

					uint64* newEntryInUse = &newEntriesInUse[ newIndex >> 6u ];
					const uint64 newEntryInUseMask = 1ull << (newIndex & 0x3fu);
					if( (*newEntryInUse & newEntryInUseMask) != 0u )
					{
						const Pair& newEntry = newEntries[ newIndex ];
						const ImUiHash newHash = calculateValueHash( newEntry.key );
						if( hashOffset >= nextCapacity || (newHash & nextIndexMask) != (hash & nextIndexMask) )
						{
							retry = true;
							break;
						}
						continue;
					}

					*newEntryInUse |= newEntryInUseMask;

					Pair& newEntry = newEntries[ newIndex ];
					newEntry.key	= mapEntry.key;
					newEntry.value	= mapEntry.value;
					break;
				}

				if( retry )
				{
					delete[] newEntriesInUse;
					delete[] newEntries;

					nextCapacity <<= 1u;
					break;
				}
			}
		}

		delete[] m_inUseMasks;
		delete[] m_data;

		m_inUseMasks	= newEntriesInUse;
		m_data			= newEntries;
		m_capacity		= nextCapacity;
	}

	template< typename TKey, typename TValue >
	template< typename T >
	HashMap< TKey, TValue >::IteratorBase< T >::IteratorBase( HashMap& map, uintsize index )
		: m_map( map )
		, m_index( index )
	{
	}

	template< typename TKey, typename TValue >
	template< typename T >
	const TKey& HashMap< TKey, TValue >::IteratorBase< T >::getKey() const
	{
		return m_map.m_data[ m_index ].key;
	}

	template< typename TKey, typename TValue >
	template< typename T >
	T& HashMap< TKey, TValue >::IteratorBase< T >::getValue()
	{
		return m_map.m_data[ m_index ].value;
	}

	template< typename TKey, typename TValue >
	template< typename T >
	const T& HashMap< TKey, TValue >::IteratorBase< T >::getValue() const
	{
		return m_map.m_data[ m_index ].value;
	}

	template< typename TKey, typename TValue >
	template< typename T >
	T& HashMap< TKey, TValue >::IteratorBase< T >::operator*()
	{
		return m_map.m_data[ m_index ].value;
	}

	template< typename TKey, typename TValue >
	template< typename T >
	const T& HashMap< TKey, TValue >::IteratorBase< T >::operator*() const
	{
		return m_map.m_data[ m_index ].value;
	}

	template< typename TKey, typename TValue >
	template< typename T >
	T* HashMap< TKey, TValue >::IteratorBase< T >::operator->()
	{
		return &m_map.m_data[ m_index ].value;
	}

	template< typename TKey, typename TValue >
	template< typename T >
	const T* HashMap< TKey, TValue >::IteratorBase< T >::operator->() const
	{
		return &m_map.m_data[ m_index ].value;
	}

	template< typename TKey, typename TValue >
	template< typename T >
	void HashMap< TKey, TValue >::IteratorBase< T >::operator++()
	{
		m_index = m_map.findNextIndex( m_index );
	}

	template< typename TKey, typename TValue >
	template< typename T >
	bool HashMap< TKey, TValue >::IteratorBase< T >::operator!=( const IteratorBase& rhs ) const
	{
		return m_index != rhs.m_index;
	}
}
