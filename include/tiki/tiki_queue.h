#pragma once

#include "tiki/tiki_array_view.h"

#include <initializer_list>

namespace tiki
{
	template< class T >
	class Queue
	{
	public:

						Queue();
						Queue( const Queue& rhs );
						Queue( const std::initializer_list< T >& initList );
						~Queue();

		bool			isEmpty() const;
		uintsize		getLength() const;
		uintsize		getCapacity() const;

		void			clear();
		void			reserve( uintsize size );

		T&				pushBack();
		void			pushBack( const T& value );
		void			pushRange( const Queue< T >& vector );
		void			pushRange( const ArrayView< T >& arrayView );
		void			pushRange( const T* pData, uintsize length );

		void			popFront();
		bool			tryPopFront( T& target );

		T&				getFront();
		const T&		getFront() const;

		T&				operator[]( uintsize index );
		const T&		operator[]( uintsize index ) const;

		Queue&			operator=( const Queue& rhs );

	private:

		T*				m_data;
		uintsize		m_top;
		uintsize		m_bottom;
		uintsize		m_length;
		uintsize		m_capacity;

		void			checkCapacity( uintsize capacity );
	};
}

#include "tiki/../../src/tiki_queue.inl"
