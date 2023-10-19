#pragma once

#include "tiki/tiki_hash.h"

namespace tiki
{
	template< typename T >
	HashSet< T >::HashSet()
	{
	}

	template< typename T >
	HashSet< T >::HashSet( const HashSet& rhs )
	{
		*this = rhs;
	}

	template< typename T >
	HashSet< T >::HashSet( const std::initializer_list< T >& initList )
	{
		for( const T& key : initList )
		{
			insert( key );
		}
	}

	template< typename T >
	HashSet< T >::~HashSet()
	{
		delete[] m_inUseMasks;
		delete[] m_data;
	}

	template< typename T >
	void HashSet< T >::clear()
	{
		memset( m_inUseMasks, 0, (sizeof( *m_inUseMasks ) * m_capacity) << 6u );
		m_length = 0u;
	}

	template< typename T >
	void HashSet< T >::reserve( uintsize size )
	{
		checkCapacity( size );
	}

	template< typename T >
	bool HashSet< T >::hasKey( const T& key ) const
	{
		return findIndex( key ) != InvalidIndex;
	}

	template< typename T >
	bool HashSet< T >::insert( const T& key )
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

			T& mapEntry = m_data[ index ];

			uint64& inUseMask = m_inUseMasks[ index >> 6u ];
			const uint64 inUseEntryMask = 1ull << (index & 0x3fu);
			if( (inUseMask & inUseEntryMask) == 0u )
			{
				inUseMask |= inUseEntryMask;

				mapEntry = key;
				m_length++;

				return true;
			}

			if( mapEntry == key )
			{
				return false;
			}

			hashOffset++;

			const TikiHash32 mapHash = calculateValueHash( mapEntry );
			if( (mapHash & indexMask) != (hash & indexMask) )
			{
				grow();

				hashOffset = 0u;
				indexMask = uint32( m_capacity - 1u );
			}
		}

		return false;
	}

	template< typename T >
	bool HashSet< T >::remove( const T& key )
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

			T* mapEntry = &m_data[ index ];
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

					T* nextMapEntry = &m_data[ nextIndex ];
					const ImUiHash nextHash = calculateValueHash( nextMapEntry );
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

				mapEntry = T();

				return true;
			}
		}

		return false;
	}

	template< typename T >
	typename HashSet< T >::Iterator HashSet< T >::getBegin()
	{
		return Iterator( *this, findFirstIndex() );
	}

	template< typename T >
	typename HashSet< T >::ConstIterator HashSet< T >::getBegin() const
	{
		return ConstIterator( *this, findFirstIndex() );
	}

	template< typename T >
	typename HashSet< T >::Iterator HashSet< T >::getEnd()
	{
		return Iterator( *this, InvalidIndex );
	}

	template< typename T >
	typename HashSet< T >::ConstIterator HashSet< T >::getEnd() const
	{
		return ConstIterator( *this, InvalidIndex );
	}

	template< typename T >
	HashSet< T >& HashSet< T >::operator=( const HashSet& rhs )
	{
		clear();

		for( ConstIterator it : rhs )
		{
			insert( it.getKey(), it.getValue() );
		}

		return *this;
	}

	template< typename T >
	uintsize HashSet< T >::findIndex( const T& key ) const
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

	template< typename T >
	uintsize HashSet< T >::findFirstIndex() const
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

	template< typename T >
	uintsize HashSet< T >::findNextIndex( uintsize index ) const
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

	template< typename T >
	void HashSet< T >::grow( uintsize minCapacity /* = 0u */ )
	{
		uint64* newEntriesInUse;
		T* newEntries;
		bool retry = true;
		uintsize nextCapacity = max( max< uintsize >( 64u, m_capacity ), getNextPowerOfTwo( minCapacity ) );
		while( retry )
		{
			retry = false;

			const uint32 nextIndexMask = uint32( nextCapacity - 1u );

			newEntriesInUse = new uint64[ nextCapacity >> 6u ];
			newEntries = new T[ nextCapacity ];
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

				const T& mapEntry = m_data[ mapIndex ];
				const ImUiHash hash = calculateValueHash( mapEntry );

				for( uint32 hashOffset = 0; ; ++hashOffset )
				{
					const uint32 newIndex = (hash + hashOffset) & nextIndexMask;

					uint64* newEntryInUse = &newEntriesInUse[ newIndex >> 6u ];
					const uint64 newEntryInUseMask = 1ull << (newIndex & 0x3fu);
					if( (*newEntryInUse & newEntryInUseMask) != 0u )
					{
						const T& newEntry = newEntries[ newIndex ];
						const ImUiHash newHash = calculateValueHash( newEntry );
						if( hashOffset >= nextCapacity || (newHash & nextIndexMask) != (hash & nextIndexMask) )
						{
							retry = true;
							break;
						}
						continue;
					}

					*newEntryInUse |= newEntryInUseMask;

					newEntries[ newIndex ] = mapEntry;
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

	template< typename T >
	template< typename TIt >
	HashSet< T >::IteratorBase< TIt >::IteratorBase( HashSet& set, uintsize index )
		: m_set( set )
		, m_index( index )
	{
	}

	template< typename T >
	template< typename TIt >
	const T& HashSet< T >::IteratorBase< TIt >::getKey() const
	{
		return m_set.m_data[ m_index ];
	}

	template< typename T >
	template< typename TIt >
	T& HashSet< T >::IteratorBase< TIt >::operator*()
	{
		return m_set.m_data[ m_index ];
	}

	template< typename T >
	template< typename TIt >
	const T& HashSet< T >::IteratorBase< TIt >::operator*() const
	{
		return m_set.m_data[ m_index ];
	}

	template< typename T >
	template< typename TIt >
	T* HashSet< T >::IteratorBase< TIt >::operator->()
	{
		return &m_set.m_data[ m_index ];
	}

	template< typename T >
	template< typename TIt >
	const T* HashSet< T >::IteratorBase< TIt >::operator->() const
	{
		return &m_set.m_data[ m_index ];
	}

	template< typename T >
	template< typename TIt >
	void HashSet< T >::IteratorBase< TIt >::operator++()
	{
		m_index = m_set.findNextIndex( m_index );
	}

	template< typename T >
	template< typename TIt >
	bool HashSet< T >::IteratorBase< TIt >::operator!=( const IteratorBase& rhs ) const
	{
		return m_index != rhs.m_index;
	}
}
