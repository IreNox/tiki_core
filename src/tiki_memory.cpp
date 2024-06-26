#include "tiki/tiki_memory.h"

#if TIKI_ENABLED( TIKI_COMPILER_MSVC )
#	include <memory.h>
#elif TIKI_ENABLED( TIKI_COMPILER_GCC ) || TIKI_ENABLED( TIKI_COMPILER_CLANG )
#	include <string.h>
#endif


namespace tiki
{
	int	memory::compare( const void* pData1, const void* pData2, uintreg sizeInBytes )
	{
		return memcmp( pData1, pData2, sizeInBytes );
	}

	void memory::copy( void* pTargetData, const void* pSourceData, uintreg sizeInBytes )
	{
		memcpy( pTargetData, pSourceData, sizeInBytes );
	}

	void memory::copyOverlapping( void* pTargetData, const void* pSourceData, uintreg sizeInBytes )
	{
		memmove( pTargetData, pSourceData, sizeInBytes );
	}
}
