#ifndef __SYSUTIL_H__
#define __SYSUTIL_H__


//#include <AEE.h>       // Standard AEE definitions //--sj
//#include <AEEStdlib.h>  // AEE Standard C library functions //--sj

#if DEBUG_LEVEL > 0
#ifdef AEE_SIMULATOR

#define ASSERT(x) {if(!(x)) __asm int 3}

#else	//arm
	#define ASSERT(x)		if(!(x)) DBGPRINTF("Assert failed: %s->%d", __FILE__, __LINE__)
#endif

#else

#define ASSERT(x) 

#endif

unsigned int GetTimeMS();
int _rand(int min,int max);
inline int rand_int()
{
	return _rand( 0, 0x7FFFFFFE );
}

//#ifndef ABS
//#define ABS(VAL) (((VAL)>0)?(VAL):(-(VAL)))
//#endif

template <typename T>
inline void arraycopy (T* src, int src_position, T* dst, int dst_position, int length)
{
	for (int i = 0; i < length; i++)
	{
		dst[i+dst_position] = src[i+src_position];
	}
}

template<class T>
inline T abs(T value)
{
	return (value>0)?value:-value;
}

template<class T>
inline T min( T a, T b )
{
	return (a>b)?b:a;
}

template<class T>
inline T max( T a, T b )
{
	return (a<b)?b:a;
}

#ifdef BIGENDIAN
	short ConvertLD2BE(short n);
	int ConvertLD2BE(int n);
#endif

#define Convert564To444(c) (((c & 0xf000) >> 4) | ((c & 0x0780) >> 3) | ((c & 0x001e) >> 1))
#define Convert444To565(c) (((c & 0x0F00) << 4) | ((c & 0x00F0) << 3) | ((c & 0x000F) << 1))

#define GET_RGB(r, g, b)    (RGBVAL) (((uint32)(r) << 16) + ((uint32)(g) << 8) + ((uint32)(b)))	

#define DEBUGPRINT(string)
#define DEBUGPRINT_NUM(string, num)

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
#endif

#define SHORT_MIN ((short)0x8000)

#if DEBUG_LEVEL == 3
template< int nMaxTimer >
class CTimer
{
	typedef enum
	{
		TIMER_RUNNING,
		TIMER_PAUSE,
	} TIMER_STATE;

#define TIMER_COUNT_ALL (nMaxTimer+1)

public:
	CTimer()
	{
		ResetAll();
	}

	void Start( int nTimer )
	{
		ASSERT( 0 < nTimer && nTimer < TIMER_COUNT_ALL );
		ASSERT( timer_state[nTimer] != TIMER_RUNNING );
		if ( timer_state[0] == TIMER_PAUSE )
		{
			StartUncond(0);	// start main timer
		}

		StartUncond(nTimer);
		
		for ( int i = 1; i < TIMER_COUNT_ALL; i++ )
		{
			if( timer_state[i] == TIMER_RUNNING && i != nTimer )
			{
				PauseUncond( i );
				return;
			}
		}
	}

	void PauseAll()
	{
		for ( int i = TIMER_COUNT_ALL-1 ; i >= 0; i-- )
		{
			if( timer_state[i] == TIMER_RUNNING )
				PauseUncond(i);
		}
	}

	void ResetAll()
	{
		for ( int i = 0; i < TIMER_COUNT_ALL; i++ )
		{
			timer_state[i] = TIMER_PAUSE;
			timer_sum[i] = 0;
		}
	}

	unsigned int GetOverAllTime()
	{
		return GetTime(0);
	}

	unsigned int GetTime( int nTimer )
	{
		ASSERT( 0 <= nTimer && nTimer < TIMER_COUNT_ALL );
		ASSERT( timer_state[nTimer] == TIMER_PAUSE );
		return timer_sum[nTimer];
	}

	int GetPercentage( int nTimer )
	{
		ASSERT( 0 < nTimer && nTimer < TIMER_COUNT_ALL );
		unsigned int all_time = GetOverAllTime();
		if( all_time == 0 ) return -1;
		return GetTime(nTimer) * 100 / all_time;
	}
	
protected:

	void StartUncond( int nTimer )
	{
		ASSERT( 0 <= nTimer && nTimer < TIMER_COUNT_ALL );
		timer_state[nTimer] = TIMER_RUNNING;
		timer_start[nTimer] = GetTimeMS();
	}

	void PauseUncond( int nTimer )
	{
		ASSERT( 0 <= nTimer && nTimer < TIMER_COUNT_ALL );
		timer_state[nTimer] = TIMER_PAUSE;
		timer_sum[nTimer] += GetTimeMS() - timer_start[nTimer];
	}

	TIMER_STATE	 timer_state[TIMER_COUNT_ALL];
	unsigned int timer_start[TIMER_COUNT_ALL];
	unsigned int timer_sum[TIMER_COUNT_ALL];
};
#endif

int StrLen(const char * str);
int StrChr(const char * str, char c);

//int Integer_parseInt(const char* str); --sj

char* TRIM (char* str);

int s_math_random_nextInt();
#endif