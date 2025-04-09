#pragma once

#include "tiki/tiki_linked_list.h"

namespace tiki
{
	template< typename T >
	class ChunkedPool
	{
	public:

		using Type				= T;
		using Reference			= T&;
		using ConstReference	= const T&;
		using Pointer			= T*;
		using ConstPointer		= const T*;

		inline					ChunkedPool();
		inline explicit			ChunkedPool( uintsize chunkSize );
		inline					~ChunkedPool();

		inline bool				create( uintsize chunkSize );
		inline void				dispose();

		inline bool				isEmpty() const { return m_legnth == 0u; }
		inline bool				hasElements() const { return m_legnth > 0u; }

		inline uintsize			getLength() const { return m_legnth; }

		inline bool				contains( ConstReference item ) const;

		inline Pointer			push();
		inline Pointer			push( const T& item );

		inline void				eraseUnsortedByValue( ConstReference item );
		inline void				eraseUnsortedByValue( ConstPointer pItem );

	private:

		struct alignas( TIKI_ALIGNOF( T ) ) PoolChunk : LinkedNode< PoolChunk >
		{
			uint8					data[ 1u ];
		};

		struct FreeElement
		{
			FreeElement*			nextFree;
		};

		LinkedList< PoolChunk >		m_chunks;
		FreeElement*				m_firstFree;

		uintsize					m_legnth;
		uintsize					m_chunkSize;

		inline bool					allocateChunk();
	};
}

#include "../../src/tiki_chunked_pool.inl"
