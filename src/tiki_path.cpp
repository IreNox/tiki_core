#include "tiki/tiki_path.h"

namespace tiki
{
	Path::Path()
	{
	}

	Path::Path( const char* pPath )
	{
		m_path = DynamicString( pPath ).replace( '\\', '/' );

		while( m_path.endsWith( '/' ) )
		{
			m_path = m_path.popBack();
		}
	}

	Path::Path( const StringView& path )
	{
		m_path = path;
		m_path = m_path.replace( '\\', '/' );

		while( m_path.endsWith( '/' ) )
		{
			m_path = m_path.popBack();
		}
	}

	Path::Path( const DynamicString& path )
	{
		m_path = path.replace( '\\', '/' );

		while( m_path.endsWith( '/' ) )
		{
			m_path = m_path.popBack();
		}
	}

	bool Path::isAbsolute() const
	{
		return m_path[ 0u ] == '/' || m_path[ 1u ] == ':';
	}

	bool Path::isRelative() const
	{
		return !isAbsolute();
	}

	void Path::clear()
	{
		m_path.clear();
	}

	Path Path::getParent() const
	{
		const uintreg slashIndex = m_path.lastIndexOf( '/' );
		if( slashIndex == InvalidIndex )
		{
			return Path();
		}

		return Path( m_path.subString( 0u, slashIndex ) );
	}

	Path Path::push( const Path& path ) const
	{
		if( path.isAbsolute() )
		{
			return *this;
		}

		Path result = *this;
		result.m_path += "/";
		result.m_path += path.m_path;

		return result;
	}

	Path Path::push( const DynamicString& pathString ) const
	{
		Path path = Path( pathString );
		return push( path );
	}

	DynamicString Path::getFilename() const
	{
		uintreg slashIndex = m_path.lastIndexOf( '/' );
		if( slashIndex == InvalidIndex )
		{
			slashIndex = 0u;
		}

		return m_path.subString( slashIndex + 1u );
	}

	DynamicString Path::getBasename() const
	{
		uintreg slashIndex = m_path.lastIndexOf( '/' );
		if( slashIndex == InvalidIndex )
		{
			slashIndex = 0u;
		}

		uintreg dotIndex = m_path.lastIndexOf( '.' );
		if( dotIndex == InvalidIndex )
		{
			dotIndex = m_path.getLength();
		}

		const uintreg length = dotIndex - slashIndex;
		return m_path.subString( slashIndex, length );
	}

	DynamicString Path::getExtension() const
	{
		const uintreg dotIndex = m_path.lastIndexOf( '.' );
		if( dotIndex == InvalidIndex )
		{
			return DynamicString();
		}

		return m_path.subString( dotIndex );
	}

	DynamicString Path::getNativePath() const
	{
#if TIKI_ENABLED( TIKI_PLATFORM_WINDOWS )
		return m_path.replace( '/', '\\' );
#else
		return getGenericPath();
#endif
	}

	bool Path::operator==( const Path& rhs ) const
	{
		return m_path == rhs.m_path;
	}

	bool Path::operator!=( const Path& rhs ) const
	{
		return m_path != rhs.m_path;
	}
}
