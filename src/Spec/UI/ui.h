#ifndef __UI_H__
#define __UI_H__

#if defined W128H160
	#include "128x160.h"
#elif defined W176H220
	#include "176x220.h"
#elif defined W240H320
	#include "240x320.h"
#elif defined W320H240
	#include "320x240.h"
#endif

#endif
