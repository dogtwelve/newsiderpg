#ifndef __STATE_SPLASH_H__
#define __STATE_SPLASH_H__

#include "..\spec\spec.h"

#ifdef EVALUATION
#define SPLASH_IMG					"/splash_e.bbm"
#else
#define SPLASH_IMG					"/splash.bbm"
#endif

#define AGEMARK_IMG					"/agemark.bbm"
#define RATING_MARK_IMG				"/ratingTable.bbm"
#define IMG_NEW						"/new.bbm"


#define Splash_Sprite			g_pGame->load_commonSpriteArray[10]
//#define PopUp_Sprite		g_pGame->load_commonSpriteArray[5]

#endif //__STATE_SPLASH_H__