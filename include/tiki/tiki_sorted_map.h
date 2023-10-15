#pragma once

#include "tiki/tiki_array_view.h"
#include "tiki/tiki_types.h"

#include <initializer_list>

namespace tiki
{
	template< class TKey, class TValue >
	struct KeyValuePair
	{
		TKey			key;
		TValue			value;
	};

	template< class TKey, class TValue >
	class SortedMap : Array< KeyValuePair< TKey, TValue > >
	{
	public:

		using Pair = KeyValuePair< TKey, TValue >;

		inline 					SortedMap();
		inline 					SortedMap( const SortedMap& rhs );
		inline 					SortedMap( const std::initializer_list< Pair >& initList );
		inline 					~SortedMap();

		inline uintsize			getCapacity() const { return m_capacity };

		inline void				clear();
		inline void				reserve( uintsize size );

		inline bool				hasKey( const TKey& key ) const;

		inline TValue*			find( const TKey& key );
		inline const TValue*	find( const TKey& key ) const;
		inline bool				findAndCopy( TValue& target, const TKey& key ) const;

		inline TValue&			insertKey( const TKey& key, bool& isNew );
		inline void				insert( const TKey& key, const TValue& value );
		inline bool				remove( const TKey& key );

		inline Pair*			getData();
		inline const Pair*		getData() const;

		inline Pair*			getBegin();
		inline const Pair*		getBegin() const;
		inline Pair*			getEnd();
		inline const Pair*		getEnd() const;

		inline SortedMap&		operator=( const SortedMap& rhs );

		inline TValue&			operator[]( const TKey& key );
		inline const TValue*	operator[]( const TKey& key ) const;

	private:

		uintsize			m_capacity = 0u;

		inline uintsize		findIndex( const TKey& key ) const;
		inline uintsize		findPositionIndex( const TKey& key ) const;

		void				checkCapacity( uintsize neededCapacity );
	};

	template< class TKey, class TValue > typename SortedMap< TKey, TValue >::Pair* begin( SortedMap< TKey, TValue >& arr ) { return arr.getBegin(); }
	template< class TKey, class TValue > typename SortedMap< TKey, TValue >::Pair* end( SortedMap< TKey, TValue >& arr ) { return arr.getEnd(); }
	template< class TKey, class TValue > const typename SortedMap< TKey, TValue >::Pair* begin( const SortedMap< TKey, TValue >& arr ) { return arr.getBegin(); }
	template< class TKey, class TValue > const typename SortedMap< TKey, TValue >::Pair* end( const SortedMap< TKey, TValue >& arr ) { return arr.getEnd(); }
}

#include "tiki/../../src/tiki_sorted_map.inl"
