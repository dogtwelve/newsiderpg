// Copyright (C) 2005 Gameloft. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Qiu Wei Min

#ifndef __COMMON_H__
#define __COMMON_H__


#define	PLATFORM_BREW 1
#define	PLATFORM_WIN32 2

//Cpu speed class
#define CPU_HIGH		0
#define CPU_MIDDLE		1
#define CPU_LOW			2
//Screen size class
#define SCREEN_HUGE     0
#define SCREEN_BIG      1
#define SCREEN_MIDDLE   2 
#define SCREEN_SMALL    3

//Brew 1.x Devices
#define DEVICE_N3589i	1
//#define DEVICE_T720		2
#define	DEVICE_Z800		2
#define DEVICE_KZ810	3
#define DEVICE_LGVX4400	4
#define DEVICE_C343		5
#define DEVICE_A610		6


//Brew 2.x Devices
#define	DEVICE_LG6000	7
#define	DEVICE_LG7000	8
#define DEVICE_MotoV260 9
#define	DEVICE_LG4700	10
#define DEVICE_A650		11
#define	DEVICE_SE47		12
#define DEVICE_CDM8600	13
#define DEVICE_KX1		14
#define DEVICE_CDM8910  15
#define DEVICE_Nokia6256 16
#define DEVICE_CDM9900	17
#define DEVICE_KX414	18
#define DEVICE_LG9800	19
#define DEVICE_LG4500	20
#define DEVICE_LG5200	21

#include "deviceinfo.h"
#include "../config_version.h"

#if PLATFORM == PLATFORM_BREW
//#ifndef WIPIC
//	#include <AEE.h> 
//	#include <AEEFile.h>
//	#include <AEEAppGen.h>
//	#include <AEEComdef.h>
//	#include <AEEStdLib.h>
//	#include <AEEHeap.h>
//#endif

#ifdef __arm
	#ifndef __FEATURE_SIGNED_CHAR //we must use -zc in mak file
	#error	please use -zc in make file
	#endif
#endif

#elif PLATFORM == PLATFORM_WIN32
	typedef unsigned char boolean;
	#ifndef USE_GDIPLUS
		#define WIN32_LEAN_AND_MEAN
	#endif
	
	#include <stdlib.h>
	#include <stdio.h>
	#include <windows.h>

	#ifdef INTERFACE
		#undef INTERFACE
	#endif	

	#ifdef DELETE
		#undef DELETE
	#endif
	
	const int		WM_GAME_BEGIN_LOAD	=	WM_USER + 1;
	const int		WM_GAME_END_LOAD	=	WM_USER + 2;
	const int		WM_GAME_RESTART		=	WM_USER + 3;
#endif

#include "SysUtil.h"
#include "memory.h"

//void* operator new(unsigned int size);
//void* operator new[](unsigned int size);
//void* operator new(unsigned int size, MemoryType memType);
//void* operator new[](unsigned int size, MemoryType memType);
//void operator delete(void *p);
//void operator delete[](void *p);
//void operator delete(void *p, MemoryType memType);
//void operator delete[](void *p, MemoryType memType);

/// @ingroup Global
/// @brief This "operator" attempts to dynamically allocate one or more objects from pool or heap.
///
/// Use this macro instead of "new" to facilitate debug
#ifdef AEE_SIMULATOR
// Note : use this debug-version GL_NEW like this:
//		pointerToSomething = (GL_NEW(MemoryType) Class);
//  or, pointerToSomething = (NEW_TOP/NEW_BOTTOM Class);
//#define GL_NEW(x) CMemoryPool::Check( __FILE__, __LINE__ ), new
//#define GL_NEW CMemoryPool::Check( __FILE__, __LINE__ ), new
//#define SET_MEM_CHECK( type ) CMemoryPool::SetCheck( (type) );
//#define GL_NEW(x) new(__FILE__, __LINE__)
//#define GL_NEW debug_new
//#define GL_NEW new

#define GL_NEW debug_new
#else
#define GL_NEW new
#define SET_MEM_CHECK( type )
#endif
/// @ingroup Global
/// @brief This operator attempts to free one or more objects in pool or heap.
///
/// Use GL_DELETE or GL_DELETE[] instead of "delete" to facilitate debug
//#define GL_DELETE delete
/// @ingroup Global
/// @brief This "operator" attempts to dynamically allocate one or more objects from the top of default pool.
//#define NEW_TOP GL_NEW(POOL_TOP)
/// @ingroup Global
/// @brief This "operator" attempts to dynamically allocate one or more objects from the bottom of default pool.
//#define NEW_BOTTOM GL_NEW(POOL_BOTTOM)

/// @ingroup Global
/// @brief This operator attempts to free one object and set the object pointer to NULL.
/// Use this macro to enhance robustness
//#define SAFE_DELETE(x) GL_DELETE x; (x) = NULL
/// @ingroup Global
/// @brief This operator attempts to free an object array and set the object array pointer to NULL.
/// Use this macro to enhance robustness
//#define SAFE_DELETE_ARRAY(x) GL_DELETE[] x; (x) = NULL

#define SAFE_DELETE(a)				{if(a){delete (a);a=NULL;}}
#define SAFE_DELETE_ARRAY(a)		{if(a){delete [] (a);a=NULL;}}
#define SAFE_DELETE_ARRAY_ARRAY(p, n) { if (p) { for (int __i = 0; __i < n;__i++) SAFE_DELETE_ARRAY((p)[__i]); delete[] (p); p = NULL; } }
MemoryType GetMemoryType(void *p);

#ifdef ENABLE_RTTI
	#define DYNAMIC_CAST(t, v) dynamic_cast<t>(v)
	#define STATIC_CAST(t, v) static_cast<t>(v)
	#define REINTERPRET_CAST(t, v) reinterpret_cast<t>(v)
	#define CONST_CAST(t, v) const_cast<t>(v)
#else
	#define DYNAMIC_CAST(t, v) ((t)(v))
	#define STATIC_CAST(t, v) ((t)(v))
	#define REINTERPRET_CAST(t, v) ((t)(v))
	#define CONST_CAST(t, v) ((t)(v))
#endif

#if defined(_MSC_VER)
	typedef __int64 s64;
	typedef unsigned __int64 u64;
#else
	typedef long long s64;
	typedef unsigned long long u64;
/*
	class s64
	{
	public:
		s64( int val = 0 )
		{
			//m_high = val & 0x80000000;
			//m_low = val & 0x7FFFFFFF;
			if ( val < 0 )
			{
				m_high = -1;
			}
			else
			{
				m_high = 0;
			}
			m_low = val & 0x7FFFFFFF;
		}

		s64( int high, unsigned int low )
		{
			m_high = high;
			m_low = low;
		}

		s64 operator << ( int bits )
		{
			ASSERT( bits >= 0 );
			if ( bits >= 32 )
			{
				return 0;
			}

			s64 res( m_high, m_low );

			if ( bits )
			{
				res.m_high <<= bits;
				res.m_high |= (m_low >> (32-bits));
				res.m_low = (m_low << bits);
			}

			return res;
		}

		s64 operator >> ( int bits )
		{
			ASSERT( bits >= 0 );
			if ( bits >= 32 )
			{
				return 0;
			}
			
			s64 res( m_high, m_low );

			if ( bits )
			{
				res.m_low >>= bits;
				res.m_low |= (( m_high  ) << (32-bits));
				res.m_high = (m_high >> bits);
			}

			return res;
		}

		bool operator == ( const s64& rhs )
		{
			return m_high == rhs.m_high && m_low == rhs.m_low;
		}

		bool operator != ( const s64& rhs )
		{
			return ! operator==( rhs );
		}

		bool operator & ( const s64& rhs )
		{
			return (m_high & rhs.m_high) || (m_low & rhs.m_low);
		}

		s64& operator |= ( const s64& rhs )
		{
			m_high |= rhs.m_high;
			m_low |= rhs.m_low;
			return *this;
		}

		s64& operator <<= ( int bits )
		{
			return operator=( operator << (bits) );
		}	

		s64& operator = ( const s64& rhs )
		{
			m_high = rhs.m_high;
			m_low = rhs.m_low;
			return *this;
		}

	protected:
		int				m_high;
		unsigned int	m_low;
	};
	*/
#endif

typedef struct {
	short x, y;
	unsigned short w, h;
}Rect16;

class CEngine;

/// @ingroup Global
/// @brief Get the global CEngine instance.
/// @warning Be careful to use these global GetXXX functions because they may need many CPU circles to get the result.
/// Cache the result if it will be used extensively in a class/function.
CEngine& GetEngine();


#ifdef ENABLE_PALETTE_ALPHA_BLIT
#ifdef USE_DIRECT_DRAW
typedef unsigned int PalettePixel_16;
#else
typedef unsigned short PalettePixel_16;
#endif
#else
typedef unsigned short PalettePixel_16;
#endif


#if NATIVE_COLOR_DEPTH == 12
typedef unsigned short NativePixel;
typedef NativePixel PalettePixel;
#elif NATIVE_COLOR_DEPTH == 16
typedef unsigned short NativePixel;
typedef PalettePixel_16 PalettePixel;
#elif NATIVE_COLOR_DEPTH == 24
typedef unsigned int NativePixel;
typedef NativePixel PalettePixel;
#else
#error NATIVE_COLOR_DEPTH must be defined!
#endif

#endif