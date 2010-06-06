#ifndef __DEVICE_INFO_H__
#define __DEVICE_INFO_H__

#define DEVICE	DEVICE_LG7000
#if DEVICE == DEVICE_N3589i

#define BREW_OS 1
//#define SCREEN_WIDTH 96
//#define SCREEN_HEIGHT 65
#define MIN_TIMER_INVERVAL 2

#elif DEVICE == DEVICE_LG4700
#define BREW_OS 2
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 114
#define MIN_TIMER_INVERVAL 2

//#elif DEVICE == DEVICE_KX414
//
//#define BREW_OS 2
//#define SCREEN_WIDTH 104
//#define SCREEN_HEIGHT 68
//#define MIN_TIMER_INVERVAL 2

#elif DEVICE == DEVICE_Nokia6256

#define BREW_OS 2
//#define SCREEN_WIDTH 128
//#define SCREEN_HEIGHT 132
#define MIN_TIMER_INVERVAL 2

#elif DEVICE == DEVICE_LG4400

#define BREW_OS 1
//#define SCREEN_WIDTH 120
//#define SCREEN_HEIGHT 115
#define MIN_TIMER_INVERVAL 2

#elif DEVICE == DEVICE_LG6000 || DEVICE == DEVICE_LG4500

#define BREW_OS 2
//#define SCREEN_WIDTH 120
//#define SCREEN_HEIGHT 146
//Minimum delay between two timer events.
//Some devices have bad keypad response if this value is too small.
#define MIN_TIMER_INVERVAL 2

// added by wubin
#define TICK_PER_FRAME_WHEN_LOADING	50

#elif DEVICE == DEVICE_LG9800 //LYJ ADD

#define BREW_OS 2
//#define SCREEN_WIDTH 320
//#define SCREEN_HEIGHT 240
//Minimum delay between two timer events.
//Some devices have bad keypad response if this value is too small.
#define MIN_TIMER_INVERVAL 2


#elif DEVICE == DEVICE_A650

#define BREW_OS 2
//#define SCREEN_WIDTH 128
//#define SCREEN_HEIGHT 146
//Minimum delay between two timer events.
//Some devices have bad keypad response if this value is too small.
#define MIN_TIMER_INVERVAL 2

#elif DEVICE == DEVICE_CDM8910

#define BREW_OS 2
//#define SCREEN_WIDTH 128
//#define SCREEN_HEIGHT 145
//Minimum delay between two timer events.
//Some devices have bad keypad response if this value is too small.
#define MIN_TIMER_INVERVAL 2

#elif DEVICE == DEVICE_LG4700
#define BREW_OS 2
//#define SCREEN_WIDTH 128
//#define SCREEN_HEIGHT 114
#define MIN_TIMER_INVERVAL 2

#elif DEVICE == DEVICE_LG5200
#define BREW_OS 2
//#define SCREEN_WIDTH 128
//#define SCREEN_HEIGHT 116
#define MIN_TIMER_INVERVAL 2
//
#elif DEVICE == DEVICE_MotoV260

#define BREW_OS 2
//#define SCREEN_WIDTH 128
//#define SCREEN_HEIGHT 116
#define MIN_TIMER_INVERVAL 2

//#elif DEVICE == DEVICE_CDM8600
//#define BREW_OS 2
//#define SCREEN_WIDTH 128
//#define SCREEN_HEIGHT 112
//#define MIN_TIMER_INVERVAL 2
//
//#elif DEVICE == DEVICE_SE47
//#define BREW_OS 2
//#define SCREEN_WIDTH 128
//#define SCREEN_HEIGHT 116
//#define MIN_TIMER_INVERVAL 2

#elif DEVICE == DEVICE_LG7000

#define BREW_OS 2
#define COLOR_DEPTH 16
#define TICK_PER_FRAME_WHEN_LOADING	50
//#define SCREEN_WIDTH 176
//#define SCREEN_HEIGHT 203

//Minimum delay between two timer events.
//Some devices have bad keypad response if this value is too small.
#define MIN_TIMER_INVERVAL 20	
#elif DEVICE == DEVICE_CDM9900

#define BREW_OS 2
#define COLOR_DEPTH 16
//#define SCREEN_WIDTH 240
//#define SCREEN_HEIGHT 292

//Minimum delay between two timer events.
//Some devices have bad keypad response if this value is too small.
#define MIN_TIMER_INVERVAL 17	
#endif

#if PLATFORM == PLATFORM_BREW
//void using SCREEN_WIDTH and SCREEN_HEIGHT to improve portability
#else

#endif

//#undef SCREEN_WIDTH
//#undef SCREEN_HEIGHT
#endif