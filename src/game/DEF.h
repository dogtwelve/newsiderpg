#ifndef __DEF_H__
#define __DEF_H__

#include "..\Spec\spec.h"
#if defined W128H160
#include "128x160.h"
#elif defined W176H220
#include "176x220.h"
#elif defined W240H320
#include "240x320.h"
#elif defined W320H240
#include "320x240.h"
#endif
#define DEBUG			
#define MY_EVT_PEN_DOWN   1
#define MY_EVT_PEN_UP   0
#define MY_EVT_PEN_MOVE   2
#define NONE_VALUE_CLICK   -100
#define MAIN_CHARACTER_HEIGHT 16 


//#define hasShine

#endif  //__DEF_H__
	


	