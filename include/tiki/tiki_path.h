#pragma once

#include "tiki/tiki_dynamic_string.h"

namespace tiki
{
	class Path
	{
	public:

						Path();
						Path( const char* pPath );
						Path( const StringView& path );
						Path( const DynamicString& path );

		bool			isEmpty() const { return m_path.isEmpty(); }
		bool			hasElements() const { return m_path.hasElements(); }
		bool			isAbsolute() const;
		bool			isRelative() const;

		void			clear();

		Path			getParent() const;

		Path			push( const Path& path ) const;

		Path			replaceFilename( const StringView& value ) const;
		Path			replaceBasename( const StringView& value ) const;
		Path			replaceExtension( const StringView& value ) const;

		DynamicString	getFilename() const;
		DynamicString	getBasename() const;
		DynamicString	getExtension() const;

		DynamicString	getNativePath() const;
		StringView		getGenericPath() const { return m_path; }

		bool			operator==( const Path& rhs ) const;
		bool			operator!=( const Path& rhs ) const;

	private:

		DynamicString	m_path;
	};
}