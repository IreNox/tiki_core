#pragma once

#include "tiki/tiki_types.h"

#include <initializer_list>

namespace tiki
{
	template< class T >
	class ArrayView
	{
	public:

		inline			ArrayView();
		inline			ArrayView( const T* data, uintsize length );
		inline			ArrayView( const std::initializer_list< T >& initList );

		inline void		set( const T* data, uintsize length );

		inline bool		isSet() const { return m_data != nullptr; }
		inline bool		isEmpty() const { return m_length == 0u; }
		inline bool		hasElements() const { return m_length != 0u; }

		inline uintsize	getLength() const { return m_length; }

		inline const T*	getData() const { return m_data; }

		inline const T*	getBegin() const;
		inline const T*	getEnd() const;

		inline const T&	getFront() const;
		inline const T&	getBack() const;

		inline const T&	operator[]( uintsize index ) const;

	protected:

		const T*		m_data;
		uintsize		m_length;
	};

	template< class T > inline const T* begin( const ArrayView< T >& arr ) { return arr.getBegin(); }
	template< class T > inline const T* end( const ArrayView< T >& arr ) { return arr.getEnd(); }
}

#include "tiki/../../src/tiki_array_view.inl"
