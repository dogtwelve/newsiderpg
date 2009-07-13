#ifndef __UI_240_320_H__
#define __UI_240_320_H__

//#define SCALE_X 240/240
//#define SCALE_Y 320/320

#define OS_SCREEN_W	(240)
#define OS_SCREEN_H	(320)

#define SCREEN_HEIGHT  (296)
#define SCREEN_WIDTH OS_SCREEN_W



//#define MENU_ITEM_HEIGHT 25

//#define TOP_START_POSY				67

//GuanHao. menu. scroll bar
//#define SCROLLBAR_X 228
//#define SCROLLBAR_Y 40
//#define SCROLLBAR_W 8
//#define SCROLLBAR_H 230
//
//#define ARROW_IN_OPTION 60
//#define  ARROW_IN_INFO 47

//GuanHao. help
//#define MENU_GAMEINFO_COUNT		    21

//GuanHao. menu. ingame
//#define INVEN_QUEST_POSY						SCREEN_HALF_HEIGHT -16 
//#define INVEN_QUEST_DESC_POSX						SCREEN_HALF_WIDTH - 76 
//#define INVEN_QUEST_DESC_POSY						SCREEN_HALF_HEIGHT + 50 
//#define INVEN_QUEST_DESC_WIDTH					140
//#define INVEN_QUEST_DESC_HEIGHT					82

//#define DRAW_PASTURE_UIX	     			35
//#define DRAW_PASTURE_UIY	     			35

//liu kunpeng
//#define FISHUI_STARTX	     			36
//#define FISHUI_STARTY	     			33

//#define DRAW_STARTX	     						(SCREEN_HALF_WIDTH - ((OBJECT_SIZEX*COUNT_X)/2))
//#define DRAW_STARTY	     						(SCREEN_HEIGHT - ((OBJECT_SIZEY*COUNT_Y)+DRAW_GAP))
//#define NUMBER_OFFSET_X 0
//#define NUMBER_OFFSET_Y 0

	//#define OBJECT_POS_X					SCREEN_HALF_WIDTH+3
	//#define OBJECT_POS_Y					SCREEN_HEIGHT - 25

	//#define OBJECT_CAR_POS_X				OBJECT_POS_X-70
	//#define OBJECT_CAR_POS_Y				OBJECT_POS_Y-49

	//#define LEVEL_POS_X						40//5
	//#define LEVEL_POS_Y						40//15
	//
	//#define MASCOT_BAR_INITAL_POS_Y                         SCREEN_HEIGHT
	//#define MASCOT_BAR_MAX_DISP_Y                           52
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

	const static int SCR_W = SCREEN_WIDTH;

	const static int SCR_H = 296;


	//////////////////////////////////////////////////
	// Workarounds for some issues...

	const static bool bClippingBug = false;
	const static bool bStreamReadBug = false;
	const static bool bMotorolaV300 = true;

	//////////////////////////////////////////////////

	const static int FIXED_PRECISION = 0;		// fixed point precision
//	const static int MAP_FIXED_PRECISION = 4;		// fixed point precision

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
	const static int TILE_W		= 16;				// width  of a tile [pixels]
	const static int TILE_H		= 16;				// height of a tile [pixels]

	// Logical game tiles...
	const static int G_TILE_W	= 16;				// width  of a tile [game pixels]
	const static int G_TILE_H	= 16;				// height of a tile [game pixels]

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
//	#define LETTER_COLLIDE_ZONE_X 177
//	#define GROUND_GAPX							(63*TILE_W/20)	// ground each depth
//	#define GROUND_GAPY							(69*TILE_W/20)	// ground each depth

    #define CLOCK_POSX			SCREEN_WIDTH-20
    #define CLOCK_POSY			17
	#define DATE_POSX			18 //slash position X
	#define DATE_POSY			3
	#define TIME_POSX			75

	#define TIME_IMG_POSX			43

	#define GAUGE_POSX			7
	#define GAUGE_POSY			17
	#define GAUGE_WIDTH			16
	#define GAUGE_HEIGHT		13

	#define UI_COIN_POSX		147
	#define UI_COIN_POSY		DATE_POSY

	#define UI_PEOPLE_POSX		169
	#define UI_PEOPLE_POSY		18

	//#define MAIN_TEXT_BAD_END_Y (50)
	//#define TEXT_BAD_POSY_OFFSET 0
	//#define BLACK_RECT_OFFSET_Y 0
	//#define CHR_POSY_OFFSET_Y 0

	//#define WOOL_GROUND_SIZE 30
	//#define OBJECT_SIZEX	     					30
	//#define OBJECT_SIZEY	     					30

	//#define DRAW_GAP	     						20

	//#define FISH_OFFSET_Y1 208
	//#define FISH_OFFSET_Y2 280
	//#define FISH_OFFSET_X1 260

	//#define FISH_RESULT_OFFSET_Y 25

 //   #define OBJECT_WIDTH_GAP				40
 //   #define OBJECT_HEIGHT_GAP				20 
	//
	//#define INVENT_OFFSET_X 39

	//#define TALK_ANIM_OFFSET_X 0

	//#define FISH_RESULT_OFFSET_X 5

	//#define NPC_RECT_MINPOPY			SCREEN_HALF_HEIGHT+5
	//#define NPC_RECT_MAXPOPY			SCREEN_HEIGHT-40

	//#define TEXT_HAPPY_POSY							(IMG_HAPPY_POSY+IMG_HAPPY_SIZEY+60)

	//#define TEXT_HAPPY_SIZEY						(SCREEN_HEIGHT-(IMG_HAPPY_POSY+IMG_HAPPY_SIZEY+25))

	//#define END_FADE_LEFT_OFFSET_X 10

	//#define IGP_NEW_POS_X 130

	//#define IGP_NEW_OFFSET_Y 2

//#define GROUND_POSX							SCREEN_HALF_WIDTH+2	// ground positionx
//#define GROUND_POSY							SCREEN_HALF_HEIGHT	// ground positiony

//#define GROUND_START_POSX					(GROUND_POSX - (GROUND_GAPX>>1) - GROUND_GAPX)	// ground positiony
//#define GROUND_START_POSY					(GROUND_POSY - (GROUND_GAPY>>1) - GROUND_GAPY)	// ground positiony

//#define GROUND_WIDTH	GROUND_GAPX * GROUND_SIZEX
//#define GROUND_HEIGHT	GROUND_GAPY * GROUND_SIZEY

	//move to 240x320.h......
	//#define GROUND_GAPX							(63*TILE_W/20)	// ground each depth
	//#define GROUND_GAPY							(69*TILE_W/20)	// ground each depth

//#define BOTTOMTOOLS_HEIGHT					0//25
//#define BOTTOMTOOLS_ARROW_WIDTH				(11*TILE_W/20)
//#define BOTTOMTOOLS_GAPX					(24*TILE_W/20)
//#define BOTTOMTOOLS_ICONGAPX				(5*TILE_W/20)

//#define TOOLS_GAPX							(40*TILE_W/20)	// tools each depth
//#define TOOLS_GAPY							(40*TILE_W/20)	// tools each depth

//#define TOOLS_CURSORX						SCREEN_HALF_WIDTH+5	
//#define TOOLS_CURSORY						SCREEN_HALF_HEIGHT	
//#define TOOLS_PAGEX							SCREEN_HALF_WIDTH+5	
//#define TOOLS_PAGEY							SCREEN_HALF_HEIGHT-15	
//
//#define TOOL_BOTTOM_UI_X					SCREEN_WIDTH-25
//#define TOOL_BOTTOM_UI_Y					SCREEN_HEIGHT-19//BOTTOMTOOLS_HEIGHT
//#define TOOL_BOTTOM_WATER_GAUGEX			TOOL_BOTTOM_UI_X+1//BOTTOMTOOLS_HEIGHT
//#define TOOL_BOTTOM_WATER_GAUGEY			TOOL_BOTTOM_UI_Y+10//BOTTOMTOOLS_HEIGHT
//	//	#define TOOL_BOTTOM_UI_Y					SCREEN_HEIGHT - BOTTOMTOOLS_HEIGHT
//
//#define UI_ICON_POSY						3
//#define UI_ICON_POSX1						SCREEN_HALF_WIDTH-47
//#define UI_ICON_POSX2						SCREEN_HALF_WIDTH+22
//
//#define UI_SEED_POSY						(8*TILE_W/20)
//#define UI_SEED_POSX						SCREEN_HALF_WIDTH+(13*TILE_W/20)
//
//#define UI_MISSION_POSY						(30*TILE_W/20)
//#define UI_MISSION_POSX						(32*TILE_W/20)
//
//
//#define UI_RESULT_POSX						SCREEN_HALF_WIDTH
//#define UI_RESULT_POSY						SCREEN_HALF_HEIGHT
//
//#define BIRD_LIMITE_POSX					(20*TILE_W/20)
//#define BIRD_LIMITE_POSY					(40*TILE_W/20)
//#define BIRD_LIMITE_POSENDX					SCREEN_WIDTH - (20*TILE_W/20)
//#define BIRD_LIMITE_POSENDY					SCREEN_HEIGHT - (30*TILE_W/20) - BOTTOMTOOLS_HEIGHT
//
//#define BIRD_OUT_POSX						(-10*TILE_W/20)
//#define BIRD_OUT_POSY						(-10*TILE_W/20)
//#define BIRD_OUT_POSENDX					SCREEN_WIDTH + (10*TILE_W/20)
//#define BIRD_OUT_POSENDY					SCREEN_HEIGHT + (10*TILE_W/20) 
//
//#define BIRD_BASIC_POSITION					(30*TILE_W/20)
//	//	#define BIRD_BASIC_MOVE						5
//#define BIRD_MAX_MOVE						(5*TILE_W/20)
//#define BIRD_BASIC_MOVE						(2*TILE_W/20)
//
//#define BIRDGUN_POSX						SCREEN_WIDTH-(35*TILE_W/20)
//#define BIRDGUN_POSY						SCREEN_HEIGHT-(55*TILE_W/20) - BOTTOMTOOLS_HEIGHT
//#define BIRDGUNSTONE_POSX					BIRDGUN_POSX+(15*TILE_W/20)
//#define BIRDGUNSTONE_POSY					BIRDGUN_POSY+(21*TILE_W/20)
//
//#define BIRDGUNTARGET_POSX					BIRDGUN_POSX-(5*TILE_W/20)
//#define BIRDGUNTARGET_POSY					BIRDGUN_POSY-(21*TILE_W/20)
//
//#define BIRD_RECTX							(10*TILE_W/20)
//#define BIRD_RECTY							(10*TILE_W/20)
//#define BIRD_RECTDX							(20*TILE_W/20)
//#define BIRD_RECTDY							(20*TILE_W/20)


////////// ATTRIBUTE OF MINI_WATER /////////////////////////////////

//#define	MINI_WATERTANK_GAUGESIZE			(54*TILE_W/20)
//#define	MINI_WATERBOX_GAUGESIZE				13
//
//#define	MINI_WATERTANK_BASIC				(60*TILE_W/20)
//#define	MINI_WATERBOX_BASIC					20
//#define	MINI_WATER_BASIC					3
//
//#define	MINI_WATERTANK_PLUS					3
//
//#define	MINI_WATERTANK_INCREASE				(90*TILE_W/20)
//#define	MINI_WATERBOX_INCREASE				10
//
//#define	MINI_WATERTANK_Y					SCREEN_HEIGHT	 - (BOTTOMTOOLS_HEIGHT+1)
//#define	MINI_WATERBOX_Y						SCREEN_HEIGHT-20 - (BOTTOMTOOLS_HEIGHT+1)
//
//#define	MINI_WATERTANK_X					0
//#define	MINI_WATERHOSE_X					MINI_WATERTANK_X+71*TILE_W/20
//#define	MINI_WATERCOCK_X					MINI_WATERHOSE_X+28*TILE_W/20
//#define	MINI_WATERBOX_X						MINI_WATERCOCK_X+22
//
//#define	MINI_WATERGAUGE_Y					(MINI_WATERTANK_Y-23*TILE_W/20	)
//#define	MINI_WATERGAUGE_X					((MINI_WATERTANK_X+4)*TILE_W/20)
//#define	MINI_WATERGAUGE_WIDTH				(22*TILE_W/20)

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////Mini wool
//
//#define DRAW_WOOL_GAUGEX   						85
//#define DRAW_WOOL_GAUGEY   						10
//
//
//#define DRAW_MISSION_POSX						SCREEN_WIDTH-30
//#define DRAW_MISSION_POSY						SCREEN_HEIGHT-15

///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////mini fishing

/////////////// FISH POSITION ///////////////////////

//GuanHao. fish
//#define FISH_AREA_STARTX				20*TILE_W/20
//#define FISH_AREA_STARTY				175*TILE_W/20
//#define FISH_AREA_ENDX					SCREEN_WIDTH-20
//#define FISH_AREA_ENDY					SCREEN_HEIGHT-15
//
//#define FISH_AREA_FIELD1_START			FISH_AREA_STARTY
//#define FISH_AREA_FIELD1_END			FISH_AREA_STARTY + FISH_AREA_SPACE + 5
//
//#define FISH_AREA_FIELD2_START			FISH_AREA_STARTY + FISH_AREA_SPACE - 5
//#define FISH_AREA_FIELD2_END			FISH_AREA_STARTY + FISH_AREA_SPACE + FISH_AREA_SPACE + 5
//
//#define FISH_AREA_FIELD3_START			FISH_AREA_STARTY + FISH_AREA_SPACE + FISH_AREA_SPACE - 5
//#define FISH_AREA_FIELD3_END			FISH_AREA_ENDY
//
//#define FISH_AREA_SPACE					40

//#define BONUS_AREA_STARTX				30*TILE_W/20  //GuanHao. fish
//#define BONUS_AREA_STARTY				FISH_AREA_STARTY
//#define BONUS_AREA_ENDX					SCREEN_WIDTH-30
//#define BONUS_AREA_ENDY					BONUS_AREA_STARTY+40*TILE_W/20  //GuanHao. fish
//
//#define BOY_AREA_STARTX					20
//#define BOY_AREA_STARTY					0
//#define BOY_AREA_ENDX					SCREEN_WIDTH-10
//#define BOY_AREA_ENDY					(140*TILE_H/20)
//
//
//#define ROD_AREA_STARTX					BONUS_AREA_STARTX+50*TILE_W/20
//#define ROD_AREA_STARTY					BONUS_AREA_ENDY
//#define ROD_AREA_ENDX					BONUS_AREA_ENDX-50
//#define ROD_AREA_ENDY					BONUS_AREA_ENDY+40
//
//#define SEASTAR_AREA_STARTX				SCREEN_HALF_WIDTH+10
//#define SEASTAR_AREA_STARTY				FISH_AREA_STARTY
//#define SEASTAR_AREA_ENDX				SCREEN_HALF_WIDTH+50
//#define SEASTAR_AREA_ENDY				FISH_AREA_ENDY
//#define SEASTAR_COUNT					2
//
//
//#define POPUP_FISH_WIDTH				118
//#define POPUP_FISH_HEIGHT				130
#endif