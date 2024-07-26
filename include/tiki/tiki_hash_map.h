#pragma once

#include "tiki/tiki_array_view.h"
#include "tiki/tiki_pair.h"
#include "tiki/tiki_types.h"

#include <initializer_list>

namespace tiki
{
	template< class TKey, class TValue >
	class HashMap
	{
	public:

		using PairType = Pair< TKey, TValue >;

		template< typename TPair >
		class IteratorBase
		{
		public:

			using KeyType = typename TPair::KeyType;
			using ValueType = typename TPair::ValueType;

			inline				IteratorBase( const HashMap& map, uintsize index );

			const KeyType&		getKey() const;
			ValueType&			getValue();
			const ValueType&	getValue() const;

			TPair&				operator*();
			const TPair&		operator*() const;
			TPair*				operator->();
			const TPair*		operator->() const;
			void				operator++();
			bool				operator!=( const IteratorBase& rhs ) const;

		private:

			const HashMap&		m_map;
			uintsize			m_index;
		};

		using Iterator = IteratorBase< typename PairType >;
		using ConstIterator = IteratorBase< typename const PairType >;

		inline 					HashMap();
		inline 					HashMap( const HashMap& rhs );
		inline 					HashMap( const std::initializer_list< PairType >& initList );
		inline 					~HashMap();

		inline bool				isEmpty() const { return m_length == 0u; }
		inline bool				hasElements() const { return m_length != 0u; }
		inline uintsize			getLength() const { return m_length; }
		inline uintsize			getCapacity() const { return m_capacity; }

		inline void				clear();
		inline void				reserve( uintsize size );

		inline bool				hasKey( const TKey& key ) const;

		inline TValue*			find( const TKey& key );
		inline const TValue*	find( const TKey& key ) const;
		inline bool				findAndCopy( TValue& target, const TKey& key ) const;
		inline TValue			findOrDefault( const TKey& key ) const;

		inline TValue&			insertKey( const TKey& key );
		inline TValue&			insertKey( const TKey& key, bool& isNew );
		inline void				insert( const TKey& key, const TValue& value );
		inline bool				remove( const TKey& key );

		inline Iterator			getBegin();
		inline ConstIterator	getBegin() const;
		inline Iterator			getEnd();
		inline ConstIterator	getEnd() const;

		inline void				swap( HashMap& rhs );

		inline HashMap&			operator=( const HashMap& rhs );

		inline TValue&			operator[]( const TKey& key );
		inline const TValue*	operator[]( const TKey& key ) const;

	private:

		uint64*					m_inUseMasks	= nullptr;
		PairType*				m_data			= nullptr;
		uintsize				m_length		= 0u;
		uintsize				m_capacity		= 0u;

		inline uintsize			findIndex( const TKey& key ) const;
		inline uintsize			findFirstIndex() const;
		inline uintsize			findNextIndex( uintsize index ) const;

		void					grow( uintsize minCapacity = 0u );
	};

	template< class TKey, class TValue > typename HashMap< TKey, TValue >::Iterator begin( HashMap< TKey, TValue >& map ) { return map.getBegin(); }
	template< class TKey, class TValue > typename HashMap< TKey, TValue >::Iterator end( HashMap< TKey, TValue >& map ) { return map.getEnd(); }
	template< class TKey, class TValue > typename HashMap< TKey, TValue >::ConstIterator begin( const HashMap< TKey, TValue >& map ) { return map.getBegin(); }
	template< class TKey, class TValue > typename HashMap< TKey, TValue >::ConstIterator end( const HashMap< TKey, TValue >& map ) { return map.getEnd(); }
}

#include "tiki/../../src/tiki_hash_map.inl"
