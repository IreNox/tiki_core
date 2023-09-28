#pragma once

#include "tiki_core.h"
#include "tiki_array_view.h"

namespace tiki
{
	template< class T, uintreg TSize >
	class StaticArray
	{
	public:

						StaticArray();

		uintreg			getLength() const;

		T*				getData();
		const T*		getData() const;

		T*				getBegin();
		const T*		getBegin() const;
		T*				getEnd();
		const T*		getEnd() const;

		T&				getFront();
		const T&		getFront() const;
		T&				getBack();
		const T&		getBack() const;

		ArrayView< T >	toArrayView() const;

		T&				operator[]( uintreg index );
		const T&		operator[]( uintreg index ) const;

		T*				begin() { return getBegin(); }
		const T*		begin() const { return getBegin(); }
		T*				end() { return getEnd(); }
		const T*		end() const { return getEnd(); }

	private:

		T			m_aData[ TSize ];
	};
}

#include "tiki_static_array.inl"