#pragma once

#define TIKI_ON 				1-
#define TIKI_OFF				0-

#define TIKI_ENABLED( value )	((2 - (value 0)) == 1)
#define TIKI_DISABLED( value )	((2 - (value 0)) == 2)

#define TIKI_IF( expr )			((expr) ? TIKI_ON : TIKI_OFF)

#if defined( _WIN32 )
#	define TIKI_PLATFORM_WINDOWS		TIKI_ON
#	if defined( _WIN64 )
#		define TIKI_POINTER_64			TIKI_ON
#		define TIKI_REGISTER_64			TIKI_ON
#	else
#		define TIKI_POINTER_32			TIKI_ON
#		define TIKI_REGISTER_32			TIKI_ON
#	endif
#	if defined( _WINDLL )
#		define TIKI_TARGET_DLL			TIKI_ON
#	endif
#	define TIKI_HAS_BREAK				TIKI_ON
#else
#	define TIKI_PLATFORM_WINDOWS		TIKI_OFF
#endif

#if defined( __ANDROID__ )
#	define TIKI_PLATFORM_ANDROID		TIKI_ON
#	define TIKI_PLATFORM_POSIX			TIKI_ON
#	define TIKI_HAS_BREAK				TIKI_ON
#else
#	define TIKI_PLATFORM_ANDROID		TIKI_OFF
#endif

#if defined( __linux__ ) && !defined( __ANDROID__ )
#	define TIKI_PLATFORM_LINUX			TIKI_ON
#	define TIKI_PLATFORM_POSIX			TIKI_ON
#	define TIKI_HAS_BREAK				TIKI_ON
#else
#	define TIKI_PLATFORM_LINUX			TIKI_OFF
#endif

#if defined( ESP_PLATFORM )
#	define TIKI_PLATFORM_ESP			TIKI_ON
#else
#	define TIKI_PLATFORM_ESP			TIKI_OFF
#endif

#if defined( _MSC_VER )
#	define TIKI_COMPILER_MSVC			TIKI_ON
#else
#	define TIKI_COMPILER_MSVC			TIKI_OFF
#endif

#if defined( __clang__ )
#	define TIKI_COMPILER_CLANG			TIKI_ON
#else
#	define TIKI_COMPILER_CLANG			TIKI_OFF
#endif

#if defined( __GNUC__ )
#	define TIKI_COMPILER_GCC			TIKI_ON
#else
#	define TIKI_COMPILER_GCC			TIKI_OFF
#endif

#if TIKI_ENABLED( TIKI_COMPILER_MSVC )
#	if defined( _M_IX86 )
#		define TIKI_ARCH_X86			TIKI_ON
#	elif defined( _M_AMD64 )
#		define TIKI_ARCH_X64			TIKI_ON
#	elif defined( _M_ARM )
#		define TIKI_ARCH_ARM32			TIKI_ON
#	elif defined( _M_ARM64 )
#		define TIKI_ARCH_ARM64			TIKI_ON
#	endif
#endif

#if TIKI_ENABLED( TIKI_COMPILER_GCC ) || TIKI_ENABLED( TIKI_COMPILER_CLANG )
#	if defined( __aarch64__ ) || defined( __amd64__ )
#		define TIKI_POINTER_64			TIKI_ON
#		define TIKI_REGISTER_64			TIKI_ON
#	elif defined( __arm__ ) || defined( __i386__ )
#		define TIKI_POINTER_32			TIKI_ON
#		define TIKI_REGISTER_32			TIKI_ON
#	endif
#	if defined( __i386__ )
#		define TIKI_ARCH_X86			TIKI_ON
#	elif defined( __amd64__ )
#		define TIKI_ARCH_X64			TIKI_ON
#	elif defined( __arm__ )
#		define TIKI_ARCH_ARM32			TIKI_ON
#	elif defined( __aarch64__ )
#		define TIKI_ARCH_ARM64			TIKI_ON
#	endif
#endif

#if !defined( TIKI_ARCH_X86 )
#	define TIKI_ARCH_X86				TIKI_OFF
#endif

#if !defined( TIKI_ARCH_X64 )
#	define TIKI_ARCH_X64				TIKI_OFF
#endif

#if !defined( TIKI_ARCH_ARM32 )
#	define TIKI_ARCH_ARM32				TIKI_OFF
#endif

#if !defined( TIKI_ARCH_ARM64 )
#	define TIKI_ARCH_ARM64				TIKI_OFF
#endif

#if !defined( TIKI_PLATFORM_ARDUINO )
#	define TIKI_PLATFORM_ARDUINO		TIKI_OFF
#endif

#if !defined( TIKI_PLATFORM_POSIX )
#	define TIKI_PLATFORM_POSIX			TIKI_OFF
#endif

#if !defined( TIKI_POINTER_16 )
#	define TIKI_POINTER_16				TIKI_OFF
#endif
#if !defined( TIKI_POINTER_32 )
#	define TIKI_POINTER_32				TIKI_OFF
#endif
#if !defined( TIKI_POINTER_64 )
#	define TIKI_POINTER_64				TIKI_OFF
#endif

#if !defined( TIKI_REGISTER_8 )
#	define TIKI_REGISTER_8				TIKI_OFF
#endif
#if !defined( TIKI_REGISTER_16 )
#	define TIKI_REGISTER_16				TIKI_OFF
#endif
#if !defined( TIKI_REGISTER_32 )
#	define TIKI_REGISTER_32				TIKI_OFF
#endif
#if !defined( TIKI_REGISTER_64 )
#	define TIKI_REGISTER_64				TIKI_OFF
#endif

#if !defined( TIKI_HAS_BREAK )
#	define TIKI_HAS_BREAK				TIKI_OFF
#endif

#if !defined( TIKI_TARGET_DLL )
#	define TIKI_TARGET_DLL				TIKI_OFF
#endif

#if !defined( TIKI_DEBUG )
#	if defined( DEBUG ) || defined( _DEBUG ) || defined( __DEBUG__ )
#		define TIKI_DEBUG				TIKI_ON
#	else
#		define TIKI_DEBUG				TIKI_OFF
#	endif
#endif

#if !defined( TIKI_USE_OVERRIDE )
#	define TIKI_USE_OVERRIDE			TIKI_ON
#endif

#if !defined( TIKI_USE_FINAL )
#	define TIKI_USE_FINAL				TIKI_ON
#endif

#if TIKI_ENABLED( TIKI_USE_OVERRIDE )
#	define TIKI_OVERRIDE override
#else
#	define TIKI_OVERRIDE
#endif

#if TIKI_ENABLED( TIKI_USE_FINAL )
#	define TIKI_FINAL final
#else
#	define TIKI_FINAL
#endif

#define TIKI_OVERRIDE_FINAL TIKI_OVERRIDE TIKI_FINAL

#if TIKI_ENABLED( TIKI_HAS_BREAK )
#	if TIKI_ENABLED( TIKI_COMPILER_MSVC )
#		define TIKI_BREAK __debugbreak()
#	elif TIKI_ENABLED( TIKI_COMPILER_GCC ) || TIKI_ENABLED( TIKI_COMPILER_CLANG )
#		define TIKI_BREAK __builtin_trap()
#	endif
#else
#	define TIKI_BREAK
#endif

#if TIKI_ENABLED( TIKI_DEBUG ) && TIKI_ENABLED( TIKI_HAS_BREAK )
#	define TIKI_ASSERT( expr ) if( !( expr ) ) TIKI_BREAK
#	define TIKI_VERIFY( expr ) if( !( expr ) ) TIKI_BREAK
#else
#	define TIKI_ASSERT( expr )
#	define TIKI_VERIFY( expr ) expr
#endif

#if TIKI_ENABLED( TIKI_COMPILER_MSVC )
#	define TIKI_ALIGN_PREFIX( var )			__declspec( align( var ) )
#	define TIKI_ALIGN_POSTFIX( var )
#	define TIKI_ALIGNOF( type )				__alignof( type )

#	define TIKI_OFFSETOF( type, member )	((uintsize)(&((type*)nullptr)->member))

#	define TIKI_FORCE_INLINE				__forceinline
#	define TIKI_NO_INLINE					__declspec(noinline)
#elif TIKI_ENABLED( TIKI_COMPILER_GCC ) || TIKI_ENABLED( TIKI_COMPILER_CLANG )
#	define TIKI_ALIGN_PREFIX( var )
#	define TIKI_ALIGN_POSTFIX( var )		__attribute__( aligned( var ) ) )
#	define TIKI_ALIGNOF( type )				__alignof__( type )

#	define TIKI_OFFSETOF( type, member )	__builtin_offsetof( type, member )

#	define TIKI_FORCE_INLINE				inline __attribute__((always_inline))
#	define TIKI_NO_INLINE					__attribute__((noinline))
#else
#	error "Unsupported compiler!"
#endif

#if TIKI_ENABLED( TIKI_ARCH_X86 ) || TIKI_ENABLED( TIKI_ARCH_X64 ) // also for ARM?
#	if TIKI_ENABLED( TIKI_COMPILER_MSVC )
#		define TIKI_DLL_EXPORT			__declspec(dllexport)
#		define TIKI_DLL_IMPORT			__declspec(dllimport)
#		define TIKI_CDECL				__stdcall
#	elif TIKI_ENABLED( TIKI_COMPILER_GCC ) || TIKI_ENABLED( TIKI_COMPILER_CLANG )
#		define TIKI_DLL_EXPORT			extern
#		define TIKI_DLL_IMPORT			extern
#		define TIKI_CDECL				__attribute__((__cdecl__))
#	endif
#else
#	define TIKI_DLL_EXPORT
#	define TIKI_DLL_IMPORT
#	define TIKI_CDECL
#endif

#define TIKI_STATIC_MIN( a, b ) ((a) < (b) ? (a) : (b))
#define TIKI_STATIC_MAX( a, b ) ((a) > (b) ? (a) : (b))

#define TIKI_STATIC_ASSERT( expr )		static_assert( ( expr ), #expr )

#define TIKI_ARRAY_COUNT( arr )			(sizeof( arr ) / sizeof( *(arr)) )

#define TIKI_USE( var )					(void)var
