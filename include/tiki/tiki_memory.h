#pragma once

#include "tiki/tiki_types.h"

namespace tiki
{
	namespace memory
	{
		int			compare( const void* pData1, const void* pData2, uintreg sizeInBytes );
		void		copy( void* pTargetData, const void* pSourceData, uintreg sizeInBytes );
		void		copyOverlapping( void* pTargetData, const void* pSourceData, uintreg sizeInBytes );

		inline void	set8( void* pTargetData, uintreg count, uint8 value );
		inline void	set16( void* pTargetData, uintreg count, uint16 value );
		inline void	set32( void* pTargetData, uintreg count, uint32 value );
		inline void	set64( void* pTargetData, uintreg count, uint64 value );
		inline void	zero( void* pTargetData, uintreg sizeInBytes );

		template< class T >
		inline void	zero( T& pTargetData );
	}
}

#include "tiki/../../src/tiki_memory.inl"
