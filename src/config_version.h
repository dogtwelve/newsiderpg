 #ifndef __CONFIG_VERSION_H__
#define __CONFIG_VERSION_H__

#include "DEF.h"

//#define USE_PATH_FINDING
//#define REDUCE_COLL_RECT
#define REMOVE_STATE_PRESENT_ZONE
//#define SCREEN_HEIGHT  296
//#define SCREEN_WIDTH 240

#define TEMP_CHARS_LENGTH  512


#define USE_OLD_KEY_CONTROL

#define WIPIC

#ifdef AEE_SIMULATOR
#define DEBUG_LEVEL 3
#else
#define DEBUG_LEVEL 0
#endif

#define SOUND_LEVEL 0
//MY_DEBUG

#ifdef MY_DEBUG
//#define DEGUG_MEMORY
#define MEMORY_OUTPUT
#endif

#define NATIVE_COLOR_DEPTH 16
#define	NATIVE_COLOR_PITCH 2	
#define GRAPHICS_ENABLE_RGB16
#define GRAPHICS_ENABLE_RGB24
#define ENABLE_CHEAT_CODE 
#define SPRITE_LAGER_THAN_64K

#define ENABLE_ALPHA

//graphic functions macro switches, comment the lines (#define) you don't need for saving code size
#define ENABLE_OPACITY_BLIT	//enable opacity blitting
#define ENABLE_ALPHA_BLIT	//enable alpha blitting
#define ENABLE_4_BLIT	//enable 4 bit to 16 bit blitting
#define ENABLE_32_BLIT	//enable 32 bit to 16 bit blitting
#define ENABLE_I64RLE_BLIT	//enable I64RLE to 16 bit blitting
#define ENABLE_I127RLE_BLIT	//enable I127RLE to 16 bit blitting
#define ENABLE_I256RLE_BLIT	//enable I256RLE to 16 bit blitting

#define ENABLE_ACCELERATE_BLIT	//enable accelerate some blitting functions, will enlarge code size

#if defined ENABLE_ALPHA_BLIT
#define ENABLE_PALETTE_ALPHA_BLIT	//enable add alpha value in palette data, will enlarge memory usage
#endif
#if defined ENABLE_PALETTE_ALPHA_BLIT
#define ENABLE_RLE_ALPHA_BLIT	//enable alpha blitting from RLE source
#endif
#if defined ENABLE_OPACITY_BLIT
#define ENABLE_RLE_OPACITY_BLIT	//enable opacity blitting from RLE source
#endif
#if defined ENABLE_PALETTE_ALPHA_BLIT && defined ENABLE_OPACITY_BLIT
#define ENABLE_RLE_ALPHA_OPACITY_BLIT	//enable both alpha and opacity blitting from RLE source
#endif

#define USE_DIRECT_DRAW
#if defined USE_DIRECT_DRAW
#define USE_DRAWRGB_FOR_TILES
#endif


#define USE_CHECKSPACE

#define ENABLE_ACCELERATE_BLIT	//enable accelerate some blitting functions, will enlarge code size



#define TICK_PER_FRAME 80
const int TARGET_FPS = 1000 / TICK_PER_FRAME;
const int REFERENCE_FPS 	= 12; // 83 ms
const int FRAME_TIME		= 1000 / TARGET_FPS;
const int FPS_RATIO		= 1;
//const int FIXED_PRECISION = 8; // fixed point precision

#define MAX_RESOURCE_FILE 1
#define DEFAULT_RESOURCE_FILE "res.bar"
//#define DEFAULT_RESOURCE_FILE2 "font.dat"


enum {
	MEMORY_POOL_DEFAULT = 0,
	MEMORY_POOL_GLOBAL,	
	MEMORY_POOL_ACTOR,
	MEMORY_POOL_TOTAL,
};

typedef enum {
	DYNAMIC = -1,
	POOL_BOTTOM,
	POOL_TOP,
	GLOBAL_BOTTOM,
	GLOBAL_TOP,
	ACTOR_BOTTOM_PLAYER,
	ACTOR_TOP_OTHERS,
}MemoryType;

const int	kDefaultPoolSize[MEMORY_POOL_TOTAL] = 
{
	350 * 1024,//POOL
	300 * 1024,//GLOBAL
	500 * 1024,
};

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

class Graphics
{
public:
	enum	// same as CGraphics::XXX
	{
		HCENTER = 1 << 0,
		VCENTER = 1 << 1,
		LEFT = 1 << 2,
		RIGHT = 1 << 3,
		TOP = 1 << 4,
		BASELINE = 1 << 5,
		BOTTOM = 1 << 6,
	};
};

class kScreen
{
public:
	enum
	{
		SCREEN_W = 240,
		SCREEN_H = 296,

		SCREEN_HALF_W		= SCREEN_W/2,
		SCREEN_HALF_H		= SCREEN_H/2,

		INTERFACE_WIDTH		= 32,
		INTERFACE_HEIGHT	= 32,

		TILE_WIDTH			= 16,
		TILE_HEIGHT			= 16,
		TILE_WIDTH_HALF		= (TILE_WIDTH >> 1),
		TILE_HEIGHT_HALF		= (TILE_HEIGHT >> 1),
		TILE_WIDTH_BIT		= 4, // value / TILE_WIDTH = value >> TILE_WIDTH_BIT
		TILE_HEIGHT_BIT		= 4, // value / TILE_HEIGHT = value >> TILE_HEIGHT_BIT

		VIEWPORT_LEFT		= 0,
		VIEWPORT_RIGHT		= SCREEN_W,
		VIEWPORT_TOP		= INTERFACE_HEIGHT,
		VIEWPORT_BOTTOM		= SCREEN_H,
		VIEWPORT_WIDTH		= VIEWPORT_RIGHT - VIEWPORT_LEFT,
		VIEWPORT_HEIGHT		= VIEWPORT_BOTTOM - VIEWPORT_TOP,

		VIEWPORT_WIDTH_HALF	= (VIEWPORT_WIDTH >> 1),
		VIEWPORT_HEIGHT_HALF	= (VIEWPORT_HEIGHT >> 1),

		MAPBUFF_TWIDTH 	= (VIEWPORT_WIDTH + TILE_WIDTH + TILE_WIDTH - 1) / TILE_WIDTH,
		MAPBUFF_THEIGHT 	= (VIEWPORT_HEIGHT + TILE_HEIGHT + TILE_HEIGHT - 1) / TILE_HEIGHT,
		MAPBUFF_WIDTH 	= MAPBUFF_TWIDTH * TILE_WIDTH,
		MAPBUFF_HEIGHT 	= MAPBUFF_THEIGHT * TILE_HEIGHT,
	};
};

//#include "game/ANIM.hpp"
//#include "game/StrId.hpp"
//#include "game/DATA.hpp"

	//formerly in Screen176x204.h

    enum { GAME_MENU_WIDTH = 90 };
    enum { GAME_MENU_HEIGHT = 120 };
    enum { GAME_MENU_LEFT = 5 };
    enum { GAME_MENU_TOP = kScreen::SCREEN_H - 26 - GAME_MENU_HEIGHT };
    enum { GAME_MENU_STRING_X = GAME_MENU_LEFT + (GAME_MENU_WIDTH >> 1) };
    enum { GAME_MENU_STRING_Y = GAME_MENU_TOP + 17 };
    enum { GAME_MENU_STRING_HEIGHT = 13 };//15 };
    enum { GAME_MENU_EDGE_COLOR = 0x808080 };

    enum { CONFIRM_WIDTH = 160 };
    enum { CONFIRM_HEIGHT = 40 };
    enum { CONFIRM_LEFT = (kScreen::SCREEN_W - CONFIRM_WIDTH) >> 1 };
    enum { CONFIRM_TOP = (kScreen::SCREEN_H - CONFIRM_HEIGHT) >> 1 };

    enum { BLACKOUT_FULLSCREEN = kScreen::SCREEN_H >> 1 };
    enum { BLACKOUT_HEIGHT_PER_FRAME = 10 };

	//formerly in Actor176x204.h        
    // Camera Control
	enum { CAMERA_FIXED_X 						= 0x01 }; //
	enum { CAMERA_FIXED_Y 						= 0x02 }; //
	enum { CAMERA_MOVE_TO 						= 0x04 }; //move to one place for 2 seconds
	enum { CAMERA_ACTIVE_ONCE 					= 0x08 }; //only active once

class IMisc
{
public:
	enum
	{
		CinemeticBarHeight = 35,
		BarsColor= 0x00000000,		
		AlphaFadingNumSteps = ((( 1000 ) * TARGET_FPS + 500) / 1000),
		DreamWorksLogoBGColor	= 0x00201818,
	};
};

class SpriteStringFlags
{
public:
	enum { None = 0 };
	enum { Wrap = 0x1000000 };

	//Anchor (same as graphics)
	enum { HCenter	= 0x0000001 };
	enum { VCenter	= 0x0000002 };
	enum { Left		= 0x0000004 };
	enum { Right		= 0x0000008 };
	enum { Top		= 0x0000010 };
	enum { Bottom		= 0x0000020 };

	//For progs only.
	enum { GraphicsHorizontalAnchorMask = HCenter | Left | Right };
	enum { GraphicsVerticalAnchorMask = VCenter | Top | Bottom };
	enum { GraphicsAnchorMask = GraphicsHorizontalAnchorMask | GraphicsVerticalAnchorMask };
};

// FONT STUFF
class Fonts
{
public:
	enum { Normal			= 0 };
	enum { HUD				= 1 };
	enum { Count			= 2 };
};

// class FontNormalPalette
// {
// public:
// 	enum { Image			= 0 };	
// 	enum { White			= Image };
// 	enum { Black			= White + 1 };
// 	enum { Red				= Black + 1 };
// };

class FontPalette
{
public:
	enum
	{
	YellowBlackOutline					= 0,
	GreenNoOutline			= 1,
	GreenYellowOutline		= 2,
	RedYellowOutline		= 3,
	YellowNoOutline		= 4,
	OrangeYellowOutline	= 5,
	YellowRedOutline			= 6,
	Grey					= 7,
	WhiteBlackOutline		= 8,
	};
};

typedef unsigned char byte;


#define INVTABLE_RANGE		((1 << 16)+32)	
#define INVTABLE_SHIFT 22





#endif
