#pragma once

namespace tiki
{
	template< typename T, uintsize TOffset >
	inline LinkedList< T, TOffset >::LinkedList()
	{
		m_firstItem = nullptr;
		m_lastItem = nullptr;
		m_length	= 0u;
	}

	template< typename T, uintsize TOffset >
	inline LinkedList< T, TOffset >::~LinkedList()
	{
		TIKI_ASSERT( m_firstItem == nullptr );
	}

	template< typename T, uintsize TOffset >
	inline void LinkedList< T, TOffset >::clear()
	{
		T* item = m_firstItem;
		while ( item != nullptr )
		{
			T* next = getNode( item )->nextItem;

			item->prevItem	= nullptr;
			item->nextItem	= nullptr;
#if TIKI_ENABLED( TIKI_DEBUG )
			item->list		= nullptr;
#endif

			item = next;
		}

		m_firstItem	= nullptr;
		m_lastItem	= nullptr;
		m_length	= 0u;
	}

	template< typename T, uintsize TOffset >
	inline T& LinkedList< T, TOffset >::push( Reference value )
	{
		return push( &value );
	}

	template< typename T, uintsize TOffset >
	inline T& LinkedList< T, TOffset >::push( Pointer value )
	{
		TIKI_ASSERT( value );

		Node* node = getNode( value );
		TIKI_ASSERT( !node->list );

		if( !m_firstItem )
		{
			node->prevItem	= nullptr;
			node->nextItem	= nullptr;
#if TIKI_ENABLED( TIKI_DEBUG )
			node->list		= this;
#endif

			m_firstItem	= value;
			m_lastItem	= value;
		}
		else
		{
			TIKI_ASSERT( m_lastItem != nullptr );

			node->prevItem	= m_lastItem;
			node->nextItem	= nullptr;
#if TIKI_ENABLED( TIKI_DEBUG )
			node->list		= this;
#endif

			getNode( m_lastItem )->nextItem = value;
			m_lastItem = value;
		}

		m_length++;

		return *value;
	}

	template< typename T, uintsize TOffset >
	inline T* LinkedList< T, TOffset >::popFirst()
	{
		if( !m_firstItem )
		{
			return nullptr;
		}

		if( m_firstItem == m_lastItem )
		{
			m_lastItem = nullptr;
		}

		T* first = m_firstItem;
		Node* node = getNode( first );
		if( node->nextItem )
		{
			Node* nextNode = getNode( node->nextItem );
			nextNode->prevItem = nullptr;
		}
		
		m_firstItem = node->nextItem;

		node->prevItem	= nullptr;
		node->nextItem	= nullptr;
#if TIKI_ENABLED( TIKI_DEBUG )
		node->list		= nullptr;
#endif

		m_length--;
		return first;
	}

	template< typename T, uintsize TOffset >
	inline T* LinkedList< T, TOffset >::popLast()
	{
		if( !m_lastItem )
		{
			return nullptr;
		}

		if( m_firstItem == m_lastItem )
		{
			m_firstItem = nullptr;
		}

		T* last = m_lastItem;
		Node* node = getNode( last );
		if( node->prevItem )
		{
			Node* prevNode = getNode( node->prevItem );
			prevNode->nextItem = nullptr;
		}
		
		m_lastItem = node->prevItem;

		node->prevItem	= nullptr;
		node->nextItem	= nullptr;
#if TIKI_ENABLED( TIKI_DEBUG )
		node->list		= nullptr;
#endif

		m_length--;
		return last;
	}

	template< typename T, uintsize TOffset >
	inline void LinkedList< T, TOffset >::eraseSortedByValue( Pointer value )
	{
		TIKI_ASSERT( pValue != nullptr );
		removeSortedByValue( *value );
	}

	template< typename T, uintsize TOffset >
	inline void LinkedList< T, TOffset >::eraseSortedByValue( Reference value )
	{
		Node* node = getNode( value );
		TIKI_ASSERT( node.list == this );

		if ( &value == m_firstItem )
		{
			m_firstItem = node.nextItem;
		}

		if ( &value == m_lastItem )
		{
			m_lastItem = node.prevItem;
		}

		if ( node.prevItem != nullptr )
		{
			Node* prevNode = getNode( node->prevItem );
			prevItem->nextItem = node.nextItem;
		}

		if( node.nextItem != nullptr )
		{
			Node* nextNode = getNode( node->nextItem );
			nextNode->prevItem = node.prevItem;
		}

		node->prevItem	= nullptr;
		node->nextItem	= nullptr;
#if TIKI_ENABLED( TIKI_DEBUG )
		node->list		= nullptr;
#endif

		m_length--;
	}

	template< typename T, uintsize TOffset >
	inline typename LinkedList< T, TOffset>::Node* LinkedList< T, TOffset >::getNode( T* item )
	{
		Node* node = (Node*)(uintsize( item ) + TOffset);
		return node;
	}

	template< typename T, uintsize TOffset >
	inline const LinkedNode< T >* LinkedList< T, TOffset >::getNode( const T* item ) const
	{
		return getNode( const_cast< T* >( item ) );
	}
}
