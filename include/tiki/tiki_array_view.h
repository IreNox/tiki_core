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

		void		set( const T* pData, uintsize length );

		bool		isSet() const { return m_data != nullptr; }
		uintsize	getLength() const { return m_length; }

		const T*	getData() const { return m_data; }

		const T*	getBegin() const;
		const T*	getEnd() const;

		const T&	getFront() const;
		const T&	getBack() const;

		const T&	operator[]( uintsize index ) const;

	protected:

		const T*	m_data;
		uintsize	m_length;
	};

	template< class T > const T* begin( const ArrayView< T >& arr ) { return arr.getBegin(); }
	template< class T > const T* end( const ArrayView< T >& arr ) { return arr.getEnd(); }
}

#include "tiki/../../src/tiki_array_view.inl"
