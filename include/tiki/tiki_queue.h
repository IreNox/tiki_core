#pragma once

#include "tiki_array_view.h"
#include "tiki_core.h"

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
		uintreg			getLength() const;
		uintreg			getCapacity() const;

		void			clear();
		void			reserve( uintreg size );

		T&				pushBack();
		void			pushBack( const T& value );
		void			pushRange( const Queue< T >& vector );
		void			pushRange( const ArrayView< T >& arrayView );
		void			pushRange( const T* pData, uintreg length );

		void			popFront();
		bool			tryPopFront( T& target );

		T&				getFront();
		const T&		getFront() const;

		T&				operator[]( uintreg index );
		const T&		operator[]( uintreg index ) const;

		Queue&			operator=( const Queue& rhs );

	private:

		T*				m_pData;
		uintreg			m_top;
		uintreg			m_bottom;
		uintreg			m_length;
		uintreg			m_capacity;

		void			checkCapacity( uintreg capacity );
	};
}

#include "tiki_queue.inl"
