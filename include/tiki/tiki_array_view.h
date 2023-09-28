#pragma once

#include "tiki/tiki_types.h"

namespace tiki
{
	template< class T >
	class ArrayView
	{
	public:

							ArrayView();
							ArrayView( const T* pData, uintsize length );

		void				set( const T* pData, uintsize length );

		bool				isSet() const { return m_pData != nullptr; }
		uintsize			getLength() const { return m_length; }

		const T*			getData() const { return m_pData; }

		const T*			getBegin() const;
		const T*			getEnd() const;

		const T&			getFront() const;
		const T&			getBack() const;

		const T&			operator[]( uintsize index ) const;

		const T*			begin() const { return getBegin(); }
		const T*			end() const { return getEnd(); }

	private:

		const T*			m_pData;
		uintsize			m_length;
	};
}

#include "tiki/../../src/tiki_array_view.inl"
