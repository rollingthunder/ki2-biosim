/**
 *************************************************************************
 *
 * @file build_config.hpp
 *
 * Configuration of the current build parameters, library dependencies,
 * and compiler-specific settings.
 *
 ************************************************************************/


#if !defined(INCLUDED_BUILD_CONFIG_HPP)
#define INCLUDED_BUILD_CONFIG_HPP




/** @cond DOXYGEN_IGNORE */




//////////////////////////////////////////////////////////////////////////
//
//	Auto configuration
//
//////////////////////////////////////////////////////////////////////////


// Various Visual C++ versions
#if defined(_MSC_VER)

	#define COMPILER_VISUALCPP
	#define COMPILER_STRING "COMPILER_VISUALCPP"

	#define OS_TARGET_WINDOWS
	#define OS_TARGET_STRING "OS_TARGET_WINDOWS"

	#if defined(_WIN64)
		#define MACHINE_TARGET_X64
		#define MACHINE_TARGET_STRING "MACHINE_TARGET_X64"
	#elif defined(_WIN32)
		#define MACHINE_TARGET_X86
		#define MACHINE_TARGET_STRING "MACHINE_TARGET_X86"
	#endif

	#if defined(_DEBUG)
		#define BUILD_MODE_DEBUG
		#define BUILD_MODE_STRING "BUILD_MODE_DEBUG"
	#else
		#define BUILD_MODE_RELEASE
		#define BUILD_MODE_STRING "BUILD_MODE_RELEASE"
	#endif

#endif


// Configuration success test
#if !defined(COMPILER_STRING) || !defined(MACHINE_TARGET_STRING) || \
	!defined(OS_TARGET_STRING) || !defined(BUILD_MODE_STRING)
	#error "Auto configuration failed"
	#error "See build_config.h for supported options."
#endif




//////////////////////////////////////////////////////////////////////////
//
//	Visual C++ specific
//
//////////////////////////////////////////////////////////////////////////


#if defined(COMPILER_VISUALCPP)

	// Enable virtual dtor nonexistant warning
	#pragma warning (default : 4265)


	// Uncomment to disable "this in initializer list" warning
	// This warning should be fixed, though.
	// #pragma warning (disable : 4355)


	// Disable the nasty CRT warnings that tell us to use
	// windows-specific methods for some potentially unsafe
	// calls such as itoa.
	#define _CRT_SECURE_NO_WARNINGS


	// WinXP and ie5 minimum is required for some threading,
	// synching, and shell stuff.
	#define _WIN32_WINNT 0x0501
	#define _WIN32_IE 0x0500


	// Don't never ever use the ugly windows max / min macros...
	#define NOMINMAX


	// Windows-specific, non-standard types.
	typedef __int64 long_int;

	#if defined(_WIN64)
		typedef unsigned __int64 pointer_int;
	#else
		typedef unsigned int pointer_int;
	#endif


	// The nothrow-tag should not be evaluated.
	// Visual C++ doesn't even report if some method clearly
	// violates a throw()-specifier, so we use the tag just
	// for additional code documentation.
	#define NOTHROW


	// Commonplace NULL define, here so we don't have
	// to pull in a standard header.
	#define NULL 0

#endif




/** @endcond */




//////////////////////////////////////////////////////////////////////////
//
// Doxygen documentation control.
//
// The defines below enable all compile-time switches for each library,
// compiler, target machine path and target build mode when
// doxygen is running. This serves for generating a complete
// documentation for all compile pathes.
//
//////////////////////////////////////////////////////////////////////////


#if defined(DOXYGEN_DOCUMENTATION)

	/**
	 * Macro that is set only if doxygen runs,
	 * and which enables all potential compile pathes through code.
	 */
	#define DOXYGEN_DOCUMENTATION


	/** Compiler define flags and associated name string. */
	//@{
	#define COMPILER_VISUALC2003
	#define COMPILER_VISUALC2005
	#define COMPILER_VISUALC2008
	#define COMPILER_VISUALC2010
	#define COMPILER_MINGW
	#define COMPILER_STRING "CURRENT_COMPILER"
	//@}


	/** Target machine flags and associated name string. */
	//@{
	#define MACHINE_TARGET_X86
	#define MACHINE_TARGET_X64
	#define MACHINE_TARGET_STRING "CURRENT_MACHINE_TARGET"
	//@}


	/** Target OS flags and associated name string. */
	//@{
	#define OS_TARGET_WINDOWS
	#define OS_TARGET_STRING "CURRENT_OS_TARGET"
	//@}


	/** Build mode flags and name string. */
	//@{
	#define BUILD_MODE_DEBUG
	#define BUILD_MODE_RELEASE
	#define BUILD_MODE_STRING "CURRENT_BUILD_MODE"
	//@}


	/** 64-bit, signed integer type. */
	typedef __int64 long_int;


	/**
	 * Unsigned integer the size of a pointer on the
	 * target architecture.
	 */
	typedef unsigned int pointer_int;


	/**
	 * This define, available for method declarations and definitions,
	 * indicates that a method provides an explicit nothrow guarantee.
	 *
	 * Ideally, we'd like exception specifiers to be verified
	 * at compile-time, which the C++ language doesn't let us do.
	 * Hence, the actual realization depends on the target compiler.	 
	 * For instance, under Visual C++, the NOTHROW tag simply is
	 * ignored, since Visual C++ never checks throwing specifiers.
	 *
	 * For Doxygen documentation purposes, all non-throwing methods
	 * have an explicit throw() specifier.
	 */
	#define NOTHROW throw()

#endif




#endif /* !defined(INCLUDED_BUILD_CONFIG_HPP) */
