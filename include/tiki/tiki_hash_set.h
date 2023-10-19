#pragma once

#include "tiki/tiki_array_view.h"
#include "tiki/tiki_types.h"

#include <initializer_list>

namespace tiki
{
	template< typename T >
	class HashSet
	{
	public:

		template< typename TIt >
		class IteratorBase
		{
		public:

			inline				IteratorBase( HashSet& set, uintsize index );

			const T&			getKey() const;

			T&					operator*();
			const T&			operator*() const;
			T*					operator->();
			const T*			operator->() const;
			void				operator++();
			bool				operator!=( const IteratorBase& rhs ) const;

		private:

			HashSet&			m_set;
			uintsize			m_index;
		};

		using Iterator = IteratorBase< T >;
		using ConstIterator = IteratorBase< const T >;

		inline 					HashSet();
		inline 					HashSet( const HashSet& rhs );
		inline 					HashSet( const std::initializer_list< T >& initList );
		inline 					~HashSet();

		inline bool				isEmpty() const { return m_length == 0u; }
		inline bool				hasElements() const { return m_length != 0u; }
		inline uintsize			getLength() const { return m_length; }
		inline uintsize			getCapacity() const { return m_capacity; }

		inline void				clear();
		inline void				reserve( uintsize size );

		inline bool				hasKey( const T& key ) const;

		inline bool				insert( const T& key );		// return isNew
		inline bool				remove( const T& key );

		inline Iterator			getBegin();
		inline ConstIterator	getBegin() const;
		inline Iterator			getEnd();
		inline ConstIterator	getEnd() const;

		inline HashSet&			operator=( const HashSet& rhs );

	private:

		uint64*					m_inUseMasks	= nullptr;
		T*						m_data			= nullptr;
		uintsize				m_length		= 0u;
		uintsize				m_capacity		= 0u;

		inline uintsize			findIndex( const T& key ) const;
		inline uintsize			findFirstIndex() const;
		inline uintsize			findNextIndex( uintsize index ) const;

		void					grow( uintsize minCapacity = 0u );
	};

	template< class T > typename HashSet< T >::Iterator begin( HashSet< T >& arr ) { return arr.getBegin(); }
	template< class T > typename HashSet< T >::Iterator end( HashSet< T >& arr ) { return arr.getEnd(); }
	template< class T > const typename HashSet< T >::ConstIterator begin( const HashSet< T >& arr ) { return arr.getBegin(); }
	template< class T > const typename HashSet< T >::ConstIterator end( const HashSet< T >& arr ) { return arr.getEnd(); }
}

#include "tiki/../../src/tiki_hash_set.inl"
