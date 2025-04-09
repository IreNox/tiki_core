#pragma once

namespace tiki
{
	template< typename T >
	inline ChunkedPool< T >::ChunkedPool()
	{
		m_firstFree	= nullptr;
		m_legnth	= 0u;
		m_chunkSize	= 0u;
	}

	template< typename T >
	ChunkedPool< T >::ChunkedPool( uintsize chunkSize )
	{
		TIKI_VERIFY( create( chunkSize ) );
	}

	template< typename T >
	inline ChunkedPool< T >::~ChunkedPool()
	{
		dispose();
	}

	template< typename T >
	inline bool ChunkedPool< T >::create( uintsize chunkSize )
	{
		TIKI_STATIC_ASSERT( sizeof( T ) >= sizeof( FreeElement ) );

		m_firstFree	= nullptr;
		m_legnth	= 0u;
		m_chunkSize	= chunkSize;

		if( !allocateChunk() )
		{
			dispose();
			return false;
		}

		return true;
	}

	template< typename T >
	inline void ChunkedPool< T >::dispose()
	{
		TIKI_ASSERT( m_legnth == 0u );

		while( !m_chunks.isEmpty() )
		{
			free( m_chunks.popFirst() );
		}

		m_firstFree	= nullptr;
		m_legnth	= 0u;
		m_chunkSize	= 0u;
	}

	template< typename T >
	inline bool ChunkedPool< T >::contains( ConstReference item ) const
	{
		const uintsize itemAddress = (uintsize)&item;
		const uintsize chunkDataSize = m_chunkSize * sizeof( T );
		for( const PoolChunk& chunk : m_chunks )
		{
			if( itemAddress >= (uintsize)&chunk.data[0u] && itemAddress < (uintsize)&chunk.data[chunkDataSize] )
			{
				return true;
			}
		}

		return false;
	}

	template< typename T >
	inline T* ChunkedPool< T >::push()
	{
		if( !m_firstFree && !allocateChunk() )
		{
			return nullptr;
		}

		T* element = (T*)m_firstFree;
		m_firstFree = m_firstFree->nextFree;
		m_legnth++;

		return new( element ) T;
	}

	template< typename T >
	inline T* ChunkedPool< T >::push( const T& item )
	{
		T* pItem = push();
		if( pItem != nullptr )
		{
			*pItem = item;
		}
		return pItem;
	}

	template< typename T >
	inline void ChunkedPool< T >::eraseUnsortedByValue( ConstReference item )
	{
		TIKI_ASSERT( contains( item ) );

		item.~T();

		FreeElement* newFree = (FreeElement*)&item;
		newFree->nextFree = m_firstFree;

		m_firstFree = newFree;

		m_legnth--;
	}

	template< typename T >
	inline void ChunkedPool< T >::eraseUnsortedByValue( ConstPointer pItem )
	{
		TIKI_ASSERT( pItem != nullptr );
		eraseUnsortedByValue( *pItem );
	}

	template< typename T >
	inline bool ChunkedPool< T >::allocateChunk()
	{
		TIKI_ASSERT( m_chunkSize > 0u );

		const uintsize chunkSize = sizeof( PoolChunk ) + (m_chunkSize * sizeof( T ));
		PoolChunk* chunk = new ( malloc( chunkSize ) ) PoolChunk;
		if( !chunk )
		{
			return false;
		}

		m_chunks.push( chunk );

		for( uintsize i = 0u; i < m_chunkSize; ++i )
		{
			FreeElement* element = (FreeElement*)&chunk->data[ i * sizeof( T ) ];
			element->nextFree = m_firstFree;

			m_firstFree = element;
		}

		return true;
	}
}
