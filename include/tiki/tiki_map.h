#pragma once

#include "tiki/tiki_array_view.h"
#include "tiki/tiki_types.h"

#include <initializer_list>

namespace tiki
{
	template< class TKey, class TValue >
	class Map
	{
	public:

		struct Pair
		{
			TKey			key;
			TValue			value;
		};

		struct InsertResult
		{
			bool			isNew;
			TValue*			pValue;
		};

							Map();
							Map( const Map& rhs );
							Map( const std::initializer_list< Pair >& initList );
							~Map();

		bool				isEmpty() const;
		uintsize			getLength() const;
		uintsize			getCapacity() const;

		void				clear();
		void				reserve( uintsize size );

		bool				hasKey( const TKey& key ) const;

		TValue*				find( const TKey& key );
		const TValue*		find( const TKey& key ) const;
		bool				findAndCopy( TValue& target, const TKey& key ) const;

		InsertResult		insertKey( const TKey& key );
		void				insert( const TKey& key, const TValue& value );
		bool				remove( const TKey& key );

		Pair*				getData();
		const Pair*			getData() const;

		Pair*				getBegin();
		const Pair*			getBegin() const;
		Pair*				getEnd();
		const Pair*			getEnd() const;

		Array< Pair >		toArray() const;
		ArrayView< Pair >	toView() const;

		Map&				operator=( const Map& rhs );

		TValue&				operator[]( const TKey& key );
		const TValue&		operator[]( const TKey& key ) const;

	private:

		Pair*				m_pData;
		uintsize			m_length;
		uintsize			m_capacity;

		uintsize			findIndex( const TKey& key ) const;
		uintsize			findPositionIndex( const TKey& key ) const;

		uintsize			getNextCapacity( uintsize neededCapacity );
		void				checkCapacity( uintsize neededCapacity );
	};

	template< class TKey, class TValue > typename Map< TKey, TValue >::Pair* begin( Map< TKey, TValue >& arr ) { return arr.getBegin(); }
	template< class TKey, class TValue > typename Map< TKey, TValue >::Pair* end( Map< TKey, TValue >& arr ) { return arr.getEnd(); }
	template< class TKey, class TValue > const typename Map< TKey, TValue >::Pair* begin( const Map< TKey, TValue >& arr ) { return arr.getBegin(); }
	template< class TKey, class TValue > const typename Map< TKey, TValue >::Pair* end( const Map< TKey, TValue >& arr ) { return arr.getEnd(); }
}

#include "tiki/../../src/tiki_map.inl"
