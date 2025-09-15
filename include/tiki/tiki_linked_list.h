#pragma once

#include "tiki/tiki_types.h"

namespace tiki
{
	template< typename T >
	struct LinkedNode
	{
		inline LinkedNode()
		{
			prevItem	= nullptr;
			nextItem	= nullptr;
#if TIKI_ENABLED( TIKI_DEBUG )
			list		= nullptr;
#endif
		}

		inline ~LinkedNode()
		{
			TIKI_ASSERT( list == nullptr );
		}

		T*		prevItem;
		T*		nextItem;
#if TIKI_ENABLED( TIKI_DEBUG )
		void*	list;
#endif
	};

	template< typename T, uintsize TOffset >
	class LinkedIterator
	{
	public:

		using Type = T;
		using Node = LinkedNode< T >;

		using Pointer = T*;
		using Reference = T&;

		inline LinkedIterator( Pointer pItem )
			: m_item( pItem )
		{
		}

		inline LinkedIterator( const LinkedIterator& copy )
		{
			*this = copy;
		}

		inline void operator=( const LinkedIterator& copy )
		{
			m_item = copy.m_item;
		}

		inline LinkedIterator& operator++()
		{
			TIKI_ASSERT( m_item != nullptr );

			LinkedNode< T >* node = (LinkedNode< T >*)(uintsize( m_item ) + TOffset);
			m_item = node->nextItem;

			return *this;
		}

		inline bool operator==( const LinkedIterator& rhs )
		{
			return m_item == rhs.m_item;
		}

		inline bool operator!=( const LinkedIterator& rhs )
		{
			return m_item != rhs.m_item;
		}

		inline Reference operator*() const
		{
			return get();
		}

		inline Pointer operator->() const
		{
			TIKI_ASSERT( m_item != nullptr );
			return m_item;
		}

		inline Reference get() const
		{
			TIKI_ASSERT( m_item != nullptr );
			return *m_item;
		}

	private:

		Pointer	m_item;
	};

	template< typename T, uintsize TOffset = 0u >
	class LinkedList
	{
	public:

		using Type				= T;
		using Node				= LinkedNode< T >;

		using Iterator			= LinkedIterator< T, TOffset >;
		using ConstIterator		= LinkedIterator< const T, TOffset >;

		using Pointer			= T*;
		using ConstPointer		= const T*;
		using Reference			= T&;
		using ConstReference	= const T&;

		inline					LinkedList();
		inline					~LinkedList();

		inline void				clear();

		inline bool				isEmpty() const	{ return m_length == 0u; }
		inline bool				hasElements() const { return m_length != 0u; }

		inline Reference		push( Reference value );
		inline Reference		push( Pointer value );

		inline Pointer			popFirst();
		inline Pointer			popLast();

		inline void				eraseSortedByValue( Pointer value );
		inline void				eraseSortedByValue( Reference value );

		inline uintsize			getLength() const						{ return m_length; }

		inline Iterator			getBegin()								{ return Iterator( m_firstItem ); }
		inline ConstIterator	getBegin() const						{ return ConstIterator( m_firstItem ); }

		inline Iterator			getEnd()								{ return Iterator( nullptr ); }
		inline ConstIterator	getEnd() const							{ return ConstIterator( nullptr ); }

		inline Pointer			getFirst()								{ return m_firstItem; }
		inline ConstPointer		getFirst() const						{ return m_firstItem; }
		inline Pointer			getLast()								{ return m_lastItem; }
		inline ConstPointer		getLast() const							{ return m_lastItem; }

		inline Pointer			getNext( Pointer pValue )				{ return getNode( pValue )->nextItem; }
		inline ConstPointer		getNext( ConstPointer pValue ) const	{ return getNode( pValue )->nextItem; }
		inline Pointer			getPrev( Pointer pValue )				{ return getNode( pValue )->prevItem; }
		inline ConstPointer		getPrev( ConstPointer pValue ) const	{ return getNode( pValue )->prevItem; }

	private:

		Type*					m_firstItem;
		Type*					m_lastItem;
		uintsize				m_length;

		inline Node*			getNode( T* item );
		inline const Node*		getNode( const T* item ) const;
	};

	template< class T, uintsize TOffset > inline LinkedIterator< T, TOffset > begin( LinkedList< T, TOffset >& arr ) { return arr.getBegin(); }
	template< class T, uintsize TOffset > inline LinkedIterator< T, TOffset > end( LinkedList< T, TOffset >& arr ) { return arr.getEnd(); }
	template< class T, uintsize TOffset > inline LinkedIterator< const T, TOffset > begin( const LinkedList< T, TOffset >& arr ) { return arr.getBegin(); }
	template< class T, uintsize TOffset > inline LinkedIterator< const T, TOffset > end( const LinkedList< T, TOffset >& arr ) { return arr.getEnd(); }
}

#include "../../src/tiki_linked_list.inl"
