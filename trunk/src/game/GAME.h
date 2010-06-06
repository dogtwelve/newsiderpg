#ifndef _GAME_
#define _GAME_

#include "DEF.h" 

class GAME
{
public:
	static const bool k_debugPathfindingExec = false ;
};



class BB
{
	// Circular Dirty Buffer...
public:
	const static int CDB_AX	= 1;												// additional columns [tiles]
	const static int CDB_AY	= 1;												// additional rows [tiles]

	const static int CDB_TW	= (SCR_W + TILE_W - 1) / TILE_W + CDB_AX;// CDB width [tiles]
	const static int CDB_TH	= (SCR_H + TILE_H - 1) / TILE_H + CDB_AY;// CDB height [tiles]

	const static int CDB_W	= CDB_TW * TILE_W;								// CDB width [pixels]
	const static int CDB_H	= CDB_TH * TILE_H;								// CDB height [pixels]
};



class VIEWPORT
{
	// --------------------------------------------------- top viewports 240x320
public:
	const static int k_x		= 0;
	const static int k_y		= 0;
	const static int k_w		= SCREEN_WIDTH;
	const static int k_h		= 296;//160 + 16;//triplet

	const static int k_bottom	= k_y + k_h;

	const static int k_middle_x		= k_x + (k_w / 2);
	const static int k_middle_y		= k_y + (k_h / 2);
};



class RECT
{
	public:
	//---------------------------------------------------------------- rectangle
	const static int k_x	= 0;
	const static int k_y	= 1;
	const static int k_w	= 2;
	const static int k_h	= 3;
	const static int k_size	= 4;
};



//typedef enum 
class COL_TILES
{
	public:

	const static int k_oob_null	 					= 100;
	const static int k_oob_top	 					= -5;
	const static int k_oob_bot	 					= -4;
	const static int k_oob_left 					= -3;
	const static int k_oob_right 					= -2;
	const static int k_can_move 					= -1;
	const static int k_cant_move_wall				= 0;
	const static int k_cant_move_stop				= 1;

	const static int k_door0				= 15;
	const static int k_door1				= 16;
	const static int k_door2				= 17;
	const static int k_door3				= 18;

	const static int k_water1						= 25;
	const static int k_water2						= 26;
	const static int k_water3						= 27;

	//const static int k_can_move_unsigned			= 255;
	//const static int k_special_tile_start			= k_pooppee;
};



class CLOCK 
{
	public:
	// --------------------------------------------------------------- positions
	const static int ck_x			= SCREEN_WIDTH;
	const static int ck_y			= 0;
	const static int k_h_radius		= 5;
	const static int k_m_radius		= 8;
	const static int k_center_x		= -19;
	const static int k_center_y		= 18;
	const static int k_color_night		= 0xffffff;
	const static int k_color_day		= 0x505068;

	// ------------------------------------------------------------------ timers
	const static int k_minute_ms	=   60*4;
	const static int k_hour_ms		= 3600*4;

	// ----------------------------------------------------------------- modulos
	const static int k_minute		= 60;
	const static int k_hour			= 24;
};



//typedef enum
class TILE_LAYER 
{
	public:
	const static int k_id_ground = 0;
	const static int k_id_ground2 = 1;
	const static int k_id_ground3 = 2;
	const static int k_id_ground4 = 3;
	const static int k_id_upper = 4;
	const static int k_id_cnt = 5;
};



#endif//_GAME_