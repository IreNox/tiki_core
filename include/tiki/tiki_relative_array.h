#pragma once

#include "tiki_array.h"
#include "tiki_array_view.h"
#include "tiki_core.h"

namespace tiki
{
	template< class TType, class TValueType >
	class RelativeArray
	{
	public:

							RelativeArray();

		TType*				get();
		const TType*		get() const;
		void				set( TType* pData, TValueType size );

		bool				isValid() const;

		TValueType			getSize() const;
		TValueType			getOffset() const;

		ArrayView< TType >	toView() const;

		RelativeArray&		operator=( const RelativeArray& rhs );
		RelativeArray&		operator=( Array< TType > rhs );

		TType&				operator[]( uintreg index );
		const TType&		operator[]( uintreg index ) const;

	private:

		TValueType			m_size;
		TValueType			m_offset;
	};

	template< class T >
	using RelativeArray8 = RelativeArray< T, uint8 >;

	template< class T >
	using RelativeArray16 = RelativeArray< T, uint16 >;

	template< class T >
	using RelativeArray32 = RelativeArray< T, uint32 >;

	template< class T >
	using RelativeArray64 = RelativeArray< T, uint64 >;
}

#include "tiki_relative_array.inl"
