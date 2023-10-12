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

		inline bool				isSet() const		{ return m_data != nullptr; }
		inline bool				isEmpty() const		{ return m_length == 0u; }
		inline bool				hasElements() const	{ return m_length != 0u; }
		inline uintsize			getLength() const	{ return m_length; }

		inline T*				getData()			{ return m_data; }
		inline const T*			getData() const		{ return m_data; }

		inline T*				getBegin()			{ return m_data; }
		inline const T*			getBegin() const	{ return m_data; }
		inline T*				getEnd()			{ return m_data + m_length; }
		inline const T*			getEnd() const		{ return m_data + m_length; }

		inline T&				getFront();
		inline const T&			getFront() const;
		inline T&				getBack();
		inline const T&			getBack() const;

		inline T&				getElement( uintsize index );
		inline const T&			getElement( uintsize index ) const;
		inline T&				getReverseElement( uintsize index );
		inline const T&			getReverseElement( uintsize index ) const;

		inline ArrayView< T >	toView() const;

		inline operator			ArrayView< T >() const;

		inline T&				operator[]( uintsize index );
		inline const T&			operator[]( uintsize index ) const;

	protected:

		T*						m_data;
		uintsize				m_length;
	};

	template< class T > inline T* begin( Array< T >& arr ) { return arr.getBegin(); }
	template< class T > inline T* end( Array< T >& arr ) { return arr.getEnd(); }
	template< class T > inline const T* begin( const Array< T >& arr ) { return arr.getBegin(); }
	template< class T > inline const T* end( const Array< T >& arr ) { return arr.getEnd(); }
}

#include "tiki/../../src/tiki_array.inl"
