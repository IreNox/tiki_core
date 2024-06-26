#pragma once

namespace tiki
{
	inline void memory::set8( void* pTargetData, uintreg count, uint8 value )
	{
		uintreg remainingCount = count;
		uint8* pData = static_cast<uint8*>(pTargetData);
		while (remainingCount-- > 0u)
		{
			*pData++ = value;
		}
	}

	inline void memory::set16( void* pTargetData, uintreg count, uint16 value )
	{
		uintreg remainingCount = count;
		uint16* pData = static_cast<uint16*>(pTargetData);
		while (remainingCount-- > 0u)
		{
			*pData++ = value;
		}
	}

	inline void memory::set32( void* pTargetData, uintreg count, uint32 value )
	{
		uintreg remainingCount = count;
		uint32* pData = static_cast<uint32*>(pTargetData);
		while (remainingCount-- > 0u)
		{
			*pData++ = value;
		}
	}

	inline void memory::set64( void* pTargetData, uintreg count, uint64 value )
	{
		uintreg remainingCount = count;
		uint64* pData = static_cast<uint64*>(pTargetData);
		while (remainingCount-- > 0u)
		{
			*pData++ = value;
		}
	}

	inline void memory::zero( void* pTargetData, uintreg sizeInBytes )
	{
		uint8* pData = static_cast<uint8*>(pTargetData);

		const uintreg uint64Count = sizeInBytes / 8u;
		const uintreg uint8Count = sizeInBytes % 8u;
		const uintreg offset = uint64Count * 8u;

		set64( pData, uint64Count, 0ull );
		set8( pData + offset, uint8Count, 0u );
	}

	template<typename T>
	inline void memory::zero( T& p )
	{
		zero( &p, sizeof( p ) );
	}
}
