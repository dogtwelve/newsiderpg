#ifndef __DEVICE_INFO_H__
#define __DEVICE_INFO_H__

#include "../Spec/spec.h"

#if defined W128H160
#include "../Spec/UI/128x160.h"
#elif defined W176H220
#include "../Spec/UI/176x220.h"
#elif defined W240H320
#include "../Spec/UI/240x320.h"
#elif defined W320H240
#include "../Spec/UI/320x240.h"
#endif

#define BREW_OS 2
#define COLOR_DEPTH 16


#ifdef AEE_SIMULATOR
#define MIN_TIMER_INVERVAL  70	//SangHo - 1프레임당 소요시간 ms 에뮬
#else
#define MIN_TIMER_INVERVAL  20	//SangHo - 1프레임당 소요시간 ms 폰
#endif




#endif


