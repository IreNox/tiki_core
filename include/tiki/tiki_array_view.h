#pragma once

#include "tiki/tiki_types.h"

#include <initializer_list>

namespace tiki
{
	template< class T >
	class ArrayView
	{
	public:

		inline					ArrayView();
		inline					ArrayView( T* data, uintsize length );
		inline					ArrayView( const std::initializer_list< T >& initList );

		inline void				set( T* data, uintsize length );

		inline bool				isSet() const { return m_data != nullptr; }
		inline bool				isEmpty() const { return m_length == 0u; }
		inline bool				hasElements() const { return m_length != 0u; }

		inline uintsize			getLength() const { return m_length; }
		inline uintsize			getSizeInBytes() const { return m_length * sizeof( T ); }
		inline uintsize			getElementSizeInBytes() const { return sizeof( T ); }

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

		inline ArrayView< T >	getRange( uintsize start ) const;
		inline ArrayView< T >	getRange( uintsize start, uintsize length ) const;

		template< typename T2 >
		inline ArrayView< T2 >			cast();
		template< typename T2 >
		inline ArrayView< const T2 >	cast() const;

		inline operator			ArrayView< const T >() const;

		inline T&				operator[]( uintsize index );
		inline const T&			operator[]( uintsize index ) const;

	protected:

		T*						m_data;
		uintsize				m_length;
	};

	template< class T > inline T* begin( ArrayView< T >& arr ) { return arr.getBegin(); }
	template< class T > inline T* end( ArrayView< T >& arr ) { return arr.getEnd(); }
	template< class T > inline const T* begin( const ArrayView< T >& arr ) { return arr.getBegin(); }
	template< class T > inline const T* end( const ArrayView< T >& arr ) { return arr.getEnd(); }

	template< class T >
	using ConstArrayView = ArrayView< const T >;
}

#include "tiki/../../src/tiki_array_view.inl"
