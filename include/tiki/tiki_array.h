#pragma once

#include "tiki_array_view.h"

namespace tiki
{
	template< class T >
	class Array
	{
	public:

						Array();
						Array( T* data, uintsize length );

		bool			isSet() const		{ return m_data != nullptr; }
		bool			isEmpty() const		{ return m_length == 0u; }
		bool			hasElements() const	{ return m_length != 0u; }
		uintsize		getLength() const	{ return m_length; }

		T*				getData()			{ return m_data; }
		const T*		getData() const		{ return m_data; }

		T*				getBegin()			{ return m_data; }
		const T*		getBegin() const	{ return m_data; }
		T*				getEnd()			{ return m_data + m_length; }
		const T*		getEnd() const		{ return m_data + m_length; }

		T&				getFront();
		const T&		getFront() const;
		T&				getBack();
		const T&		getBack() const;

		T&				getElement( uintsize index );
		const T&		getElement( uintsize index ) const;
		T&				getReverseElement( uintsize index );
		const T&		getReverseElement( uintsize index ) const;

		ArrayView< T >	toView() const;

		operator		ArrayView< T >() const;

		T&				operator[]( uintsize index );
		const T&		operator[]( uintsize index ) const;

	protected:

		T*				m_data;
		uintsize		m_length;
	};

	template< class T > T* begin( Array< T >& arr ) { return arr.getBegin(); }
	template< class T > T* end( Array< T >& arr ) { return arr.getEnd(); }
	template< class T > const T* begin( const Array< T >& arr ) { return arr.getBegin(); }
	template< class T > const T* end( const Array< T >& arr ) { return arr.getEnd(); }
}

#include "tiki/../../src/tiki_array.inl"
