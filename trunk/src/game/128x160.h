#ifndef __UI_128_160_H__
#define __UI_128_160_H__

#define SCALE_X 128/240
#define SCALE_Y 160/320
#define OS_SCREEN_W	(128)
#define OS_SCREEN_H	(160)

#define SCREEN_HEIGHT  (OS_SCREEN_H-g_pGame->m_nAnnunciator_Height)
#define SCREEN_WIDTH OS_SCREEN_W

#define TOP_START_POSY				41
#define TOP_MENU_GAPY				27

//GuanHao. menu. scroll bar
#define SCROLLBAR_X 122
#define SCROLLBAR_Y 20
#define SCROLLBAR_W 5
#define SCROLLBAR_H 100

#define ARROW_IN_OPTION 45
#define  ARROW_IN_INFO 47

//GuanHao. help
#define MENU_GAMEINFO_COUNT		    21

//GuanHao. menu. ingame
#define INVEN_QUEST_POSY						SCREEN_HALF_HEIGHT -12 

#define INVEN_QUEST_DESC_POSX						SCREEN_HALF_WIDTH - 40 
#define INVEN_QUEST_DESC_POSY						SCREEN_HALF_HEIGHT + 28 
#define INVEN_QUEST_DESC_WIDTH					80
#define INVEN_QUEST_DESC_HEIGHT					52

#define DRAW_PASTURE_UIX	     			33
#define DRAW_PASTURE_UIY	     			20

//liu kunpeng
#define FISHUI_STARTX	     			33
#define FISHUI_STARTY	     			13

#define DRAW_STARTX	     						(SCREEN_HALF_WIDTH - ((OBJECT_SIZEX*COUNT_X)/2))
#define DRAW_STARTY	     						(SCREEN_HEIGHT - ((OBJECT_SIZEY*COUNT_Y)+DRAW_GAP))
#define NUMBER_OFFSET_X 0
#define NUMBER_OFFSET_Y 0

	#define OBJECT_POS_X					SCREEN_HALF_WIDTH+3-7
	#define OBJECT_POS_Y					SCREEN_HEIGHT - 25+14

	#define OBJECT_CAR_POS_X				OBJECT_POS_X-70
	#define OBJECT_CAR_POS_Y				OBJECT_POS_Y-49

	#define LEVEL_POS_X						20//5
	#define LEVEL_POS_Y						20//15
	
	#define MASCOT_BAR_MAX_DISP_Y                           52
//

//class DEF
//{
//public:
	const static bool bOnline = true; 	// multiplayer code
	const static bool bEmu = false;	// emulator
	const static bool bRelease = true; 	// release version
	const static bool bSnd = !true; 	// sound suport enable
	const static bool bSnd_test = false;	// test the sound
	const static bool bErr = !false;	// catch errors (exceptions)
	const static bool bASSERT = false;	// enables DBG.ASSERT

	// enable/disable "System.out.println"
	const static bool bDbgO = !false;	// generic debug out (System.out.println)
	const static bool bDbgT = false;	// trace calls and params (lots of output)
	const static bool bDbgM = !false;	// debug out for memory
	const static bool bDbgS = false;	// debug out for cSprite.Load()
	const static bool bDbgI = false;	// debug out for images (cached sprites)

	const static bool bDbgMp = false;	// debug out for multiplayer

	const static bool DbgDrawFPS = false;	// shows the FPS
	const static bool DbgDrawMem = false;	// shows the free memory
	const static bool DbgDrawFrameNr = false;	// shoes the frame number (game counter)
	const static bool bDbgInfo = (bErr || bDbgO || DbgDrawFPS || DbgDrawMem || DbgDrawFrameNr);

	const static bool bSlowMode = !false;	// slow mode can be switched with the SOFT_M key

	//const static bool LIMIT_FPS = true; 	// limit framerate
	const static int MAX_FPS = 14;		// maximum fps (if limited)

	const static int SCR_W = 128;
	const static int SCR_H = 144;

	//////////////////////////////////////////////////
	// Workarounds for some issues...

	const static bool bClippingBug = false;
	const static bool bStreamReadBug = false;
	const static bool bMotorolaV300 = true;

	//////////////////////////////////////////////////

	const static int FIXED_PRECISION = 0;		// fixed point precision

	//////////////////////////////////////////////////
	// [game pixels] = game pixels = [screen pixels] * ZOOM_XY_DIV / ZOOM_XY
	// [pixels]      = screen pixels = [game pixels] * ZOOM_XY / ZOOM_XY_DIV
	// [tiles]       = map tiles = [pixels] / TILE_WH

	// Game to screen zoom [screen pixels] / [game pixels]...
	const static int ZOOM_X = 1; // zoom in
	const static int ZOOM_Y = 1;
	const static int ZOOM_X_DIV = 1; // zoom out
	const static int ZOOM_Y_DIV = 1;

	// Tileset for background...
	const static int TILE_W		= 10;				// width  of a tile [pixels]
	const static int TILE_H		= 10;				// height of a tile [pixels]

	// Logical game tiles...
	const static int G_TILE_W	= 10;				// width  of a tile [game pixels]
	const static int G_TILE_H	= 10;				// height of a tile [game pixels]

	// Screen view [pixels]...
	const static int SV_W = SCR_W;			// screen view width
	const static int SV_H = SCR_H;			// screen view height
	const static int SV_X = 0;				// screen view position x
	const static int SV_Y = 0;				// screen view position y

	// Game view [game pixels]...
	//	const static int GV_X 		=					// _nGV_X = -(_level.x >> 8)
	//	const static int GV_Y 		=					// _nGV_Y = -(_level.y >> 8)
	const static int GV_W = SV_W * ZOOM_X_DIV / ZOOM_X;	// game view width
	const static int GV_H = SV_H * ZOOM_Y_DIV / ZOOM_Y;	// game view height

//};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
	#define LETTER_COLLIDE_ZONE_X (177+20)
	#define GROUND_GAPX							(63*TILE_W/20)	// ground each depth
	#define GROUND_GAPY							(69*TILE_W/20)	// ground each depth
	#define DATE_POSX			SCREEN_HALF_WIDTH+4
	#define CLOCK_POSX			SCREEN_WIDTH-15
	#define CLOCK_POSY			7
	#define DATE_POSY			CLOCK_POSY-4

	#define MAIN_TEXT_BAD_END_Y 31
	#define TEXT_BAD_POSY_OFFSET 0
	#define BLACK_RECT_OFFSET_Y 0
	#define CHR_POSY_OFFSET_Y 0

	#define WOOL_GROUND_SIZE 15
	#define OBJECT_SIZEX	     					15//30
	#define OBJECT_SIZEY	     					15//30
	#define DRAW_GAP	     						10

	#define FISH_OFFSET_Y1 208
	#define FISH_OFFSET_Y2 280
	#define FISH_OFFSET_X1 260

	#define FISH_RESULT_OFFSET_Y 50

    #define OBJECT_WIDTH_GAP				20//40
	#define OBJECT_HEIGHT_GAP				10//20

	#define INVENT_OFFSET_X 35

	#define TALK_ANIM_OFFSET_X 0

	#define FISH_RESULT_OFFSET_X 0

	#define NPC_RECT_MINPOPY			SCREEN_HALF_HEIGHT+5
	#define NPC_RECT_MAXPOPY			SCREEN_HEIGHT-40

	#define TEXT_HAPPY_POSY							(IMG_HAPPY_POSY+IMG_HAPPY_SIZEY+60)

	#define TEXT_HAPPY_SIZEY						(SCREEN_HEIGHT-(IMG_HAPPY_POSY+IMG_HAPPY_SIZEY+25))

	#define END_FADE_LEFT_OFFSET_X 0

	#define IGP_NEW_POS_X 81

	#define IGP_NEW_OFFSET_Y 0

#endif