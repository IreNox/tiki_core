#pragma once

#include "tiki/tiki_array_view.h"

namespace tiki
{
	class StringView : public ArrayView< char >
	{
	public:

							StringView();
		explicit			StringView( const char* cstring );
							StringView( const char* string, uintsize length );
		template< uintsize TLen >
							StringView( const char (&string)[ TLen ] );
	};
}

#include "tiki/../../src/tiki_string_view.inl"